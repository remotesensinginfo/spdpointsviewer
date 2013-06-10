/*
 *  SPDPointsViewer3DWidget.h
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 01/08/2010.
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

#ifndef SPDPointsViewer3DWidget_H
#define SPDPointsViewer3DWidget_H

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include <math.h>

#include <QtGui>
#include <QGLWidget>

#include "SPDPointsViewerDisplayProfile.h"
#include "SPDPointsViewerReadPTXTMeshFile.h"
#include "SPDPointsViewerCommon.h"

#include "spd/SPDCommon.h"

#define GL_PI 3.1415f

using namespace std;
using namespace spdlib;

namespace spdpointsviewer
{	
	class SPDPointsViewer3DWidget : public QGLWidget
	{
		Q_OBJECT
		
	public:
		SPDPointsViewer3DWidget(QWidget *parent = 0);

		void setXRotation(GLfloat xRot);
		void setYRotation(GLfloat yRot);
		void setZRotation(GLfloat zRot);
		
		void setXShift(GLfloat xShift);
		void setYShift(GLfloat yShift);
		void setZShift(GLfloat zShift);
		
		void setRange(GLfloat range);
		
		void reset3DTrans();
		void clearData();
				
		void setBGColour(QColor bgColour);
		QColor* getBGColour();
		
		void setPointSizeMulti(float sizeMulti);
		
		void setPoints(vector<SimpleColour3DPoint> *points);
		void setShowPoints(bool showPoints);
		bool getShowPoints();
		
		void setLineColour(QColor *lineColour);
		QColor* getLineColour();
		void setLines(vector<Simple3DPoint> *lines);
		void setShowLines(bool showLines);
		bool getShowLines();
		
		void setWaveforms(vector<SimpleColour3DPoint> *waveforms);
		void setShowWaveforms(bool showWaveforms);
		bool getShowWaveforms();
		
		void setDTMSurface(unsigned long numTriDTMVertInRow, unsigned long numTrisDTMInRow, unsigned long numTriDTMRows, GLfloat **coordsXTriDTM, GLfloat **coordsYTriDTM, GLfloat **coordsZTriDTM, GLfloat **normXTriDTM, GLfloat **normYTriDTM, GLfloat **normZTriDTM);
		void setDisplayDTM(bool displayDTM);
		bool getDisplayDTM();
		
		void setDTMColour(QColor dtmColour);
		QColor* getDTMColour();

		void setShowWireframe(bool showWireframe);
		bool showWireframe();
		
		void setUseLighting(bool useLighting);
		bool useLighting();
		
		void setSHPLineColour(QColor *shpLineColour);
		QColor* getSPDLineColour();
		void setSHPLines(vector<Simple3DPoint> *lines);
		void setShowSHP(bool showSHP);
		bool showSHP();

		void setDisplayTriangles(bool displayTriangles);
		bool getDisplayTriangles();
		
		void updateView();
		
		void setGenerateProfile(bool generateProfile);
		
		void savePlotAsPDF(QString filepath);
		
		void setShowTriangles(bool showTris);
		bool showTriangles();
		
		~SPDPointsViewer3DWidget();
	protected:
		void initializeGL();
		void resizeGL(int widthIn, int heightIn);
		void paintGL();
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);
	private:
		void draw();
		
		GLfloat rotationX;
		GLfloat rotationY;
		GLfloat rotationZ;
		GLfloat shiftX;
		GLfloat shiftY;
		GLfloat shiftZ;
		GLfloat nRange;
		
		QPoint lastPos;
		
		unsigned int heightStored;
		unsigned int widthStored;
		
		float pointSizeMulti;
		
		QColor *bgColor;
				
		bool dataRead;
		
		QColor *lineColor;
		vector<Simple3DPoint> *lines;
		bool showLines;
		bool linesRead;
		
		vector<SimpleColour3DPoint> *points;
		bool showPoints;
		bool pointsRead;
		
		vector<SimpleColour3DPoint> *waveforms;
		bool showWaveforms;
		bool waveformsRead;
		
		unsigned long numTriDTMVertInRow;
		unsigned long numTrisDTMInRow;
		unsigned long numTriDTMRows;
		GLfloat **coordsXTriDTM;
		GLfloat **coordsYTriDTM;
		GLfloat **coordsZTriDTM;
		GLfloat **normXTriDTM;
		GLfloat **normYTriDTM;
		GLfloat **normZTriDTM;
		
		bool dtmReadIn;
		bool displayDTM;
		
		QColor *dtmColour;
		
		bool surfaceWireframe;
		bool surfaceLighting;
		
        QColor *shpLineColor;
		vector<Simple3DPoint> *shpPointlines;
		bool showSHPLines;
        bool shpLinesRead;
		
		
		
		
		
		
		
		

		

		
		
		
		
		bool showTrisVal;
		bool trisReadIn;
		bool displayTris;

		bool generateProfile;
		SPDPointsViewerDisplayProfile *displayProfile;

		
		
		
		
		
	};
}

#endif
