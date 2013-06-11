/*
 *  SPDPointsViewerOverviewWidget.cpp
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

#include "SPDPointsViewerOverviewWidget.h"

namespace spdpointsviewer
{

	SPDPointsViewerOverviewWidget::SPDPointsViewerOverviewWidget(QWidget *parent) : QWidget(parent)
	{
		image = NULL;
		rectDefined = false;
		zoomLevel = 1;
	}

	void SPDPointsViewerOverviewWidget::setImage(QImage *image)
	{
		this->image = image;
	}

	void SPDPointsViewerOverviewWidget::upZoom()
	{
		if(zoomLevel < 0.1)
		{
			zoomLevel = zoomLevel*2;
		}
		else 
		{
			zoomLevel += 0.1;
		}
	}

	void SPDPointsViewerOverviewWidget::downZoom()
	{
		if((zoomLevel - 0.1) < 0)
		{
			zoomLevel = zoomLevel/2;
		}
		else 
		{
			zoomLevel -= 0.1;
		}
	}
	
	void SPDPointsViewerOverviewWidget::setStartEndPts(QPoint start, QPoint end)
	{
		rectDefined = true;
		this->startPt.setX(start.x());
		this->startPt.setY(start.y());
		this->endPt.setX(end.x());
		this->endPt.setY(end.y());
		this->repaint();
	}
	
	void SPDPointsViewerOverviewWidget::defineStartEndWholeImage()
	{
		rectDefined = true;
		this->startPt.setX(0);
		this->startPt.setY(0);
		QSize imgSize = image->size();
		this->endPt.setX(imgSize.width()*zoomLevel);
		this->endPt.setY(imgSize.height()*zoomLevel);
		this->repaint();
	}

	void SPDPointsViewerOverviewWidget::paintEvent(QPaintEvent*)
	{
		QPainter painter(this);
		
		if(image != NULL)
		{		
			//cout << "Paint\n";
			QSize imgSize = image->size();
			//QSize widgetSize = this->size();
			
			setMinimumSize(imgSize.width(), imgSize.height());
			
			source = QRectF(0.0, 0.0, imgSize.width(), imgSize.height());
			target = QRectF(0.0, 0.0, imgSize.width()*zoomLevel, imgSize.height()*zoomLevel);
			
			setMinimumSize(imgSize.width()*zoomLevel, imgSize.height()*zoomLevel);
			
			painter.drawImage(target, *image, source);
			
			if(rectDefined)
			{
				QPen pen;
				pen.setColor(Qt::red);
				pen.setWidthF(3);
				painter.setPen(pen);
				QRectF rect = QRectF(startPt, endPt);
				painter.drawRect(rect);
			}
		}
		else
		{
			painter.setPen(Qt::blue);
			painter.setFont(QFont("Arial", 30));
			painter.drawText(rect(), Qt::AlignCenter, "You need to open an SPD file.");
		}
		
	}

	void SPDPointsViewerOverviewWidget::mousePressEvent(QMouseEvent *event)
	{
		if(event->button() == Qt::LeftButton) 
		{
			this->startPt = event->pos();
		} 
	}


	void SPDPointsViewerOverviewWidget::mouseReleaseEvent(QMouseEvent *event)
	{
		if(event->button() == Qt::LeftButton) 
		{
			this->endPt = event->pos();
			rectDefined = true;
			
			//cout << "Start PT [" << startPt.x() << ", "<< startPt.y() << "]" << endl;
			//cout << "End PT [" << endPt.x() << ", "<< endPt.y() << "]" << endl;
			this->repaint();
			
			
			
			if(endPt.x() < startPt.x())
			{
				int tmpX = endPt.x();
				endPt.setX(startPt.x());
				startPt.setX(tmpX);
			}
			
			if(endPt.y() < startPt.y())
			{
				int tmpY = endPt.y();
				endPt.setY(startPt.y());
				startPt.setY(tmpY);
			}
			
			float sourceWidth = source.width();
			float sourceHeight = source.height();
			
			float targetWidth = target.width();
			float targetHeight = target.height();
			
			//cout << "sourceWidth = " << sourceWidth << endl;
			//cout << "sourceHeight = " << sourceHeight << endl;
			
			//cout << "targetWidth = " << targetWidth << endl;
			//cout << "targetHeight = " << targetHeight << endl;
			
			float widthRatio = sourceWidth / targetWidth;
			float heightRatio = sourceHeight / targetHeight;
			
			//cout << "widthRatio = " << widthRatio << endl;
			//cout << "heightRatio = " << heightRatio << endl;
			
			unsigned int startX = static_cast<unsigned int>(startPt.x()*widthRatio);
			unsigned int endX = static_cast<unsigned int>(endPt.x()*widthRatio);
			
			unsigned int startY = static_cast<unsigned int>(startPt.y()*heightRatio);
			unsigned int endY = static_cast<unsigned int>(endPt.y()*heightRatio);
			
			unsigned int *bbox = new unsigned int[4];
			bbox[0] = startX;
			bbox[1] = startY;
			bbox[2] = endX;
			bbox[3] = endY;
			
			//cout << "BBOX (1) = [" << bbox[0] << ", " << bbox[1] << "][" << bbox[2] << ", " << bbox[3] << "]\n";
			
			//openGLWidget->readPoints(bbox);
			emit selectedRegion(bbox);
		}
	}

	void SPDPointsViewerOverviewWidget::mouseMoveEvent(QMouseEvent *event)
	{
		this->endPt = event->pos();
		rectDefined = true;
		this->repaint();
	}

	void SPDPointsViewerOverviewWidget::reset()
	{
		if(image != NULL)
		{
			delete image;
			image = NULL;
		}
		rectDefined = false;
		this->repaint();
	}

}

