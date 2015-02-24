/*
 *  SPDPointsViewerCreateOverviewImage.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 23/08/2010.
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

#include "SPDPointsViewerCreateOverviewImage.h"

namespace spdpointsviewer
{

	SPDPointsViewerCreateOverviewImage::SPDPointsViewerCreateOverviewImage(): pointsViewer(NULL)
	{
		
	}
	
	void SPDPointsViewerCreateOverviewImage::setPointViewer(SPDPointsViewer *pointsViewer)
	{
		this->pointsViewer = pointsViewer;
		
		// Check if we have a file waiting
		if (this->pointsViewer != NULL && !nextFile.isEmpty())
		{
			this->loadSPDFile(nextFile);
			nextFile = "";
		}
	}
	
	void SPDPointsViewerCreateOverviewImage::loadSPDFile(QString file)
	{
		if(pointsViewer != NULL)
		{
			pointsViewer->loadSPDFile(file);
		}
		else
		{
			nextFile = file;
		}
	}

	
}


