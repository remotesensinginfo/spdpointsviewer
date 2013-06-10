/*
 *  SPDPointsViewerCommon.h
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

#ifndef SPDPointsViewerCommon_H
#define SPDPointsViewerCommon_H

#include <string>

using namespace std;

namespace spdpointsviewer
{
    struct Simple3DPoint 
	{
		float x;
		float y;
		float z;
	};
	
	struct SimpleColour3DPoint 
	{
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
		float ptSize;
		float clrVal;
	};
    
    enum ColourPtsType
	{
		classColourType = 0,
		amplitudeColourType = 1,
		rgbColourType = 2,
		heightColourType = 3,
		returnColourType = 4,
		sourceColourType = 5,
		elevationColourType = 6,
		widthColourType = 7
	};
    
    enum ZFieldType
	{
		topoHeightType = 0,
		normHeightType = 1
	};
	
	struct CatDisplayInfo 
	{
		float pointSize;
		float red;
		float green;
		float blue;
	};
	
	inline bool cmpClrPtsSize( SimpleColour3DPoint a, SimpleColour3DPoint b ) 
	{
		return a.ptSize > b.ptSize;
	};
    
    
}


#endif


