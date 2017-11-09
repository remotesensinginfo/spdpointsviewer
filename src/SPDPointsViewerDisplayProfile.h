/*
 *  SPDPointsViewerDisplayProfile.h
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


#ifndef SPDPointsViewerDisplayProfile_H
#define SPDPointsViewerDisplayProfile_H

#include <iostream>
#include <string>
#include <list>

#include <QtWidgets>

//#include "spd/SPDPoint.h"

//#include "qwt/qwt_plot_curve.h"
//#include "qwt/qwt_plot.h"
//#include "qwt/qwt_plot_grid.h"

using namespace std;
//using namespace spdlib;

namespace spdpointsviewer
{
	class SPDPointsViewerDisplayProfile : public QDialog
	{
		Q_OBJECT
	public:
		SPDPointsViewerDisplayProfile(QWidget *parent);//, list<SPDPoint*> *pts);
		//void generatePlot(list<SPDPoint*> *pts);
		void clearPlot();
		void savePlot(QString filepath);
		~SPDPointsViewerDisplayProfile();
	private:
		//QwtPlotCurve *data2Plot;
		//QwtPlot *profilePlot;
		//QwtPlotGrid *grid;
		double *yValues;
		double *xValues;
		int range;
	};
}

#endif


