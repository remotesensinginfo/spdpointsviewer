/*
 *  SPDPointsViewerOverviewWidget.h
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

#ifndef SPDPointsViewerOverviewWidget_H
#define SPDPointsViewerOverviewWidget_H

#include <iostream>
#include <string>

#include <QtGui>

using namespace std;

namespace spdpointsviewer
{
	class SPDPointsViewerOverviewWidget : public QWidget
	{
		Q_OBJECT
		
	public:
		SPDPointsViewerOverviewWidget(QWidget *parent);
		void setImage(QImage *image);
		void downZoom();
		void upZoom();
		void reset();
		void setStartEndPts(QPoint start, QPoint end);
		void defineStartEndWholeImage();
	public: signals:
		void selectedRegion(unsigned int *bbox);
	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent*);
	private:
		QImage *image;
		QPoint startPt;
		QPoint endPt;
		bool rectDefined;
		QRectF target;
		QRectF source;
		float zoomLevel;
	};

}
#endif
