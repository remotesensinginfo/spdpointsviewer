/*
 *  SPDPointsViewerReadPTXTMeshFile.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 13/08/2010.
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

#include "SPDPointsViewerReadPTXTMeshFile.h"



namespace spdpointsviewer
{

	
	SPDPointsViewerReadPTXTMeshFile::SPDPointsViewerReadPTXTMeshFile()
	{
		
	}
	
	unsigned long SPDPointsViewerReadPTXTMeshFile::countNumVertex(string inputFile) 
	{
		unsigned long numVertex = 0;
		ifstream openInFile;
		openInFile.open(inputFile.c_str());
		if(!openInFile.is_open())
		{
			throw SPDPointsViewerException("Could not open input text file.");
		}
		else
		{
			string strLine;
			openInFile.seekg(ios_base::beg);
			getline(openInFile, strLine);
			if(strLine != "#triangle3d")
			{
				openInFile.close();
				throw SPDPointsViewerException("Could not parse file as format incorrect.");
			}
			
			openInFile.seekg(ios_base::beg);
			while(!openInFile.eof())
			{
				getline(openInFile, strLine);
				if(this->lineStart(strLine, '#'))
				{
					// IGNORE HEADER/METADATA
				}
				else if(strLine.size() == 0)
				{
					// IGNORE BLANK LINES
				}
				else
				{
					++numVertex;
				}
			}
		}
		openInFile.close();
		
		return numVertex;
	}
	
	void SPDPointsViewerReadPTXTMeshFile::readInputFile(string inputFile, unsigned long numVertex, GLfloat *coordsXTri, GLfloat *coordsYTri, GLfloat *coordsZTri, float xOff, float yOff, float zOff) 
	{
		ifstream openInFile;
		openInFile.open(inputFile.c_str());
		if(!openInFile.is_open())
		{
			throw SPDPointsViewerException("Could not open input text file.");
		}
		else
		{
			string strLine;
			vector<string> *tokens = new vector<string>();
			openInFile.seekg(ios_base::beg);
			getline(openInFile, strLine);
			if(strLine != "#triangle3d")
			{
				openInFile.close();
				throw SPDPointsViewerException("Could not parse file as format incorrect.");
			}
			
			if((numVertex % 3) != 0)
			{
				throw SPDPointsViewerException("The number of vertices in the input file is not in groups of 3.");
			}
			
			
			pt3dfloat ptA, ptB, ptC;
			
			ptA.x = 0;
			ptA.y = 0;
			ptA.z = 0;
			
			ptB.x = 0;
			ptB.y = 0;
			ptB.z = 0;
			
			ptC.x = 0;
			ptC.y = 0;
			ptC.z = 0;
			
			//cout << "xOff = " << xOff << endl;
			//cout << "yOff = " << yOff << endl;
			//cout << "zOff = " << zOff << endl;
			
			unsigned int ptCount = 0;
			unsigned long vertexCount = 0;
			openInFile.seekg(ios_base::beg);
			while(!openInFile.eof())
			{
				getline(openInFile, strLine);
				if(this->lineStart(strLine, '#'))
				{
					// IGNORE HEADER/METADATA
				}
				else if(strLine.size() == 0)
				{
					// IGNORE BLANK LINES
				}
				else
				{
					//cout << strLine << endl;
					this->tokenizeString(strLine, ',', tokens, true);
					if(tokens->size() != 3)
					{
						openInFile.close();
						throw SPDPointsViewerException("Error while parsing. File format is incorrect for triangle3d file.");
					}
					
					if(vertexCount > numVertex-3)
					{
						throw SPDPointsViewerException("Vertex arrays are too small.");
					}
					
					//cout << vertexCount << " [" << tokens->at(0) << "," << tokens->at(1) << "," << tokens->at(2) << "]\n";
					
					if(ptCount == 0)
					{
						ptA.x = this->strtodouble(tokens->at(0));
						ptA.y = this->strtodouble(tokens->at(1));
						ptA.z = this->strtodouble(tokens->at(2));
						//cout << vertexCount << " [" << ptA.x << "," << ptA.y << "," << ptA.z << "]\n";
						++ptCount;
					}
					else if(ptCount == 1)
					{
						ptB.x = this->strtodouble(tokens->at(0));
						ptB.y = this->strtodouble(tokens->at(1));
						ptB.z = this->strtodouble(tokens->at(2));
						//cout << vertexCount << " [" << ptB.x << "," << ptB.y << "," << ptB.z << "]\n";
						++ptCount;
					}
					else 
					{
						ptC.x = this->strtodouble(tokens->at(0));
						ptC.y = this->strtodouble(tokens->at(1));
						ptC.z = this->strtodouble(tokens->at(2));
						//cout << vertexCount << " [" << ptC.x << "," << ptC.y << "," << ptC.z << "]\n";
						
						coordsXTri[vertexCount] = ptA.x - xOff;
						coordsYTri[vertexCount] = ptA.y - yOff;
						coordsZTri[vertexCount] = ptA.z - zOff;
						//cout << vertexCount << " [" << coordsXTri[vertexCount] << "," << coordsYTri[vertexCount] << "," << coordsZTri[vertexCount] << "]\n";
						++vertexCount;
						
						coordsXTri[vertexCount] = ptB.x - xOff;
						coordsYTri[vertexCount] = ptB.y - yOff;
						coordsZTri[vertexCount] = ptB.z - zOff;
						//cout << vertexCount << " [" << coordsXTri[vertexCount] << "," << coordsYTri[vertexCount] << "," << coordsZTri[vertexCount] << "]\n";
						++vertexCount;
						
						coordsXTri[vertexCount] = ptC.x - xOff;
						coordsYTri[vertexCount] = ptC.y - yOff;
						coordsZTri[vertexCount] = ptC.z - zOff;
						//cout << vertexCount << " [" << coordsXTri[vertexCount] << "," << coordsYTri[vertexCount] << "," << coordsZTri[vertexCount] << "]\n";
						++vertexCount;
						
						ptCount = 0;
					}					
					tokens->clear();
				}
			}
			delete tokens;
		}
		openInFile.close();
	}
		
	void SPDPointsViewerReadPTXTMeshFile::tokenizeString(string line, char token, vector<string> *tokens, bool ignoreDuplicateTokens)
	{
		string word;
		int start = 0;
		int lineLength = line.length();
		for(int i = 0; i < lineLength; i++)
		{
			if(line.at(i) == token)
			{
				word = line.substr(start, i-start);
				if(ignoreDuplicateTokens)
				{
					if(word.length() > 0)
					{
						tokens->push_back(word);
					}
				}
				else 
				{
					tokens->push_back(word);
				}
				
				
				
				
				start = start + i-start+1;
			}
		}
		word = line.substr(start);
		tokens->push_back(word);
	}
	
	bool SPDPointsViewerReadPTXTMeshFile::lineStart(string line, char token)
	{
		int lineLength = line.length();
		for(int i = 0; i < lineLength; i++)
		{
			if((line.at(i) == ' ') | (line.at(i) == '\t') | (line.at(i) == '\n'))
			{
				// spaces and tabs at the beginning of a line can be ignored.
			}
			else if(line.at(i) == token)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	
	double SPDPointsViewerReadPTXTMeshFile::strtodouble(string inValue)
	{
		istringstream instr(inValue);
		double doubleVal;
		instr >> doubleVal;
		return doubleVal;
	}
	
	SPDPointsViewerReadPTXTMeshFile::~SPDPointsViewerReadPTXTMeshFile()
	{
		
	}

}

