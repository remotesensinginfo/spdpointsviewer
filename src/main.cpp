/*
 *  main.cpp
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

#include <QtWidgets>
#include "SPDPointsViewer.h"
#include "SPDPointsViewerApplication.h"
#include "SPDPointsViewerCreateOverviewImage.h"

using namespace spdpointsviewer;

#ifdef _WIN32
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
    // grab them out of the compiler supplied variables
    int argc = __argc;
    char **argv = __argv;
#else
int main(int argc, char *argv[])
{
#endif

	SPDPointsViewerCreateOverviewImage *createOverviewImageProxy = new SPDPointsViewerCreateOverviewImage();
    SPDPointsViewerApplication app(argc, argv, createOverviewImageProxy);
    SPDPointsViewer *mainWin = new SPDPointsViewer();
	createOverviewImageProxy->setPointViewer(mainWin);
    mainWin->show();
		
    return app.exec();
}


