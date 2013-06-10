/*
 *  SPDPointsViewerConvertDialog.h
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 03/08/2010.
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


#ifndef SPDPointsViewerConvertDialog_H
#define SPDPointsViewerConvertDialog_H

#include <iostream>
#include <string>
#include <sstream>

#include <QtGui>
#include <QtCore>

#ifdef Q_WS_MAC
#include <CoreFoundation/CFBundle.h>
#endif

using namespace std;

namespace spdpointsviewer
{
	class SPDPointsViewerConvertDialog : public QDialog
	{
		Q_OBJECT
	public:
		SPDPointsViewerConvertDialog(QWidget *parent);
		
	private slots:
		void selectInput();
		void selectOutput();
		void applyResults();
		void stopSPD2SPD();
		
		void printStdOut();
		void printStdError();
		void processingfinished(int, QProcess::ExitStatus);
	private:
		QLineEdit *labelInputFile;
		QLineEdit *labelOutputFile;
		QLineEdit *lineGridSize;
		QLineEdit *lineSpatialRef;
		QCheckBox *memoryOrDisk;
		QComboBox *format;
		QTextEdit *outputTextBox;
		QProcess *spd2spdProcess;
		
	};
}

#endif

