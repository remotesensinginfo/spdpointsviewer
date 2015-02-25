/*
 *  SPDPointsViewerApplication.cpp
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

#include "SPDPointsViewerApplication.h"

namespace spdpointsviewer
{
	SPDPointsViewerApplication::SPDPointsViewerApplication(int& argc, char *argv[], SPDPointsViewerCreateOverviewImage *createOverviewImageProxy) : QApplication(argc, argv)
	{
		this->createOverviewImageProxy = createOverviewImageProxy;
        
        if(argc == 2)
        {
            QString file2Open = argv[1];
            createOverviewImageProxy->loadSPDFile(file2Open);
        }
	}
	
	bool SPDPointsViewerApplication::event(QEvent *event)
	{
		QString file2Open = "";
		switch (event->type()) 
		{
			case QEvent::FileOpen:
				file2Open = static_cast<QFileOpenEvent *>(event)->file();
				createOverviewImageProxy->loadSPDFile(file2Open);
				return true;
			default:
				return QApplication::event(event);
        }
	}
}