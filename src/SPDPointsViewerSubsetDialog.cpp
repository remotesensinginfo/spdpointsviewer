/*
 *  SPDPointsViewerSubsetDialog.cpp
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

#include "SPDPointsViewerSubsetDialog.h"


namespace spdpointsviewer
{
	
	SPDPointsViewerSubsetDialog::SPDPointsViewerSubsetDialog(SPDFile *spdFile, unsigned int *bbox, QWidget *parent) : QDialog(parent)
	{	
		this->spdFile = spdFile;
		this->bbox = bbox;
		
		/**************** Start Input File ****************/
		labelInputFile = new QLineEdit();
		labelInputFile->setMaxLength(200);
		QPushButton *selectInputButton = new QPushButton("Select Input");
		QObject::connect(selectInputButton, SIGNAL(clicked()), this, SLOT(selectInput()));
		selectInputButton->setDefault(false);
		
		if(spdFile != NULL)
		{
			labelInputFile->setText(QString::fromStdString(spdFile->getFilePath()));
		}
		
		QHBoxLayout *inputForm = new QHBoxLayout();
		inputForm->addWidget(labelInputFile, 0, 0);
		inputForm->addWidget(selectInputButton, 0, 0);
		/**************** End Input File ****************/
		
		/**************** Start Output File ****************/
		labelOutputFile = new QLineEdit();
		labelInputFile->setMaxLength(200);
		QPushButton *selectOutputButton = new QPushButton("Select Output");
		QObject::connect(selectOutputButton, SIGNAL(clicked()), this, SLOT(selectOutput()));
		selectOutputButton->setDefault(false);
		
		QHBoxLayout *outputForm1 = new QHBoxLayout();
		outputForm1->addWidget(labelOutputFile, 0, 0);
		outputForm1->addWidget(selectOutputButton, 0, 0);
		/**************** End Output File ****************/
		
		/**************** Start Output Limits ****************/
		labelMinX = new QLineEdit();
		labelMinX->setMaxLength(30);
		labelMaxX = new QLineEdit();
		labelMaxX->setMaxLength(30);
		labelMinY = new QLineEdit();
		labelMinY->setMaxLength(30);
		labelMaxY = new QLineEdit();
		labelMaxY->setMaxLength(30);
		labelMinZ = new QLineEdit();
		labelMinZ->setMaxLength(30);
		labelMaxZ = new QLineEdit();
		labelMaxZ->setMaxLength(30);
		
		QHBoxLayout *tlLimitsLayout = new QHBoxLayout();
		tlLimitsLayout->insertWidget(0, new QLabel("TL (X,Y):"), 0, Qt::AlignLeft);
		tlLimitsLayout->insertWidget(1, labelMinX, 0, Qt::AlignLeft);
		tlLimitsLayout->insertWidget(2, labelMaxY, 0, Qt::AlignLeft);
		
		QHBoxLayout *brLimitsLayout = new QHBoxLayout();
		brLimitsLayout->insertWidget(0, new QLabel("BR (X,Y):"), 0, Qt::AlignLeft);
		brLimitsLayout->insertWidget(1, labelMaxX, 0, Qt::AlignLeft);
		brLimitsLayout->insertWidget(2, labelMinY, 0, Qt::AlignLeft);
		
		QHBoxLayout *zLimitsLayout = new QHBoxLayout();
		zLimitsLayout->insertWidget(0, new QLabel("Z (Min,Max):"), 0, Qt::AlignLeft);
		zLimitsLayout->insertWidget(1, labelMinZ, 0, Qt::AlignLeft);
		zLimitsLayout->insertWidget(2, labelMaxZ, 0, Qt::AlignLeft);
		
		if(bbox != NULL)
		{
			double bboxTLX = spdFile->getXMin() + (((float)bbox[0]) * spdFile->getBinSize());
			double bboxTLY = spdFile->getYMax() - (((float)bbox[1]) * spdFile->getBinSize());
			double bboxBRX = spdFile->getXMin() + (((float)bbox[2]) * spdFile->getBinSize());
			double bboxBRY = spdFile->getYMax() - (((float)bbox[3]) * spdFile->getBinSize());
			
			labelMinX->setText(QString::number(bboxTLX, 'g', 10));
			labelMaxX->setText(QString::number(bboxBRX, 'g', 10));
			labelMinY->setText(QString::number(bboxBRY, 'g', 10));
			labelMaxY->setText(QString::number(bboxTLY, 'g', 10));
			labelMinZ->setText(QString::number(spdFile->getZMin(), 'g', 10));
			labelMaxZ->setText(QString::number(spdFile->getZMax(), 'g', 10));
		}
		else if(spdFile != NULL)
		{
			labelMinX->setText(QString::number(spdFile->getXMin(), 'g', 10));
			labelMaxX->setText(QString::number(spdFile->getXMax(), 'g', 10));
			labelMinY->setText(QString::number(spdFile->getYMin(), 'g', 10));
			labelMaxY->setText(QString::number(spdFile->getYMax(), 'g', 10));
			labelMinZ->setText(QString::number(spdFile->getZMin(), 'g', 10));
			labelMaxZ->setText(QString::number(spdFile->getZMax(), 'g', 10));
		}
				
		/**************** End Output Limits ****************/
		
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
		layout->insertLayout(3, tlLimitsLayout, 0);
		layout->insertLayout(4, brLimitsLayout, 0);
		layout->insertLayout(5, zLimitsLayout, 0);
		layout->insertLayout(6, buttons, 0);
		layout->insertWidget(7, outputTextBox, 0);
		setLayout(layout);
		/**************** END Final Layout ****************/
	}
	
	void SPDPointsViewerSubsetDialog::selectInput()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
		
		QStringList filters;
		filters << "SPD File (*.spd)";
		fileDialog->setNameFilters(filters);
		fileDialog->exec();
		
		QStringList files = fileDialog->selectedFiles();
		
		if(files.size() == 1)
		{
			labelInputFile->setText(files[0]);
		}
	}
	
	void SPDPointsViewerSubsetDialog::selectOutput()
	{
		
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptSave);
		
		QStringList filters;
		filters << "SPD File (*.spd)";
		fileDialog->setNameFilters(filters);
		fileDialog->exec();
		
		QStringList files = fileDialog->selectedFiles();
		
		if(files.size() == 1)
		{
			labelOutputFile->setText(files[0]);
		}
		 
	}
	
	void SPDPointsViewerSubsetDialog::applyResults()
	{
		QString filePath2exe = "/usr/local/bin/";
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
		 filePath2exe = pathStr + std::string("/Contents/MacOS/");
		 #endif
		 */
		
		QString spdsubset = "spdsubset";
		QString programPath = filePath2exe + spdsubset;
		
		QStringList arguments;
		arguments << "--inputformat" << "SPD"; 
		arguments << "--outputformat" << "SPD";
		
		if(labelMinX->text().length() > 0)
		{
			arguments << "--xmin" << labelMinX->text();
		}
		if(labelMaxX->text().length() > 0)
		{
			arguments << "--xmax" << labelMaxX->text();
		}
		
		if(labelMinY->text().length() > 0)
		{
			arguments << "--ymin" << labelMinY->text();
		}
		if(labelMaxY->text().length() > 0)
		{
			arguments << "--ymax" << labelMaxY->text();
		}
		
		if(labelMinZ->text().length() > 0)
		{
			arguments << "--zmin" << labelMinZ->text();
		}
		if(labelMaxZ->text().length() > 0)
		{
			arguments << "--zmax" << labelMaxZ->text();
		}
		
		arguments << labelInputFile->text() << labelOutputFile->text();
		
		outputTextBox->textCursor().insertText("Started...\n");
		spdSubsetProcess = new QProcess(this);
		connect(spdSubsetProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(printStdOut()));
		connect(spdSubsetProcess, SIGNAL(readyReadStandardError()), this, SLOT(printStdError()));
		connect(spdSubsetProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processingfinished(int, QProcess::ExitStatus)));
		spdSubsetProcess->start(programPath, arguments);
	}
	
	void SPDPointsViewerSubsetDialog::stopSPD2SPD()
	{
		spdSubsetProcess->kill();
		outputTextBox->setTextColor(QColor::fromRgb(0, 0, 255));
		outputTextBox->textCursor().insertText("KILLED...\n");
		outputTextBox->moveCursor(QTextCursor::End);
	}
	
	void SPDPointsViewerSubsetDialog::printStdOut()
	{
		QByteArray byteArray = spdSubsetProcess->readAllStandardOutput();
		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
		QString stdOutString = codec->toUnicode(byteArray);
		outputTextBox->setTextColor(QColor::fromRgb(0, 0, 0));
		outputTextBox->textCursor().insertText(stdOutString);
		outputTextBox->moveCursor(QTextCursor::End);
	}
	
	void SPDPointsViewerSubsetDialog::printStdError()
	{
		QByteArray byteArray = spdSubsetProcess->readAllStandardError();
		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
		QString stdOutString = codec->toUnicode(byteArray);
		outputTextBox->setTextColor(QColor::fromRgb(255, 0, 0));
		outputTextBox->textCursor().insertText(stdOutString);
		outputTextBox->moveCursor(QTextCursor::End);
	}
	
	void SPDPointsViewerSubsetDialog::processingfinished(int, QProcess::ExitStatus)
	{
		outputTextBox->setTextColor(QColor::fromRgb(0, 255, 0));
		outputTextBox->textCursor().insertText("Complete\n");
	}

	
}


