/*
 *  SPDPointsViewerLoadOverviewImage.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 12/12/2010.
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

#include "SPDPointsViewerLoadOverviewImage.h"

namespace spdpointsviewer
{
	
	SPDPointsViewerLoadOverviewImage::SPDPointsViewerLoadOverviewImage(SPDFile *spdFile)
	{
		this->spdFile = spdFile;
		this->imageCreated = true;
	}
	
	void SPDPointsViewerLoadOverviewImage::run()
	{
		SPDFileIncrementalReader spdIncReader;
		
		outImage = new QImage(spdFile->getNumberBinsX(), spdFile->getNumberBinsY(), QImage::Format_Indexed8);
		
		spdIncReader.open(spdFile);
		float *imageRow = new float[spdFile->getNumberBinsX()];
		
		float minVal = 0;
		float maxVal = 0;
		bool first = true;
				
		for(unsigned int i = 0; i < spdFile->getNumberBinsY(); ++i)
		{
			spdIncReader.readQKRow(imageRow, i);
			for(unsigned int j = 0; j < spdFile->getNumberBinsX(); ++j)
			{
				if(imageRow[j] > 0)
				{
					if(first)
					{
						minVal = imageRow[j];
						maxVal = imageRow[j];
						first = false;
					}
					else if(imageRow[j] < minVal)
					{
						minVal = imageRow[j];
					}
					else if(imageRow[j] > maxVal)
					{
						maxVal = imageRow[j];
					}
				}
			}
			emit valueChanged(i);
		}
				
		float valRange = maxVal - minVal;
		float stretchFactor = valRange/255;
		
		float hue = 0.0;
		QVector<QRgb> colors;
		QColor color = QColor(0, 0, 0, 255);
		for(int i = 0; i < 256; ++i)
		{
			if(i == 0)
			{
				color.setHsvF(0, 0, 0, 1.0);
				colors.push_back(color.rgb());
			}
			else 
			{
				hue = float(i)/255;
				color.setHsvF(hue, 1, 1, 1.0);
				colors.push_back(color.rgb());
			}			
		}
		
		
		
		outImage->setColorTable(colors);
		
		unsigned int pxlVal = 0;
		
		for(unsigned int i = 0; i < spdFile->getNumberBinsY(); ++i)
		{
			spdIncReader.readQKRow(imageRow, i);
			for(unsigned int j = 0; j < spdFile->getNumberBinsX(); ++j)
			{
				if(compare_float(imageRow[j], 0))
				{
					outImage->setPixel(j, i, 0);
				}
				else
				{
					pxlVal = static_cast<unsigned int>(((imageRow[j]-minVal)/stretchFactor));
					outImage->setPixel(j, i, pxlVal);
				}
			}
			emit valueChanged(i+spdFile->getNumberBinsY());
		}		
	}
	
	QImage* SPDPointsViewerLoadOverviewImage::getImage()throw(SPDPointsViewerException)
	{
		if(imageCreated)
		{
			return outImage;
		}
		throw SPDPointsViewerException("Image has not been created.");
	}
	
	SPDFile* SPDPointsViewerLoadOverviewImage::getSPDFile()
	{
		return spdFile;
	}
	
	SPDPointsViewerLoadOverviewImage::~SPDPointsViewerLoadOverviewImage()
	{
		
	}
	
}