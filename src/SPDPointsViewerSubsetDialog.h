/*
 *  SPDPointsViewerSubsetDialog.h
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 16/02/2011.
 *  Copyright 2011 SPD3DPointsViewer.
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

#ifndef SPDPointsViewerSubsetDialog_H
#define SPDPointsViewerSubsetDialog_H

#include <iostream>
#include <string>
#include <sstream>

#include <QtWidgets>
#include <QtCore>

#ifdef Q_WS_MAC
#include <CoreFoundation/CFBundle.h>
#endif

#include "spd/SPDFile.h"

using namespace std;
using namespace spdlib;

namespace spdpointsviewer
{
	class SPDPointsViewerSubsetDialog : public QDialog
	{
		Q_OBJECT
	public:
		SPDPointsViewerSubsetDialog(SPDFile *spdFile, unsigned int *bbox, QWidget *parent=NULL);
		
		private slots:
		void selectInput();
		void selectOutput();
		void applyResults();
		void stopSPD2SPD();
		
		void printStdOut();
		void printStdError();
		void processingfinished(int, QProcess::ExitStatus);
	private:
		unsigned int *bbox;
		SPDFile *spdFile;
		
		QLineEdit *labelInputFile;
		QLineEdit *labelOutputFile;
		QTextEdit *outputTextBox;
		QProcess *spdSubsetProcess;
		
		QLineEdit *labelMinX;
		QLineEdit *labelMaxX;
		QLineEdit *labelMinY;
		QLineEdit *labelMaxY;
		QLineEdit *labelMinZ;
		QLineEdit *labelMaxZ;
		
	};
}

#endif


