/*
 *  SPDPointsViewerDisplayProfile.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 02/08/2010.
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

#include "SPDPointsViewerDisplayProfile.h"

namespace spdpointsviewer
{

SPDPointsViewerDisplayProfile::SPDPointsViewerDisplayProfile(QWidget *parent): QDialog(parent)
{
	xValues = NULL;
	yValues = NULL;
	//data2Plot = NULL;
	//profilePlot = NULL;
	//grid = NULL;
}

	/*
void SPDPointsViewerDisplayProfile::generatePlot(list<SPDPoint*> *pts)
{
	
	unsigned int numPts = pts->size();
	
	if(numPts > 0)
	{
		double minZ = 0;
		double maxZ = 0;
		bool first = true;
		
		list<SPDPoint*>::iterator iterPts;
		for(iterPts = pts->begin(); iterPts != pts->end(); ++iterPts)
		{
			if(first)
			{
				minZ = (*iterPts)->z;
				maxZ = (*iterPts)->z;
				first = false;
			}
			else if((*iterPts)->z > maxZ)
			{
				maxZ = (*iterPts)->z;
			}
			else if((*iterPts)->z < minZ)
			{
				minZ = (*iterPts)->z;
			}
		}
		
		int minZInt = static_cast<int>(minZ);
		int maxZInt = static_cast<int>(maxZ+0.5);
		
		int range = maxZInt - minZInt;
		
		if(range == 0)
		{
			range = 1;
		}
		
		unsigned int *bins = new unsigned int[range];
		for(int i = 0; i < range; ++i)
		{
			bins[i] = 0;
		}
		
		int *binRanges = new int[range+1];
		
		binRanges[0] = minZInt;
		for(int i = 1; i <= range; ++i)
		{
			binRanges[i] = minZInt + i;
		}
		
		for(iterPts = pts->begin(); iterPts != pts->end(); ++iterPts)
		{
			for(int i = 0; i < range; ++i)
			{
				if(((*iterPts)->z > binRanges[i]) & ((*iterPts)->z < binRanges[i+1]))
				{
					++bins[i];
					break;
				}
			}
		}
		
		double *yValues = new double[range];
		for(int i = 0; i < range; ++i)
		{
			yValues[i] = ((float)(minZInt + i))+0.5;
		}
		
		double *xValues = new double[range];
		for(int i = 0; i < range; ++i)
		{
			xValues[i] = (((double)bins[i])/numPts)*100;
		}
		
		delete[] binRanges;
		delete[] bins;
		
		data2Plot = new QwtPlotCurve();
		data2Plot->setData(xValues, yValues, range);
		
		QString plotTitleQString = QString::fromStdString("Vertical Profile");
		QString plotXTitleQString = QString::fromStdString("Freq. (%)");
		QString plotYTitleQString = QString::fromStdString("Height (m)");
		QwtText plotTitle = QwtText(plotTitleQString, QwtText::AutoText);
		
		profilePlot = new QwtPlot(plotTitle, this);
		profilePlot->setCanvasBackground(QColor(Qt::white));
		profilePlot->setAxisTitle (QwtPlot::xBottom, plotXTitleQString);
		profilePlot->setAxisTitle (QwtPlot::yLeft, plotYTitleQString);
		
		grid = new QwtPlotGrid;
		grid->enableXMin(true);
		grid->enableYMin(true);
		grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
		grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
		grid->attach(profilePlot);
		
		data2Plot->attach(profilePlot);
		profilePlot->polish();
		profilePlot->replot();
		
		setMinimumSize(profilePlot->sizeHint());
	}
	else 
	{
		QLabel *labelTitle = new QLabel("There are no points to create a profile");
		QVBoxLayout *layout = new QVBoxLayout();
		layout->addWidget(labelTitle, 1, 0);
		setLayout(layout);
	}
	 
}
	 */

void SPDPointsViewerDisplayProfile::savePlot(QString filepath)
{
	/*if(profilePlot != NULL)
	{
		QPrinter printer;
		printer.setOrientation(QPrinter::Landscape);
		printer.setColorMode(QPrinter::Color);
		printer.setOutputFileName(filepath);
		printer.setResolution(96);
		profilePlot->print(printer);
	}
	else
	{
		QLabel *labelTitle = new QLabel("No plot has been exported...");
		QVBoxLayout *layout = new QVBoxLayout();
		layout->addWidget(labelTitle, 1, 0);
		setLayout(layout);
	}*/
}

void SPDPointsViewerDisplayProfile::clearPlot()
{
	delete[] xValues;
	delete[] yValues;
	//delete data2Plot;
	//delete profilePlot;
}

SPDPointsViewerDisplayProfile::~SPDPointsViewerDisplayProfile()
{
	delete[] xValues;
	delete[] yValues;
	//delete data2Plot;
	//delete profilePlot;
}

}

