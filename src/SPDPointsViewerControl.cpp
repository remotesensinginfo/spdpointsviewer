/*
 *  SPDPointsViewerControl.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 04/08/2010.
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

#include "SPDPointsViewerControl.h"
#include <ctime>

namespace spdpointsviewer
{
	
	SPDPointsViewer3DControlObj::SPDPointsViewer3DControlObj(SPDPointsViewer3DWidget *openGLWidget, bool singleIteration, bool screenshots, QString outputPath, float degreeMove)
	{
		this->openGLWidget = openGLWidget;
		this->singleIteration = singleIteration;
		this->screenshots = screenshots;
		this->outputPath = outputPath;
		continueLoop = false;
		this->degreeMove = degreeMove;
	}

	void SPDPointsViewer3DControlObj::reset(bool singleIteration, bool screenshots, QString outputPath, float degreeMove)
	{
		this->singleIteration = singleIteration;
		this->screenshots = screenshots;
		this->outputPath = outputPath;
		continueLoop = false;
		this->degreeMove = degreeMove;
	}

	void SPDPointsViewer3DControlObj::run()
	{
		continueLoop = true;
		GLfloat zRot = 0;
		QString png = ".png";
		QString outFile;
		outputPath = outputPath + "/";
		int imageCounter = 0;
		bool first = true;
		while(continueLoop)
		{
			this->openGLWidget->setZRotation(zRot);
			this->wait(0.1);
			zRot += degreeMove;
			
			if(singleIteration && (zRot > 361))
			{
				continueLoop = false;
			}
			
			if(screenshots & !first)
			{
				outFile = outputPath + QString::number(imageCounter, 10) + png;
				QImage image = openGLWidget->grabFrameBuffer(true);
				image.save(outFile, "PNG", -1);
				++imageCounter;
			}
			if(first)
			{
				first = false;
			}
		}
	}

	void SPDPointsViewer3DControlObj::wait(float secs)
	{
		clock_t endwait;
		endwait = clock() + secs * CLOCKS_PER_SEC ;
		while (clock() < endwait) {}
	}

	void SPDPointsViewer3DControlObj::setContinueLoop(bool continueLoop)
	{
		this->continueLoop = continueLoop;
	}

}
