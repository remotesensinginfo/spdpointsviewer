/*
 *  SPDPointsViewerControl.h
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

#ifndef SPDPointsViewerControl_H
#define SPDPointsViewerControl_H

#include <iostream>
#include <string>

#include <QtCore>

#include "SPDPointsViewer3DWidget.h"

using namespace std;

namespace spdpointsviewer
{
	class SPDPointsViewer3DControlObj : public QThread
	{
		Q_OBJECT
	public:
		SPDPointsViewer3DControlObj(SPDPointsViewer3DWidget *openGLWidget, bool singleIteration, bool screenshots, QString outputPath, float degreeMove);
		void reset(bool singleIteration, bool screenshots, QString outputPath, float degreeMove);
		void run();
		void wait(float secs);
		void setContinueLoop(bool continueLoop);
	private:
		SPDPointsViewer3DWidget *openGLWidget;
		bool singleIteration;
		bool screenshots;
		QString outputPath;
		bool continueLoop;
		float degreeMove;
	};
}

#endif


