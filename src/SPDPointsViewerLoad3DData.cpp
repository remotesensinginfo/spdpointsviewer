/*
 *  SPDPointsViewerLoad3DData.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 14/12/2010.
 *  Copyright 2010 SPD3DPointsViewer.
 * 
 *  SPD3DPointsViewer is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SPD3DPointsViewer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SPD3DPointsViewer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "SPDPointsViewerLoad3DData.h"



namespace spdpointsviewer
{
	
	SPDPointsViewerLoad3DData::SPDPointsViewerLoad3DData(unsigned int *bbox, SPDPointsViewer3DWidget *openGLWidget, SPDPointsViewerColourTable *colourTable, SPDFile *spdFile, string inputDTM, string inputTris, string inputSHP, bool loadPoints, bool loadVectors, bool loadDTM, bool loadTris, bool loadSHP, bool loadWaveform, bool normaliseWaveform, ColourPtsType clrPtType, QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay, QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay, QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay, ZFieldType zFieldType, bool grdReturnsOnly)
	{
		this->bbox = bbox;
		this->openGLWidget = openGLWidget;
        this->colourTable = colourTable;
		this->spdFile = spdFile;
		this->inputDTM = inputDTM;
		this->inputTris = inputTris;
		this->inputSHP = inputSHP;
		this->loadPoints = loadPoints;
		this->loadVectors = loadVectors;
		this->loadDTM = loadDTM;
		this->loadTris = loadTris;
		this->loadSHP = loadSHP;
		this->loadWaveform = loadWaveform;
		this->clrPtType = clrPtType;
		this->classDisplay = classDisplay; 
		this->returnDisplay = returnDisplay;
		this->sourceDisplay = sourceDisplay;
		this->normaliseWaveform = normaliseWaveform;
        this->zFieldType = zFieldType;
        this->grdReturnsOnly = grdReturnsOnly; 
	}
	
	void SPDPointsViewerLoad3DData::run()
	{
		try 
		{
			if(spdFile == NULL)
			{
				emit errorMessages("No SPD file has been opened.");
				return;
			}
			
			//cout << "BBOX (READ): [" << bbox[0] << "," << bbox[1] << "," << bbox[2] << "," << bbox[3] << "]" << endl;
			
			// Define the geographic area to be read in. 
			double bboxTLX = 0;
			double bboxTLY = 0;
			double bboxBRX = 0;
			double bboxBRY = 0;
            
            double xMidValue = 0;
			double yMidValue = 0;
            
            if((spdFile->getIndexType() == SPD_SPHERICAL_IDX) | (spdFile->getIndexType() == SPD_POLAR_IDX))
            {
                unsigned int xMidPointBin = bbox[2] - bbox[0];
                unsigned int yMidPointBin = bbox[3] - bbox[1];
                
                SPDFileIncrementalReader reader;
                reader.open(spdFile);
                vector<SPDPulse*>::iterator iterPulses;
                vector<SPDPulse*> *pulses = new vector<SPDPulse*>();
                uint_fast32_t *bboxSearchArea = new uint_fast32_t[4];
                bboxSearchArea[0] = xMidPointBin - 1;
                bboxSearchArea[1] = yMidPointBin - 1;
                bboxSearchArea[2] = xMidPointBin + 1;
                bboxSearchArea[3] = yMidPointBin + 1;
                
                bool searchingForPoint = true;
                while(searchingForPoint)
                {
                    reader.readPulseDataBlock(pulses, bboxSearchArea);
                    if(pulses->size()>0)
                    {
                        xMidValue = pulses->front()->xIdx;
                        yMidValue = pulses->front()->yIdx;
                        searchingForPoint = false;
                        break;
                    }
                    else
                    {
                        bboxSearchArea[0] -= 1;
                        bboxSearchArea[1] -= 1;
                        bboxSearchArea[2] += 1;
                        bboxSearchArea[3] += 1;
                        if(bboxSearchArea[2] > spdFile->getNumberBinsX())
                        {
                            bboxSearchArea[2] = spdFile->getNumberBinsX();
                        }
                        
                        if(bboxSearchArea[3] > spdFile->getNumberBinsY())
                        {
                            bboxSearchArea[3] = spdFile->getNumberBinsY();
                        }
                    }
                }
                reader.close();
                
                SPDPulseUtils pulseUtils;
                delete[] bboxSearchArea;
                for(iterPulses = pulses->begin(); iterPulses != pulses->end(); )
                {
                    pulseUtils.deleteSPDPulse(*iterPulses);
                    iterPulses = pulses->erase(iterPulses);
                }
                delete pulses;
            }
            else
            {
                bboxTLX = spdFile->getXMin() + (((float)bbox[0]) * spdFile->getBinSize());
                bboxTLY = spdFile->getYMax() - (((float)bbox[1]) * spdFile->getBinSize());
                bboxBRX = spdFile->getXMin() + (((float)bbox[2]) * spdFile->getBinSize());
                bboxBRY = spdFile->getYMax() - (((float)bbox[3]) * spdFile->getBinSize());
                
                xMidValue = bboxTLX + ((bboxBRX - bboxTLX)/2);
                yMidValue = bboxBRY + ((bboxTLY - bboxBRY)/2);
            }
			
			cout.precision(14);
			//cout << "BBOX (MAP): [" << bboxTLX << "," << bboxTLY << "," << bboxBRX << "," << bboxBRY << "]"  << endl;
            
            //cout << "Mid Point [" << xMidValue << "," << yMidValue << "]\n";
			
			vector<float> zValues;
			float zMidValue = 0;
			float minZ = 0;
			float maxZ = 0;
			bool firstZVal = true;
			/*
            float minClrVal = 0;
			float maxClrVal = 0;
			bool firstClrVal = true;
            */
			bool clrNorm = true;
			QColor color = QColor();
			if(clrPtType == classColourType)
			{
				clrNorm = false;
			}
			else if(clrPtType == amplitudeColourType)
			{
				clrNorm = true;
			}
			else if(clrPtType == rgbColourType)
			{
				clrNorm = false;
			}
			else if(clrPtType == heightColourType)
			{
				clrNorm = true;
			}
			else if(clrPtType == returnColourType)
			{
				clrNorm = false;
			}
			else if(clrPtType == sourceColourType)
			{
				clrNorm = false;
			}
			else if(clrPtType == elevationColourType)
			{
				clrNorm = true;
			}
			else if(clrPtType == widthColourType)
			{
				clrNorm = true;
			}
			/*
            uint_fast32_t minWaveInt = 0;
			uint_fast32_t maxWaveInt = 0;
			uint_fast32_t rangeWaveInt = 0;
			bool firstWaveInt = true;
			float hue = 0;
            */
			double tempX = 0;
			double tempY = 0;
			double tempZ = 0;
			
			int feedbackVal = 0;
			
			if(loadPoints | loadVectors | loadWaveform)
			{
				if((spdFile->getDecomposedPtDefined() == SPD_FALSE) &
				   (spdFile->getDiscretePtDefined() == SPD_FALSE) &
				   (spdFile->getReceiveWaveformDefined() == SPD_FALSE))
				{
					emit errorMessages("There is no point or waveform data within the inputted SPD File.");
					return;
				}
				else 
				{
					vector<Simple3DPoint> *lines = new vector<Simple3DPoint>();
					vector<SimpleColour3DPoint> *points = new vector<SimpleColour3DPoint>();
					vector<SimpleColour3DPoint> *waveforms = new vector<SimpleColour3DPoint>();
					
					SPDFileIncrementalReader reader;
					reader.open(spdFile);
					list<SPDPulse*>::iterator iterPulses;
					list<SPDPulse*> *pulses = new list<SPDPulse*>();
					
					uint_fast32_t numRows = bbox[3] - bbox[1];
					uint_fast32_t feedback = numRows/10;
					
					for(uint_fast32_t i = 0; i < numRows; ++i)
					{
						if((numRows > 10) && (i % feedback == 0))
						{
							emit valueChanged(feedbackVal++);
						}
						
						reader.readPulseData(pulses, (i+bbox[1]), bbox[0], bbox[2]);
												
						for(iterPulses = pulses->begin(); iterPulses != pulses->end(); )
						{
							if((spdFile->getDecomposedPtDefined() == SPD_FALSE) &
							   (spdFile->getDiscretePtDefined() == SPD_FALSE) &
							   (spdFile->getReceiveWaveformDefined() == SPD_TRUE))
							{
								// Waveform data only.
								if(loadWaveform)
								{
									if((*iterPulses)->numOfReceivedBins > 0)
									{
										for(boost::uint_fast16_t n = 0; n < (*iterPulses)->numOfReceivedBins; ++n)
										{
											if(((float)(*iterPulses)->received[n]) > (*iterPulses)->receiveWaveNoiseThreshold)
											{
												if(this->zFieldType == topoHeightType)
                                                {
                                                    SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, ((*iterPulses)->rangeToWaveformStart+((((float)(n*spdFile->getTemporalBinSpacing()))/2)*SPD_SPEED_OF_LIGHT_NS)), (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->z0, &tempX, &tempY, &tempZ);
                                                }
                                                else if(this->zFieldType == normHeightType)
                                                {
                                                    SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, ((*iterPulses)->rangeToWaveformStart+((((float)(n*spdFile->getTemporalBinSpacing()))/2)*SPD_SPEED_OF_LIGHT_NS)), (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->h0, &tempX, &tempY, &tempZ);
                                                }
												
												SimpleColour3DPoint pt;
												pt.x = tempX - xMidValue;
												pt.y = tempY - yMidValue;
												pt.z = tempZ;
												pt.ptSize = 1;
                                                pt.clrVal = (((float)(*iterPulses)->received[n])*(*iterPulses)->receiveWaveGain)+(*iterPulses)->receiveWaveOffset;
												waveforms->push_back(pt);
												
												zValues.push_back(pt.z);
												if(firstZVal)
												{
													minZ = pt.z;
													maxZ = pt.z;
													firstZVal = false;
												}
												else
												{
													if(pt.z < minZ)
													{
														minZ = pt.z;
													}
													else if(pt.z > maxZ)
													{
														maxZ = pt.z;
													}
												}
											}
										}
									}
								}
								
								if(loadVectors)
								{
									if((*iterPulses)->numOfReceivedBins > 0)
									{
                                        if(this->zFieldType == topoHeightType)
                                        {
                                            SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, (*iterPulses)->rangeToWaveformStart, (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->z0, &tempX, &tempY, &tempZ);
                                        }
                                        else if(this->zFieldType == normHeightType)
                                        {
                                            SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, (*iterPulses)->rangeToWaveformStart, (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->h0, &tempX, &tempY, &tempZ);
                                        }
                                        
										Simple3DPoint pt1;
										pt1.x = tempX - xMidValue;
										pt1.y = tempY - yMidValue;
										pt1.z = tempZ;
										lines->push_back(pt1);
										
                                        if(this->zFieldType == topoHeightType)
                                        {
                                            SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, ((*iterPulses)->rangeToWaveformStart + ((((float)((*iterPulses)->numOfReceivedBins-1))/2)*SPD_SPEED_OF_LIGHT_NS)), (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->z0, &tempX, &tempY, &tempZ);
                                        }
                                        else if(this->zFieldType == normHeightType)
                                        {
                                            SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, ((*iterPulses)->rangeToWaveformStart + ((((float)((*iterPulses)->numOfReceivedBins-1))/2)*SPD_SPEED_OF_LIGHT_NS)), (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->h0, &tempX, &tempY, &tempZ);
                                        }
										Simple3DPoint pt2;
										pt2.x = tempX - xMidValue;
										pt2.y = tempY - yMidValue;
										pt2.z = tempZ;
										lines->push_back(pt2);
										
										if(firstZVal)
										{
											minZ = pt1.z;
											maxZ = pt1.z;
											firstZVal = false;
										}
										else
										{
											if(pt1.z < minZ)
											{
												minZ = pt1.z;
											}
											else if(pt1.z > maxZ)
											{
												maxZ = pt1.z;
											}
										}
										
										if(pt2.z < minZ)
										{
											minZ = pt2.z;
										}
										else if(pt2.z > maxZ)
										{
											maxZ = pt2.z;
										}
									}
									
								}
								
							}
							else if(((spdFile->getDecomposedPtDefined() == SPD_TRUE) |
									 (spdFile->getDiscretePtDefined() == SPD_TRUE)) &
									(spdFile->getReceiveWaveformDefined() == SPD_TRUE))
							{
								// Waveform and point data
								if(loadPoints)
								{
                                    if((*iterPulses)->numberOfReturns > 0)
                                    {
                                        for(unsigned int n = 0; n < (*iterPulses)->pts->size(); ++n)
                                        {
                                            if((this->grdReturnsOnly && ((*iterPulses)->pts->at(n)->classification == SPD_GROUND)) | (!this->grdReturnsOnly))
                                            {
                                                SimpleColour3DPoint pt;
                                                pt.x = (*iterPulses)->pts->at(n)->x - xMidValue;
                                                pt.y = (*iterPulses)->pts->at(n)->y - yMidValue;
                                                
                                                if(this->zFieldType == topoHeightType)
                                                {
                                                    pt.z = (*iterPulses)->pts->at(n)->z;
                                                }
                                                else if(this->zFieldType == normHeightType)
                                                {
                                                    pt.z = (*iterPulses)->pts->at(n)->height;
                                                }                                        
                                                
                                                pt.ptSize = 1;
                                                
                                                zValues.push_back(pt.z);
                                                if(firstZVal)
                                                {
                                                    minZ = pt.z;
                                                    maxZ = pt.z;
                                                    firstZVal = false;
                                                }
                                                else
                                                {
                                                    if(pt.z < minZ)
                                                    {
                                                        minZ = pt.z;
                                                    }
                                                    else if(pt.z > maxZ)
                                                    {
                                                        maxZ = pt.z;
                                                    }
                                                }
                                                
                                                if(clrPtType == classColourType)
                                                {
                                                    if (classDisplay->contains((*iterPulses)->pts->at(n)->classification))
                                                    {
                                                        CatDisplayInfo disInfo = classDisplay->value((*iterPulses)->pts->at(n)->classification);
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                    else 
                                                    {
                                                        CatDisplayInfo disInfo;
                                                        disInfo.pointSize = 1;
                                                        color.setHsvF(float(rand() % 100 + 1)/100, 1, 1, 1);
                                                        disInfo.red = color.redF();
                                                        disInfo.green = color.greenF();
                                                        disInfo.blue = color.blueF();
                                                        classDisplay->insert((*iterPulses)->pts->at(n)->classification, disInfo);
                                                        
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                }
                                                else if(clrPtType == amplitudeColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->amplitudeReturn;
                                                }
                                                else if(clrPtType == rgbColourType)
                                                {
                                                    color.setRed((*iterPulses)->pts->at(n)->red);
                                                    color.setGreen((*iterPulses)->pts->at(n)->green);
                                                    color.setBlue((*iterPulses)->pts->at(n)->blue);
                                                    
                                                    pt.r = color.redF();
                                                    pt.g = color.greenF();
                                                    pt.b = color.blueF();
                                                }
                                                else if(clrPtType == heightColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->height;
                                                }
                                                else if(clrPtType == returnColourType)
                                                {
                                                    if (returnDisplay->contains((*iterPulses)->pts->at(n)->returnID))
                                                    {
                                                        CatDisplayInfo disInfo = returnDisplay->value((*iterPulses)->pts->at(n)->returnID);
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                    else 
                                                    {
                                                        CatDisplayInfo disInfo;
                                                        disInfo.pointSize = 1;
                                                        color.setHsvF(float(rand() % 100 + 1)/100, 1, 1, 1);
                                                        disInfo.red = color.redF();
                                                        disInfo.green = color.greenF();
                                                        disInfo.blue = color.blueF();
                                                        returnDisplay->insert((*iterPulses)->pts->at(n)->returnID, disInfo);
                                                        
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                }
                                                else if(clrPtType == sourceColourType)
                                                {
                                                    if (sourceDisplay->contains((*iterPulses)->sourceID))
                                                    {
                                                        CatDisplayInfo disInfo = sourceDisplay->value((*iterPulses)->sourceID);
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                    else 
                                                    {
                                                        CatDisplayInfo disInfo;
                                                        disInfo.pointSize = 1;
                                                        color.setHsvF(float(rand() % 100 + 1)/100, 1, 1, 1);
                                                        disInfo.red = color.redF();
                                                        disInfo.green = color.greenF();
                                                        disInfo.blue = color.blueF();
                                                        sourceDisplay->insert((*iterPulses)->sourceID, disInfo);
                                                        
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                }
                                                else if(clrPtType == elevationColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->z;
                                                }
                                                else if(clrPtType == widthColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->widthReturn;
                                                }
                                                
                                                points->push_back(pt);
                                            }
                                        }
                                    }
								}
								
								if(loadVectors)
								{
                                    if((*iterPulses)->numberOfReturns > 0)
                                    {
                                        if((*iterPulses)->pts->size() > 1)
                                        {
                                            Simple3DPoint pt1;
                                            pt1.x = (*iterPulses)->pts->front()->x - xMidValue;
                                            pt1.y = (*iterPulses)->pts->front()->y - yMidValue;
                                            if(this->zFieldType == topoHeightType)
                                            {
                                                pt1.z = (*iterPulses)->pts->front()->z;
                                            }
                                            else if(this->zFieldType == normHeightType)
                                            {
                                                pt1.z = (*iterPulses)->pts->front()->height;
                                            } 
                                            lines->push_back(pt1);
                                            Simple3DPoint pt2;
                                            pt2.x = (*iterPulses)->pts->back()->x - xMidValue;
                                            pt2.y = (*iterPulses)->pts->back()->y - yMidValue;
                                            if(this->zFieldType == topoHeightType)
                                            {
                                                pt2.z = (*iterPulses)->pts->back()->z;
                                            }
                                            else if(this->zFieldType == normHeightType)
                                            {
                                                pt2.z = (*iterPulses)->pts->back()->height;
                                            }
                                            lines->push_back(pt2);
                                            
                                            if(firstZVal)
                                            {
                                                minZ = pt1.z;
                                                maxZ = pt1.z;
                                                firstZVal = false;
                                            }
                                            else
                                            {
                                                if(pt1.z < minZ)
                                                {
                                                    minZ = pt1.z;
                                                }
                                                else if(pt1.z > maxZ)
                                                {
                                                    maxZ = pt1.z;
                                                }
                                            }
                                            
                                            if(pt2.z < minZ)
                                            {
                                                minZ = pt2.z;
                                            }
                                            else if(pt2.z > maxZ)
                                            {
                                                maxZ = pt2.z;
                                            }
                                        }
									}
								}
								
								if(loadWaveform)
								{
									if((*iterPulses)->numOfReceivedBins > 0)
									{
										for(boost::uint_fast16_t n = 0; n < (*iterPulses)->numOfReceivedBins; ++n)
										{
											if(((float)(*iterPulses)->received[n]) > (*iterPulses)->receiveWaveNoiseThreshold)
											{
												if(this->zFieldType == topoHeightType)
                                                {
                                                    SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, ((*iterPulses)->rangeToWaveformStart+((((float)(n*spdFile->getTemporalBinSpacing()))/2)*SPD_SPEED_OF_LIGHT_NS)), (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->z0, &tempX, &tempY, &tempZ);
                                                }
                                                else if(this->zFieldType == normHeightType)
                                                {
                                                    SPDConvertToCartesian((*iterPulses)->zenith, (*iterPulses)->azimuth, ((*iterPulses)->rangeToWaveformStart+((((float)(n*spdFile->getTemporalBinSpacing()))/2)*SPD_SPEED_OF_LIGHT_NS)), (*iterPulses)->x0, (*iterPulses)->y0, (*iterPulses)->h0, &tempX, &tempY, &tempZ);
                                                }
												
												SimpleColour3DPoint pt;
												pt.x = tempX - xMidValue;
												pt.y = tempY - yMidValue;
												pt.z = tempZ;
												pt.ptSize = 1;
                                                pt.clrVal = (((float)(*iterPulses)->received[n])*(*iterPulses)->receiveWaveGain)+(*iterPulses)->receiveWaveOffset;
												waveforms->push_back(pt);
												
												zValues.push_back(pt.z);
												if(firstZVal)
												{
													minZ = pt.z;
													maxZ = pt.z;
													firstZVal = false;
												}
												else
												{
													if(pt.z < minZ)
													{
														minZ = pt.z;
													}
													else if(pt.z > maxZ)
													{
														maxZ = pt.z;
													}
												}
											}
										}
									}
								}
							}
							else if((spdFile->getDecomposedPtDefined() == SPD_TRUE) |
									(spdFile->getDiscretePtDefined() == SPD_TRUE))
							{
								// Point data only.
								if(loadPoints)
								{
                                    if((*iterPulses)->numberOfReturns > 0)
                                    {
                                        for(unsigned int n = 0; n < (*iterPulses)->pts->size(); ++n)
                                        {
                                            if((this->grdReturnsOnly && ((*iterPulses)->pts->at(n)->classification == SPD_GROUND)) | (!this->grdReturnsOnly))
                                            {
                                                SimpleColour3DPoint pt;
                                                pt.x = (*iterPulses)->pts->at(n)->x - xMidValue;
                                                pt.y = (*iterPulses)->pts->at(n)->y - yMidValue;
                                                
                                                if(this->zFieldType == topoHeightType)
                                                {
                                                    pt.z = (*iterPulses)->pts->at(n)->z;
                                                }
                                                else if(this->zFieldType == normHeightType)
                                                {
                                                    pt.z = (*iterPulses)->pts->at(n)->height;
                                                }                                        
                                                
                                                pt.ptSize = 1;
                                                
                                                zValues.push_back(pt.z);
                                                if(firstZVal)
                                                {
                                                    minZ = pt.z;
                                                    maxZ = pt.z;
                                                    firstZVal = false;
                                                }
                                                else
                                                {
                                                    if(pt.z < minZ)
                                                    {
                                                        minZ = pt.z;
                                                    }
                                                    else if(pt.z > maxZ)
                                                    {
                                                        maxZ = pt.z;
                                                    }
                                                }
                                                
                                                if(clrPtType == classColourType)
                                                {
                                                    if (classDisplay->contains((*iterPulses)->pts->at(n)->classification))
                                                    {
                                                        CatDisplayInfo disInfo = classDisplay->value((*iterPulses)->pts->at(n)->classification);
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                    else 
                                                    {
                                                        CatDisplayInfo disInfo;
                                                        disInfo.pointSize = 1;
                                                        color.setHsvF(float(rand() % 100 + 1)/100, 1, 1, 1);
                                                        disInfo.red = color.redF();
                                                        disInfo.green = color.greenF();
                                                        disInfo.blue = color.blueF();
                                                        classDisplay->insert((*iterPulses)->pts->at(n)->classification, disInfo);
                                                        
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                }
                                                else if(clrPtType == amplitudeColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->amplitudeReturn;
                                                    
                                                    /*
                                                     if(firstClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     maxClrVal = pt.clrVal;
                                                     firstClrVal = false;
                                                     }
                                                     else 
                                                     {
                                                     if(pt.clrVal < minClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     }
                                                     else if(pt.clrVal > maxClrVal)
                                                     {
                                                     maxClrVal = pt.clrVal;
                                                     }
                                                     }
                                                     */
                                                }
                                                else if(clrPtType == rgbColourType)
                                                {
                                                    color.setRed((*iterPulses)->pts->at(n)->red);
                                                    color.setGreen((*iterPulses)->pts->at(n)->green);
                                                    color.setBlue((*iterPulses)->pts->at(n)->blue);
                                                    
                                                    pt.r = color.redF();
                                                    pt.g = color.greenF();
                                                    pt.b = color.blueF();
                                                }
                                                else if(clrPtType == heightColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->height;
                                                    /*
                                                     if(firstClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     maxClrVal = pt.clrVal;
                                                     firstClrVal = false;
                                                     }
                                                     else 
                                                     {
                                                     if(pt.clrVal < minClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     }
                                                     else if(pt.clrVal > maxClrVal)
                                                     {
                                                     maxClrVal = pt.clrVal;
                                                     }
                                                     }
                                                     */
                                                }
                                                else if(clrPtType == returnColourType)
                                                {
                                                    if (returnDisplay->contains((*iterPulses)->pts->at(n)->returnID))
                                                    {
                                                        CatDisplayInfo disInfo = returnDisplay->value((*iterPulses)->pts->at(n)->returnID);
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                    else 
                                                    {
                                                        CatDisplayInfo disInfo;
                                                        disInfo.pointSize = 1;
                                                        color.setHsvF(float(rand() % 100 + 1)/100, 1, 1, 1);
                                                        disInfo.red = color.redF();
                                                        disInfo.green = color.greenF();
                                                        disInfo.blue = color.blueF();
                                                        returnDisplay->insert((*iterPulses)->pts->at(n)->returnID, disInfo);
                                                        
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                }
                                                else if(clrPtType == sourceColourType)
                                                {
                                                    if (sourceDisplay->contains((*iterPulses)->sourceID))
                                                    {
                                                        CatDisplayInfo disInfo = sourceDisplay->value((*iterPulses)->sourceID);
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                    else 
                                                    {
                                                        CatDisplayInfo disInfo;
                                                        disInfo.pointSize = 1;
                                                        color.setHsvF(float(rand() % 100 + 1)/100, 1, 1, 1);
                                                        disInfo.red = color.redF();
                                                        disInfo.green = color.greenF();
                                                        disInfo.blue = color.blueF();
                                                        sourceDisplay->insert((*iterPulses)->sourceID, disInfo);
                                                        
                                                        pt.ptSize = disInfo.pointSize;
                                                        pt.r = disInfo.red;
                                                        pt.g = disInfo.green;
                                                        pt.b = disInfo.blue;
                                                    }
                                                }
                                                else if(clrPtType == elevationColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->z;
                                                    /*
                                                     if(firstClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     maxClrVal = pt.clrVal;
                                                     firstClrVal = false;
                                                     }
                                                     else 
                                                     {
                                                     if(pt.clrVal < minClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     }
                                                     else if(pt.clrVal > maxClrVal)
                                                     {
                                                     maxClrVal = pt.clrVal;
                                                     }
                                                     }
                                                     */
                                                }
                                                else if(clrPtType == widthColourType)
                                                {
                                                    pt.clrVal = (*iterPulses)->pts->at(n)->widthReturn;
                                                    /*
                                                     if(firstClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     maxClrVal = pt.clrVal;
                                                     firstClrVal = false;
                                                     }
                                                     else 
                                                     {
                                                     if(pt.clrVal < minClrVal)
                                                     {
                                                     minClrVal = pt.clrVal;
                                                     }
                                                     else if(pt.clrVal > maxClrVal)
                                                     {
                                                     maxClrVal = pt.clrVal;
                                                     }
                                                     }
                                                     */
                                                }
                                                
                                                points->push_back(pt);
                                            }
                                        }
                                    }
								}
								
								if(loadVectors)
								{
                                    if((*iterPulses)->numberOfReturns > 0)
                                    {
                                        if((*iterPulses)->pts->size() > 1)
                                        {
                                            Simple3DPoint pt1;
                                            pt1.x = (*iterPulses)->pts->front()->x - xMidValue;
                                            pt1.y = (*iterPulses)->pts->front()->y - yMidValue;
                                            if(this->zFieldType == topoHeightType)
                                            {
                                                pt1.z = (*iterPulses)->pts->front()->z;
                                            }
                                            else if(this->zFieldType == normHeightType)
                                            {
                                                pt1.z = (*iterPulses)->pts->front()->height;
                                            } 
                                            lines->push_back(pt1);
                                            Simple3DPoint pt2;
                                            pt2.x = (*iterPulses)->pts->back()->x - xMidValue;
                                            pt2.y = (*iterPulses)->pts->back()->y - yMidValue;
                                            if(this->zFieldType == topoHeightType)
                                            {
                                                pt2.z = (*iterPulses)->pts->back()->z;
                                            }
                                            else if(this->zFieldType == normHeightType)
                                            {
                                                pt2.z = (*iterPulses)->pts->back()->height;
                                            }
                                            lines->push_back(pt2);
                                            
                                            if(firstZVal)
                                            {
                                                minZ = pt1.z;
                                                maxZ = pt1.z;
                                                firstZVal = false;
                                            }
                                            else
                                            {
                                                if(pt1.z < minZ)
                                                {
                                                    minZ = pt1.z;
                                                }
                                                else if(pt1.z > maxZ)
                                                {
                                                    maxZ = pt1.z;
                                                }
                                            }
                                            
                                            if(pt2.z < minZ)
                                            {
                                                minZ = pt2.z;
                                            }
                                            else if(pt2.z > maxZ)
                                            {
                                                maxZ = pt2.z;
                                            }
                                        }
									}
								}
							}
							
							SPDPulseUtils::deleteSPDPulse(*iterPulses); 
							iterPulses = pulses->erase(iterPulses);
						}
					}
					
					zMidValue = minZ + ((maxZ - minZ)/2);
					
					if(zValues.size() > 3)
					{
						sort(zValues.begin(), zValues.end());
						float zMedianVal = zValues.at(zValues.size()/2);
						
						if((zMedianVal - zMidValue) < 0)
						{
							zMidValue = zMedianVal;
						}
					}
										
					if(loadPoints)
					{
                        vector<SimpleColour3DPoint>::iterator iterPts;
                        
                        float normMax = 0;
                        float normMin = 0;
                        float normRange = 0;
                        if(clrNorm)
                        {
                            float maxClrVal = 0;
                            float minClrVal = 0;
                            float meanClrVal = 0;
                            float stdDevClrVal = 0;
                            unsigned long numVals = 0;
                            double sumClrVal = 0;
                            double sumSqDifClrVal = 0;
                            bool firstClrVal = true;
                            
                            for(iterPts = points->begin(); iterPts != points->end(); ++iterPts)
                            {
                                if(firstClrVal)
                                {
                                    maxClrVal = (*iterPts).clrVal;
                                    minClrVal = (*iterPts).clrVal;
                                    firstClrVal = false;
                                }
                                else
                                {
                                    if((*iterPts).clrVal > maxClrVal)
                                    {
                                        maxClrVal = (*iterPts).clrVal;
                                    }
                                    else if((*iterPts).clrVal < minClrVal)
                                    {
                                        minClrVal = (*iterPts).clrVal;
                                    }
                                }
                                
                                sumClrVal += (*iterPts).clrVal;
                                ++numVals;
                            }
                            
                            meanClrVal = sumClrVal/numVals;
                            for(iterPts = points->begin(); iterPts != points->end(); ++iterPts)
                            {
                                sumSqDifClrVal += (((*iterPts).clrVal - meanClrVal)*((*iterPts).clrVal - meanClrVal));
                            }
                            
                            stdDevClrVal = sqrt(sumSqDifClrVal/numVals);
                            
                            normMax = meanClrVal + (stdDevClrVal*2);
                            if(normMax > maxClrVal)
                            {
                                normMax = maxClrVal;
                            }
                            normMin = meanClrVal - (stdDevClrVal*2);
                            if(normMin < minClrVal)
                            {
                                normMin = minClrVal;
                            }
                            normRange = normMax - normMin;
                        }
                        
						float normClrVal = 0;
                        unsigned int normIntVal = 0;
                        
						for(iterPts = points->begin(); iterPts != points->end(); ++iterPts)
						{
							(*iterPts).z -= zMidValue;
							
							if(clrNorm)
							{
								normClrVal = ((*iterPts).clrVal-normMin)/normRange;
                                if(normClrVal < 0)
                                {
                                    normClrVal = 0;
                                }
                                else if(normClrVal > 1)
                                {
                                    normClrVal = 1;
                                }
                                try
                                {
                                    normIntVal = this->colourTable->scaleVal(normClrVal);
                                    color = this->colourTable->findColour(normIntVal);
                                }
                                catch(SPDPointsViewerException &e)
                                {
                                    cerr << "WARNING (Points): " << e.what() << endl;
                                    color = QColor("white");
                                }
                                
								(*iterPts).r = color.redF();
								(*iterPts).g = color.greenF();
								(*iterPts).b = color.blueF();
							}
						}
						
						sort(points->begin(), points->end(), cmpClrPtsSize);
						
						openGLWidget->setPoints(points);
					}
					
					if(loadVectors)
					{
						vector<Simple3DPoint>::iterator iterPts;
						for(iterPts = lines->begin(); iterPts != lines->end(); ++iterPts)
						{
							(*iterPts).z -= zMidValue;
						}
						openGLWidget->setLines(lines);
					}
					
					if(loadWaveform)
					{
                        vector<SimpleColour3DPoint>::iterator iterPts;
                        float normMax = 0;
                        float normMin = 0;
                        float normRange = 0;
                        if(normaliseWaveform)
                        {                            
                            float maxClrVal = 0;
                            float minClrVal = 0;
                            float meanClrVal = 0;
                            float stdDevClrVal = 0;
                            unsigned long numVals = 0;
                            double sumClrVal = 0;
                            double sumSqDifClrVal = 0;
                            bool firstClrVal = true;
                            
                            for(iterPts = waveforms->begin(); iterPts != waveforms->end(); ++iterPts)
                            {
                                if(firstClrVal)
                                {
                                    maxClrVal = (*iterPts).clrVal;
                                    minClrVal = (*iterPts).clrVal;
                                    firstClrVal = false;
                                }
                                else
                                {
                                    if((*iterPts).clrVal > maxClrVal)
                                    {
                                        maxClrVal = (*iterPts).clrVal;
                                    }
                                    else if((*iterPts).clrVal < minClrVal)
                                    {
                                        minClrVal = (*iterPts).clrVal;
                                    }
                                }
                                
                                sumClrVal += (*iterPts).clrVal;
                                ++numVals;
                            }
                            
                            meanClrVal = sumClrVal/numVals;
                            for(iterPts = points->begin(); iterPts != points->end(); ++iterPts)
                            {
                                sumSqDifClrVal += (((*iterPts).clrVal - meanClrVal)*((*iterPts).clrVal - meanClrVal));
                            }
                            
                            stdDevClrVal = sqrt(sumSqDifClrVal/numVals);
                            
                            normMax = meanClrVal + (stdDevClrVal*2);
                            if(normMax > maxClrVal)
                            {
                                normMax = maxClrVal;
                            }
                            normMin = meanClrVal - (stdDevClrVal*2);
                            if(normMin < minClrVal)
                            {
                                normMin = minClrVal;
                            }
                            normRange = normMax - normMin;
                        }
                        else
                        {
                            normMax = 100;
                            normMin = 0;
                            normRange = 100;
                        }
                        
                        float normClrVal = 0;
                        unsigned int normIntVal = 0;
						
						for(iterPts = waveforms->begin(); iterPts != waveforms->end(); ++iterPts)
						{
							(*iterPts).z -= zMidValue;
                            
                            normClrVal = ((*iterPts).clrVal-normMin)/normRange;
                            if(normClrVal < 0)
                            {
                                normClrVal = 0;
                            }
                            else if(normClrVal > 1)
                            {
                                normClrVal = 1;
                            }
                            try
                            {
                                normIntVal = this->colourTable->scaleVal(normClrVal);
                                color = this->colourTable->findColour(normIntVal);
                            }
                            catch(SPDPointsViewerException &e)
                            {
                                cerr << "WARNING (waveform): " << e.what() << endl;
                                color = QColor("white");
                            }
                            
                            (*iterPts).r = color.redF();
                            (*iterPts).g = color.greenF();
                            (*iterPts).b = color.blueF();
						}
						openGLWidget->setWaveforms(waveforms);
					}
				}
			}
			
			if(loadDTM)
			{
				unsigned long numTriDTMVertInRow = 0;
				unsigned long numTrisDTMInRow = 0;
				unsigned long numTriDTMRows = 0;
				GLfloat **coordsXTriDTM = NULL;
				GLfloat **coordsYTriDTM = NULL;
				GLfloat **coordsZTriDTM = NULL;
				GLfloat **normXTriDTM = NULL;
				GLfloat **normYTriDTM = NULL;
				GLfloat **normZTriDTM = NULL;
				
				GDALAllRegister();					
				GDALDataset *inGDALImage = (GDALDataset *) GDALOpenShared(this->inputDTM.c_str(), GA_ReadOnly);
				
				unsigned int numImgBands = inGDALImage->GetRasterCount();
				if(numImgBands > 0)
				{
					unsigned int imgWidth = inGDALImage->GetRasterXSize();
					unsigned int imgHeight = inGDALImage->GetRasterYSize();
					
					double transform[6];
					inGDALImage->GetGeoTransform(transform);
					double imgRes = transform[1];
					double imgGeoBBoxTLX = transform[0];
					double imgGeoBBoxTLY = transform[3];
					double imgGeoBBoxBRX = transform[0] + (((float)imgWidth)*imgRes);
					double imgGeoBBoxBRY = transform[3] - (((float)imgHeight)*imgRes);
										
					if((bboxTLX > imgGeoBBoxTLX) & (bboxTLY < imgGeoBBoxTLY) & (bboxBRX < imgGeoBBoxBRX) & (bboxBRY > imgGeoBBoxBRY))
					{
						// Find image pixel coordinates
						unsigned int imgBBoxTLX = static_cast<unsigned int>((bboxTLX - imgGeoBBoxTLX) / imgRes);
						unsigned int imgBBoxTLY = static_cast<unsigned int>(((imgGeoBBoxTLY - bboxTLY) / imgRes)+0.5);
						unsigned int imgBBoxBRX = static_cast<unsigned int>(((bboxBRX - imgGeoBBoxTLX) / imgRes)+0.5);
						unsigned int imgBBoxBRY = static_cast<unsigned int>((imgGeoBBoxTLY - bboxBRY) / imgRes);
						
						unsigned int imgPxlWidthRange = imgBBoxBRX - imgBBoxTLX;
						unsigned int imgPxlHeightRange = imgBBoxBRY - imgBBoxTLY;
						
						numTriDTMVertInRow = imgPxlWidthRange*2;
						numTrisDTMInRow = (imgPxlWidthRange-1)*2;
						numTriDTMRows = imgPxlHeightRange-1;
						
						coordsXTriDTM = new GLfloat*[numTriDTMRows];
						coordsYTriDTM = new GLfloat*[numTriDTMRows];
						coordsZTriDTM = new GLfloat*[numTriDTMRows];
						
						normXTriDTM = new GLfloat*[numTriDTMRows];
						normYTriDTM = new GLfloat*[numTriDTMRows];
						normZTriDTM = new GLfloat*[numTriDTMRows];
						
						for(unsigned int i = 0; i < numTriDTMRows; ++i)
						{
							coordsXTriDTM[i] = new GLfloat[numTriDTMVertInRow];
							coordsYTriDTM[i] = new GLfloat[numTriDTMVertInRow];
							coordsZTriDTM[i] = new GLfloat[numTriDTMVertInRow];
							
							normXTriDTM[i] = new GLfloat[numTrisDTMInRow];
							normYTriDTM[i] = new GLfloat[numTrisDTMInRow];
							normZTriDTM[i] = new GLfloat[numTrisDTMInRow];
						}
						
						GDALRasterBand *dtmImgBand = inGDALImage->GetRasterBand(1);
						float *imgData1 = (float *) CPLMalloc(sizeof(float)*imgPxlWidthRange);
						float *imgData2 = (float *) CPLMalloc(sizeof(float)*imgPxlWidthRange);
						
						double startEastings = imgGeoBBoxTLX + (imgRes * imgBBoxTLX) + (imgRes/2);
						double startNorthings = imgGeoBBoxTLY - (imgRes * imgBBoxTLY) - (imgRes/2);
						double currentNorthing = startNorthings - imgRes;
						double currentEasting = startEastings;
						
						unsigned long coordTriCount = 0;
						unsigned long triRowCount = 0;
						
						dtmImgBand->RasterIO(GF_Read, imgBBoxTLX, imgBBoxTLY, imgPxlWidthRange, 1, imgData1, imgPxlWidthRange, 1, GDT_Float32, 0, 0);
						
						unsigned int feedback = imgPxlHeightRange/10;
						
						for(unsigned int i = 1; i < imgPxlHeightRange; ++i)
						{
							if((imgPxlHeightRange > 10) && (i % feedback == 0))
							{
								emit valueChanged(feedbackVal++);
							}
							
							dtmImgBand->RasterIO(GF_Read, imgBBoxTLX, (i+imgBBoxTLY), imgPxlWidthRange, 2, imgData2, imgPxlWidthRange, 1, GDT_Float32, 0, 0);
							currentEasting = startEastings;
							coordTriCount = 0;
							for(unsigned int j = 0; j < imgPxlWidthRange; ++j)
							{
								coordsXTriDTM[triRowCount][coordTriCount] = currentEasting - xMidValue;
								coordsYTriDTM[triRowCount][coordTriCount] = (currentNorthing + imgRes) - yMidValue;
								coordsZTriDTM[triRowCount][coordTriCount] = imgData1[j] - zMidValue;
								++coordTriCount;
								
								
								coordsXTriDTM[triRowCount][coordTriCount] = currentEasting - xMidValue;
								coordsYTriDTM[triRowCount][coordTriCount] = currentNorthing - yMidValue;
								coordsZTriDTM[triRowCount][coordTriCount] = imgData2[j] - zMidValue;
								++coordTriCount;
								
								imgData1[j] = imgData2[j];
								currentEasting += imgRes;
							}
							currentNorthing -= imgRes;
							++triRowCount;
						}
						
						CPLFree(imgData1);
						CPLFree(imgData2);
						
						GLfloat prev2X = 0;
						GLfloat prev2Y = 0;
						GLfloat prev2Z = 0;
						
						GLfloat prev1X = 0;
						GLfloat prev1Y = 0;
						GLfloat prev1Z = 0;
						
						GLfloat currX = 0;
						GLfloat currY = 0;
						GLfloat currZ = 0;
						
						pt3dfloat p,p1,p2;
						pt3dfloat normVec;
						
						unsigned long triNormCount = 0;
						
						for(unsigned int i = 0; i < numTriDTMRows; ++i)
						{
							prev2X = coordsXTriDTM[i][0];
							prev2Y = coordsYTriDTM[i][0];
							prev2Z = coordsZTriDTM[i][0];
							
							prev1X = coordsXTriDTM[i][1];
							prev1Y = coordsYTriDTM[i][1];
							prev1Z = coordsZTriDTM[i][1];
							
							triNormCount = 0;
							
							for(unsigned int j = 2; j < numTrisDTMInRow; ++j)
							{
								currX = coordsXTriDTM[i][j];
								currY = coordsYTriDTM[i][j];
								currZ = coordsZTriDTM[i][j];
								
								if((j % 2) == 0)
								{
									p.x = prev2X;
									p.y = prev2Y;
									p.z = prev2Z;

									p1.x = prev1X;
									p1.y = prev1Y;
									p1.z = prev1Z;

									p2.x = currX;
									p2.y = currY;
									p2.z = currZ;												
								}
								else 
								{
									p.x = prev2X;
									p.y = prev2Y;
									p.z = prev2Z;

									p1.x = currX;
									p1.y = currY;
									p1.z = currZ;

									p2.x = prev1X;
									p2.y = prev1Y;
									p2.z = prev1Z;
								}
								
								normVec = this->calcNormalVec(p, p1, p2);
								
								normXTriDTM[i][triNormCount] = normVec.x;
								normYTriDTM[i][triNormCount] = normVec.y;
								normZTriDTM[i][triNormCount] = normVec.z;
								++triNormCount;
								
								prev2X = prev1X;
								prev2Y = prev1Y;
								prev2Z = prev1Z;
								
								prev1X = currX;
								prev1Y = currY;
								prev1Z = currZ;
							}
						}
					}
				}
				
				GDALClose(inGDALImage);
				GDALDestroyDriverManager();
				
				openGLWidget->setDTMSurface(numTriDTMVertInRow, numTrisDTMInRow, numTriDTMRows, coordsXTriDTM, coordsYTriDTM, coordsZTriDTM, normXTriDTM, normYTriDTM, normZTriDTM);
			}
			
			if(loadTris)
			{
				//Not Implemented
			}
			
			if(loadSHP)
			{
                OGRRegisterAll();
                
                vector<Simple3DPoint> *shplines = new vector<Simple3DPoint>();
                
                float minZVecLineVal = ((zMidValue - minZ)*2) * (-1);
                float maxZVecLineVal = ((maxZ - zMidValue)*2);
                
                //cout << "Line z values = [" << minZVecLineVal << "," << maxZVecLineVal << "]\n";
                
                string shpFileLayerName = this->getLayerName(inputSHP);
                
                //cout << "Shapefile layer " << shpFileLayerName << endl;
                
                OGRDataSource *inputSHPDS = OGRSFDriverRegistrar::Open(inputSHP.c_str(), FALSE);
				if(inputSHPDS == NULL)
				{
                    emit errorMessages("Could not open shapefile");
                    return;
				}
				OGRLayer *inputSHPLayer = inputSHPDS->GetLayerByName(shpFileLayerName.c_str());
				if(inputSHPLayer == NULL)
				{
                    emit errorMessages("Could not open shapefile layer.");
                    return;
				}

                OGRPoint *point = NULL;
                OGRGeometry *geometry = NULL;
                OGRFeature *feature = NULL;
                
                inputSHPLayer->ResetReading();
                while( (feature = inputSHPLayer->GetNextFeature()) != NULL )
                {
                    geometry = feature->GetGeometryRef();
                    if( geometry != NULL && wkbFlatten(geometry->getGeometryType()) == wkbPoint )
                    {
                        point = (OGRPoint *) geometry;
                        
                        if((point->getX() > bboxTLX) &
                           (point->getY() < bboxTLY) &
                           (point->getX() < bboxBRX) &
                           (point->getY() > bboxBRY))
                        {
                            Simple3DPoint pt1;
                            pt1.x = point->getX() - xMidValue;
                            pt1.y = point->getY() - yMidValue;
                            pt1.z = minZVecLineVal;
                            shplines->push_back(pt1);
                            
                            Simple3DPoint pt2;
                            pt2.x = point->getX() - xMidValue;
                            pt2.y = point->getY() - yMidValue;
                            pt2.z = maxZVecLineVal;
                            shplines->push_back(pt2);
                        }
                    }
                    else
                    {
                        emit errorMessages("Only point data type shapefiles are supported.");
                        return;
                    }
                    OGRFeature::DestroyFeature( feature );
                }
                openGLWidget->setSHPLines(shplines);
                OGRCleanupAll();
			}
		}
		catch (SPDException &e) 
		{
			emit errorMessages(	QString::fromStdString(e.what()));
			return;
		}
		
	}
	
	void SPDPointsViewerLoad3DData::normaliseVec(pt3dfloat *p)
	{
		double length;
		
		length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
		if (!compare_double(length, 0))
		{
			p->x /= length;
			p->y /= length;
			p->z /= length;
		} 
		else 
		{
			p->x = 0;
			p->y = 0;
			p->z = 0;
		}
	}
	
	pt3dfloat SPDPointsViewerLoad3DData::calcNormalVec(pt3dfloat p,pt3dfloat p1,pt3dfloat p2)
	{
		pt3dfloat n,pa,pb;
		
		pa.x = p1.x - p.x;
		pa.y = p1.y - p.y;
		pa.z = p1.z - p.z;
		pb.x = p2.x - p.x;
		pb.y = p2.y - p.y;
		pb.z = p2.z - p.z;
		this->normaliseVec(&pa);
		this->normaliseVec(&pb);
		
		n.x = pa.y * pb.z - pa.z * pb.y;
		n.y = pa.z * pb.x - pa.x * pb.z;
		n.z = pa.x * pb.y - pa.y * pb.x;
		this->normaliseVec(&n);
		
		return(n);
	}
    
    string SPDPointsViewerLoad3DData::getLayerName(string filepath)
	{
		int strSize = filepath.size();
		int lastSlash = 0;
		for(int i = 0; i < strSize; i++)
		{
			if(filepath.at(i) == '/')
			{
				lastSlash = i;
			}
		}
		string filename = filepath.substr(lastSlash+1);
		
		strSize = filename.size();
		int lastpt = 0;
		for(int i = 0; i < strSize; i++)
		{
			if(filename.at(i) == '.')
			{
				lastpt = i;
			}
		}
		
		string layerName = filename.substr(0, lastpt);
		return layerName;		
	}
	
	SPDPointsViewerLoad3DData::~SPDPointsViewerLoad3DData()
	{
		delete[] bbox;
	}
	
}

