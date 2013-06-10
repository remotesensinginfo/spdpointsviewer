/*
 *  SPDPointsViewerLoad3DData.h
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 14/12/2010.
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

#ifndef SPDPointsViewerLoad3DData_H
#define SPDPointsViewerLoad3DData_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/cstdint.hpp>

#include "gdal_priv.h"
#include "ogrsf_frmts.h"
#include "ogr_api.h"

#include <QtCore>

#include "spd/SPDPulse.h"
#include "spd/SPDPoint.h"
#include "spd/SPDFile.h"
#include "spd/SPDFileReader.h"
#include "spd/SPDFileIncrementalReader.h"

#include "SPDPointsViewer3DWidget.h"
#include "SPDPointsViewerCommon.h"
#include "SPDPointsViewerColourTable.h"

using namespace spdlib;

namespace spdpointsviewer
{	
	class SPDPointsViewerLoad3DData : public QThread
	{
		Q_OBJECT
	public:
		SPDPointsViewerLoad3DData(unsigned int *bbox, SPDPointsViewer3DWidget *openGLWidget, SPDPointsViewerColourTable *colourTable, SPDFile *spdFile, string inputDTM, string inputTris, string inputSHP, bool loadPoints, bool loadVectors, bool loadDTM, bool loadTris, bool loadSHP, bool loadWaveform, bool normaliseWaveform, ColourPtsType clrPtType, QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay, QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay, QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay, ZFieldType zFieldType, bool grdReturnsOnly);
		void run();
		~SPDPointsViewerLoad3DData();
	public: signals:
		void valueChanged(int newValue);
		void errorMessages(QString message);
	private:
		void normaliseVec(pt3dfloat *p);
		pt3dfloat calcNormalVec(pt3dfloat p,pt3dfloat p1,pt3dfloat p2);
		string getLayerName(string filepath);
		unsigned int *bbox;
		SPDPointsViewer3DWidget *openGLWidget;
        SPDPointsViewerColourTable *colourTable;
		SPDFile *spdFile;
		string inputDTM;
		string inputTris;
		string inputSHP;
		bool loadPoints;
		bool loadVectors;
		bool loadDTM;
		bool loadTris; 
		bool loadSHP;
		bool loadWaveform;
		bool normaliseWaveform;
        bool grdReturnsOnly;
		ColourPtsType clrPtType;
        ZFieldType zFieldType;
		QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay;
		QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay;
		QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay;
	};
	
}

#endif


