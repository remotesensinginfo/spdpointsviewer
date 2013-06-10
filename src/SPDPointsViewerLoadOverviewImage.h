/*
 *  SPDPointsViewerLoadOverviewImage.h
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 12/12/2010.
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


#ifndef SPDPointsViewerLoadOverviewImage_H
#define SPDPointsViewerLoadOverviewImage_H

#include <iostream>
#include <string>

#include <QtCore>
#include <QtGui>

#include "SPDPointsViewerException.h"
#include "SPDPointsViewerCommon.h"

#include "spd/SPDFile.h"
#include "spd/SPDFileReader.h"
#include "spd/SPDFileIncrementalReader.h"

using namespace spdlib;

namespace spdpointsviewer
{
	class SPDPointsViewerLoadOverviewImage : public QThread
	{
		Q_OBJECT
	public:
		SPDPointsViewerLoadOverviewImage(SPDFile *spdFile);
		void run();
		QImage* getImage()throw(SPDPointsViewerException);
		SPDFile* getSPDFile();
		~SPDPointsViewerLoadOverviewImage();
	public: signals:
		void valueChanged(int newValue);
	private:
		SPDFile *spdFile;
		QImage *outImage;
		bool imageCreated;
	};

}

#endif

