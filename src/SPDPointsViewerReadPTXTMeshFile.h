/*
 *  SPDPointsViewerReadPTXTMeshFile.h
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

#ifndef SPDPointsViewerReadPTXTMeshFile_H
#define SPDPointsViewerReadPTXTMeshFile_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <QGLWidget>

#include "SPDPointsViewerException.h"

using namespace std;

namespace spdpointsviewer
{
	typedef struct 
	{
		GLfloat x,y,z;
	} pt3dfloat;
	
	class SPDPointsViewerReadPTXTMeshFile
	{
	public:
		SPDPointsViewerReadPTXTMeshFile();
		unsigned long countNumVertex(string inputFile)throw(SPDPointsViewerException);
		void readInputFile(string inputFile, unsigned long numVertex, GLfloat *coordsXTri, GLfloat *coordsYTri, GLfloat *coordsZTri, float xOff, float yOff, float zOff)throw(SPDPointsViewerException);
		~SPDPointsViewerReadPTXTMeshFile();
	private:
		void tokenizeString(string line, char token, vector<string> *tokens, bool ignoreDuplicateTokens);
		double strtodouble(string inValue);
		bool lineStart(string line, char token);
	};
}

#endif


