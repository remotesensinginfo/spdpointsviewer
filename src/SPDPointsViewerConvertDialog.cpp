/*
 *  SPDPointsViewerConvertDialog.cpp
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

#include "SPDPointsViewerConvertDialog.h"

namespace spdpointsviewer
{

	SPDPointsViewerConvertDialog::SPDPointsViewerConvertDialog(QWidget *parent) : QDialog(parent)
	{	
		/**************** Start Inputs ****************/
		labelInputFile = new QLineEdit();
		labelInputFile->setMaxLength(200);
		QPushButton *selectInputButton = new QPushButton("Select Input");
		QObject::connect(selectInputButton, SIGNAL(clicked()), this, SLOT(selectInput()));
		selectInputButton->setDefault(false);
		
		QHBoxLayout *inputForm = new QHBoxLayout();
		inputForm->addWidget(labelInputFile, 0, 0);
		inputForm->addWidget(selectInputButton, 0, 0);
		/**************** End Inputs ****************/
		
		/**************** Start Outputs ****************/
		labelOutputFile = new QLineEdit();
		labelInputFile->setMaxLength(200);
		QPushButton *selectOutputButton = new QPushButton("Select Output");
		QObject::connect(selectOutputButton, SIGNAL(clicked()), this, SLOT(selectOutput()));
		selectOutputButton->setDefault(false);
		
		QHBoxLayout *outputForm1 = new QHBoxLayout();
		outputForm1->addWidget(labelOutputFile, 0, 0);
		outputForm1->addWidget(selectOutputButton, 0, 0);
		
		QLabel *gridSizeLabel = new QLabel("Grid Size:");
		lineGridSize = new QLineEdit();
		lineGridSize->setMaxLength(3);
		memoryOrDisk = new QCheckBox("In Memory");
		memoryOrDisk->setChecked(true);
		format = new QComboBox();
		QStringList formatsList;
		formatsList << "SPD" << "PTS" << "CSV" << "ASCII" << "SHP" << "XYZ" << "XYZI";
		format->addItems(formatsList);
		
		QHBoxLayout *outputForm2 = new QHBoxLayout();
		outputForm2->addWidget(format, 0, 0);
		outputForm2->addWidget(gridSizeLabel, 0, 0);
		outputForm2->addWidget(lineGridSize, 0, 0);
		outputForm2->addWidget(memoryOrDisk, 0, 0);
		
		QLabel *spatialRefLabel = new QLabel("Spatial Ref:");
		
		lineSpatialRef = new QLineEdit();
		lineSpatialRef->setMaxLength(300);
		
		QHBoxLayout *outputForm3 = new QHBoxLayout();
		outputForm3->addWidget(spatialRefLabel, 0, 0);
		outputForm3->addWidget(lineSpatialRef, 0, 0);
		/**************** End Outputs ****************/	
		
		/**************** SETUP Buttons ****************/
		QPushButton *okButton = new QPushButton("Run");
		QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(applyResults()));
		okButton->setDefault(true);
		QPushButton *stopButton = new QPushButton("Stop");
		QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stopSPD2SPD()));
		stopButton->setDefault(false);
		QPushButton *cancelButton = new QPushButton("Exit");
		QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
		cancelButton->setDefault(false);
		QHBoxLayout *buttons = new QHBoxLayout();
		buttons->addStretch(1);
		buttons->addWidget(okButton, 1, 0);
		buttons->addWidget(stopButton, 1, 0);
		buttons->addWidget(cancelButton, 2, 0);
		buttons->addStretch(1);
		/**************** END Buttons ****************/
		
		/**************** SETUP Output Box ****************/
		outputTextBox = new QTextEdit();
		outputTextBox->setReadOnly(true);
		/**************** END Output Box ****************/
		
		/**************** SETUP Final Layout ****************/
		QVBoxLayout *layout = new QVBoxLayout();
		layout->insertLayout(1, inputForm, 0);
		layout->insertLayout(2, outputForm1, 0);
		layout->insertLayout(3, outputForm2, 0);
		layout->insertLayout(4, outputForm3, 0);
		layout->insertLayout(5, buttons, 0);
		layout->insertWidget(6, outputTextBox, 0);
		setLayout(layout);
		/**************** END Final Layout ****************/
	}

	void SPDPointsViewerConvertDialog::selectInput()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
		
		QStringList filters;
		filters << "SPD File (*.spd)" << "Points File (*.pts)" << "ASCII File (*.asc)" << "XYZ File (*.xyz)" << "XYZI File (*.xyzi)" << "CSV File (*.csv)" << "Any files (*)";
		fileDialog->setNameFilters(filters);
		fileDialog->exec();
		
		QStringList files = fileDialog->selectedFiles();
		
		if(files.size() == 1)
		{
			labelInputFile->setText(files[0]);
		}
	}

	void SPDPointsViewerConvertDialog::selectOutput()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptSave);
		
		QStringList filters;
		filters << "SPD File (*.spd)" << "Points File (*.pts)" << "ASCII File (*.asc)" << "XYZ File (*.xyz)" << "XYZI File (*.xyzi)" << "CSV File (*.csv)" << "Any files (*)";
		fileDialog->setNameFilters(filters);
		fileDialog->exec();
		
		QStringList files = fileDialog->selectedFiles();
		
		if(files.size() == 1)
		{
			labelOutputFile->setText(files[0]);
		}
	}

	void SPDPointsViewerConvertDialog::applyResults()
	{
		/*
		cout << "Input File " << labelInputFile->text().toStdString() << endl;
		cout << "Output File " << labelOutputFile->text().toStdString() << endl;
		cout << "Output Format " << format->currentText().toStdString() << endl;
		cout << "Spatial Ref \"" << lineSpatialRef->text().toStdString()<< "\"" << endl;
		cout << "Grid Size " << lineGridSize->text().toFloat() << endl;
		if(memoryOrDisk->isChecked())
		{
			cout << "In Memory\n";
		}
		else
		{
			cout << "Using Disk\n";
		}
		*/
		
		
		std::string macOSFilePath = "/usr/local/bin/";
/*
#ifdef Q_WS_MAC
		std::string pathStr = "";
		CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
		CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef,kCFURLPOSIXPathStyle);
		const char *pathPtr = CFStringGetCStringPtr(macPath,CFStringGetSystemEncoding());
		std::stringstream ss;
		ss << pathPtr;
		ss >> pathStr;
		CFRelease(appUrlRef);
		CFRelease(macPath);
		macOSFilePath = pathStr + std::string("/Contents/MacOS/");
#endif
*/
		QString spd2spd = "spd2spd";
		QString programPath = QString::fromStdString(macOSFilePath) + spd2spd;
		
		QStringList arguments;
		arguments << "-i" << labelInputFile->text(); 
		arguments << "-o" << labelOutputFile->text();
		arguments << "-f" << format->currentText();
		arguments << "-g" << lineGridSize->text();
		
		//if((!lineGridSize->text().isEmpty()) & (!lineGridSize->text().isNull()) & (lineGridSize->text() != ""))
		if(lineGridSize->text().length() > 5)
		{
			arguments << "-s" << lineSpatialRef->text();
			//cout << "including proj = " << lineGridSize->text().length() << endl;
		}
		
		if(memoryOrDisk->isChecked())
		{
			arguments << "-m";
			//SPDConvertFormats convertFormats;
			//convertFormats.convertInMemory(labelInputFile->text().toStdString(), labelOutputFile->text().toStdString(), format->currentText().toStdString(), lineGridSize->text().toFloat(), lineSpatialRef->text().toStdString());
		}
		else
		{
			arguments << "-d";
			//SPDConvertFormats convertFormats;
			//convertFormats.convertInRows(labelInputFile->text().toStdString(), labelOutputFile->text().toStdString(), format->currentText().toStdString(), lineGridSize->text().toFloat(), lineSpatialRef->text().toStdString());
		}
		outputTextBox->textCursor().insertText("Started...\n");
		spd2spdProcess = new QProcess(this);
		connect(spd2spdProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(printStdOut()));
		connect(spd2spdProcess, SIGNAL(readyReadStandardError()), this, SLOT(printStdError()));
		connect(spd2spdProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processingfinished(int, QProcess::ExitStatus)));
		spd2spdProcess->start(programPath, arguments);
	}
	
	void SPDPointsViewerConvertDialog::stopSPD2SPD()
	{
		spd2spdProcess->kill();
		outputTextBox->setTextColor(QColor::fromRgb(0, 0, 255));
		outputTextBox->textCursor().insertText("KILLED...\n");
		outputTextBox->moveCursor(QTextCursor::End);
	}
	
	void SPDPointsViewerConvertDialog::printStdOut()
	{
		QByteArray byteArray = spd2spdProcess->readAllStandardOutput();
		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
		QString stdOutString = codec->toUnicode(byteArray);
		outputTextBox->setTextColor(QColor::fromRgb(0, 0, 0));
		outputTextBox->textCursor().insertText(stdOutString);
		outputTextBox->moveCursor(QTextCursor::End);
	}
	
	void SPDPointsViewerConvertDialog::printStdError()
	{
		QByteArray byteArray = spd2spdProcess->readAllStandardError();
		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
		QString stdOutString = codec->toUnicode(byteArray);
		outputTextBox->setTextColor(QColor::fromRgb(255, 0, 0));
		outputTextBox->textCursor().insertText(stdOutString);
		outputTextBox->moveCursor(QTextCursor::End);
	}
	
	void SPDPointsViewerConvertDialog::processingfinished(int, QProcess::ExitStatus)
	{
		outputTextBox->setTextColor(QColor::fromRgb(0, 255, 0));
		outputTextBox->textCursor().insertText("Complete\n");
	}
	

}
