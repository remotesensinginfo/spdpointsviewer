/*
 *  SPDPointsViewer.cpp
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

#include "SPDPointsViewer.h"

namespace spdpointsviewer
{

	SPDPointsViewer::SPDPointsViewer()
	{	
        colourTablesFac = new SPDPointsViewerColourTableFactory();
        
		this->setWindowTitle("SPDPointsViewer");
		
		// Set Minimum size of window
		setMinimumSize(775, 600);

		int sliderControlMinSize = 200;
		
		/**************** SETUP 3D TAB ****************/		
		openGLWidget = new SPDPointsViewer3DWidget();
		openGLWidget->setMinimumSize(400,300);
		openGLWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
		
		animateThread = new SPDPointsViewer3DControlObj(openGLWidget, true, false, "", 1);
		
		startAnimationButton = new QPushButton("Start");
		startAnimationButton->setMaximumSize(100, 30);
		QObject::connect(startAnimationButton, SIGNAL(clicked()), this, SLOT(startAnimation()));
		startAnimationButton->setDisabled(false);
		stopAnimationButton = new QPushButton("Stop");
		stopAnimationButton->setMaximumSize(100, 30);
		QObject::connect(stopAnimationButton, SIGNAL(clicked()), this, SLOT(stopAnimation()));
		stopAnimationButton->setDisabled(true);
		
		screenshotsCheckBox = new QCheckBox("Screenshots", this);
		screenshotsCheckBox->setChecked(false);

		continuousCheckBox = new QCheckBox("Continuous", this);
		continuousCheckBox->setChecked(false);
		continuousCheckBox->setDisabled(false);
		
		degreesMovement = 1;
		QSlider *moveDegreeSlider = new QSlider(Qt::Horizontal);
		moveDegreeSlider->setTickInterval(1);
		moveDegreeSlider->setTickPosition(QSlider::TicksBothSides);
		moveDegreeSlider->setRange(1, 20);
		moveDegreeSlider->setMinimumSize(sliderControlMinSize, 1);
		moveDegreeSlider->setTracking(true);
		moveDegreeSlider->setValue(10);
		connect(moveDegreeSlider, SIGNAL(valueChanged(int)), this, SLOT(degreesMovementSlot(int)));
		
		QString strValOverlap = "1";
		degreesMovementLabel = new QLabel(strValOverlap);
		
		QHBoxLayout *layoutDegreesMove = new QHBoxLayout();
		layoutDegreesMove->insertWidget(0, moveDegreeSlider, 0, Qt::AlignLeft);
		layoutDegreesMove->insertWidget(1, degreesMovementLabel, 0, Qt::AlignLeft);
		
		QHBoxLayout *column1Buttons = new QHBoxLayout();
		column1Buttons->insertWidget(0, startAnimationButton, 0, Qt::AlignLeft);
		column1Buttons->insertWidget(1, stopAnimationButton, 0, Qt::AlignLeft);
		
		QVBoxLayout *column1 = new QVBoxLayout();
		column1->insertWidget(0, new QLabel("Generate Animation:"), 0, Qt::AlignLeft);
		column1->insertLayout(1, column1Buttons, 0);
		column1->insertWidget(2, screenshotsCheckBox, 0, Qt::AlignLeft);
		column1->insertWidget(3, continuousCheckBox, 0, Qt::AlignLeft);
		column1->insertLayout(4, layoutDegreesMove, 0);
		
		xRotSlider = new QSlider(Qt::Horizontal);
		xRotSlider->setTickInterval(30);
		xRotSlider->setTickPosition(QSlider::TicksBothSides);
		xRotSlider->setRange(0, 360);
		xRotSlider->setMinimumSize(sliderControlMinSize, 10);
		xRotSlider->setTracking(true);
		xRotSlider->setValue(120);
		connect(xRotSlider, SIGNAL(valueChanged(int)), this, SLOT(xRotMovement(int)));

		yRotSlider = new QSlider(Qt::Horizontal);
		yRotSlider->setTickInterval(30);
		yRotSlider->setTickPosition(QSlider::TicksBothSides);
		yRotSlider->setRange(0, 360);
		yRotSlider->setMinimumSize(sliderControlMinSize, 10);
		yRotSlider->setTracking(true);
		yRotSlider->setValue(180);
		connect(yRotSlider, SIGNAL(valueChanged(int)), this, SLOT(yRotMovement(int)));
		
		zRotSlider = new QSlider(Qt::Horizontal);
		zRotSlider->setTickInterval(30);
		zRotSlider->setTickPosition(QSlider::TicksBothSides);
		zRotSlider->setRange(0, 360);
		zRotSlider->setMinimumSize(sliderControlMinSize, 10);
		zRotSlider->setTracking(true);
		zRotSlider->setValue(180);
		connect(zRotSlider, SIGNAL(valueChanged(int)), this, SLOT(zRotMovement(int)));
		
		rangeSlider = new QSlider(Qt::Horizontal);
		rangeSlider->setTickInterval(10);
		rangeSlider->setTickPosition(QSlider::TicksBothSides);
		rangeSlider->setRange(-30, 120);
		rangeSlider->setMinimumSize(sliderControlMinSize, 10);
		rangeSlider->setTracking(true);
		rangeSlider->setValue(40);
		connect(rangeSlider, SIGNAL(valueChanged(int)), this, SLOT(rangeMovement(int)));
		
		xShiftSlider = new QSlider(Qt::Horizontal);
		xShiftSlider->setTickInterval(30);
		xShiftSlider->setTickPosition(QSlider::TicksBothSides);
		xShiftSlider->setRange(-160, 160);
		xShiftSlider->setMinimumSize(sliderControlMinSize, 10);
		xShiftSlider->setTracking(true);
		xShiftSlider->setValue(0);
		connect(xShiftSlider, SIGNAL(valueChanged(int)), this, SLOT(xShiftMovement(int)));
		
		yShiftSlider = new QSlider(Qt::Horizontal);
		yShiftSlider->setTickInterval(30);
		yShiftSlider->setTickPosition(QSlider::TicksBothSides);
		yShiftSlider->setRange(-160, 160);
		yShiftSlider->setMinimumSize(sliderControlMinSize, 10);
		yShiftSlider->setTracking(true);
		yShiftSlider->setValue(0);
		connect(yShiftSlider, SIGNAL(valueChanged(int)), this, SLOT(yShiftMovement(int)));

		zShiftSlider = new QSlider(Qt::Horizontal);
		zShiftSlider->setTickInterval(30);
		zShiftSlider->setTickPosition(QSlider::TicksBothSides);
		zShiftSlider->setRange(-160, 160);
		zShiftSlider->setMinimumSize(sliderControlMinSize, 10);
		zShiftSlider->setTracking(true);
		zShiftSlider->setValue(0);
		connect(zShiftSlider, SIGNAL(valueChanged(int)), this, SLOT(zShiftMovement(int)));
		
		pointSizeSlider = new QSlider(Qt::Horizontal);
		pointSizeSlider->setTickInterval(10);
		pointSizeSlider->setTickPosition(QSlider::TicksBothSides);
		pointSizeSlider->setRange(0, 200);
		pointSizeSlider->setMinimumSize(sliderControlMinSize, 10);
		pointSizeSlider->setTracking(true);
		pointSizeSlider->setValue(10);
		connect(pointSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(pointSizeMovement(int)));
		
		QHBoxLayout *hLayoutXRot = new QHBoxLayout();
		hLayoutXRot->insertWidget(0, new QLabel("X Rot"), 0, Qt::AlignLeft);
		hLayoutXRot->insertWidget(1, xRotSlider, 0, Qt::AlignLeft);
		
		QHBoxLayout *hLayoutYRot = new QHBoxLayout();
		hLayoutYRot->insertWidget(0, new QLabel("Y Rot"), 0, Qt::AlignLeft);
		hLayoutYRot->insertWidget(1, yRotSlider, 0, Qt::AlignLeft);
		
		QHBoxLayout *hLayoutZRot = new QHBoxLayout();
		hLayoutZRot->insertWidget(0, new QLabel("Z Rot"), 0, Qt::AlignLeft);
		hLayoutZRot->insertWidget(1, zRotSlider, 0, Qt::AlignLeft);
		
		QHBoxLayout *hLayoutXShift = new QHBoxLayout();
		hLayoutXShift->insertWidget(0, new QLabel("X Shift"), 0, Qt::AlignLeft);
		hLayoutXShift->insertWidget(1, xShiftSlider, 0, Qt::AlignLeft);
		
		QHBoxLayout *hLayoutYShift = new QHBoxLayout();
		hLayoutYShift->insertWidget(0, new QLabel("Y Shift"), 0, Qt::AlignLeft);
		hLayoutYShift->insertWidget(1, yShiftSlider, 0, Qt::AlignLeft);
		
		QHBoxLayout *hLayoutZShift = new QHBoxLayout();
		hLayoutZShift->insertWidget(0, new QLabel("Z Shift"), 0, Qt::AlignLeft);
		hLayoutZShift->insertWidget(1, zShiftSlider, 0, Qt::AlignLeft);
		
		QHBoxLayout *hLayoutPointSize = new QHBoxLayout();
		hLayoutPointSize->insertWidget(0, new QLabel("Pt Size"), 0, Qt::AlignLeft);
		hLayoutPointSize->insertWidget(1, pointSizeSlider, 0, Qt::AlignLeft);
		
		QPushButton *resetButton = new QPushButton("Reset");
		resetButton->setMaximumSize(100, 30);
		QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(reset3DTransformation()));
		
		QVBoxLayout *column2 = new QVBoxLayout();
		column2->insertWidget(0, new QLabel("Scene Movement:"), 0, Qt::AlignLeft);
		column2->insertLayout(1, hLayoutXRot, 0);
		column2->insertLayout(2, hLayoutYRot, 0);
		column2->insertLayout(3, hLayoutZRot, 0);
		column2->insertLayout(4, hLayoutXShift, 0);
		column2->insertLayout(5, hLayoutYShift, 0);
		column2->insertLayout(6, hLayoutZShift, 0);
		column2->insertLayout(7, hLayoutPointSize, 0);
		column2->insertWidget(-1, resetButton, 0, Qt::AlignCenter);
		
		showPtsCheckBox = new QCheckBox("Show Points", this);
		showPtsCheckBox->setChecked(openGLWidget->getShowPoints());
		showPtsCheckBox->setEnabled(false);
		QObject::connect(showPtsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(showPTSSlot(int)));
		
		showLinesCheckBox = new QCheckBox("Show Lines", this);
		showLinesCheckBox->setChecked(openGLWidget->getShowLines());
		showLinesCheckBox->setEnabled(false);
		QObject::connect(showLinesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(showLinesDisplaySlot(int)));
		
		showWaveformCheckBox3D = new QCheckBox("Show Waveforms", this);
		showWaveformCheckBox3D->setChecked(openGLWidget->getShowWaveforms());
		showWaveformCheckBox3D->setEnabled(false);
		QObject::connect(showWaveformCheckBox3D, SIGNAL(stateChanged(int)), this, SLOT(showWaveformDisplaySlot(int)));
		
		showDTMCheckBox3D = new QCheckBox("Show DTM", this);
		showDTMCheckBox3D->setChecked(openGLWidget->getDisplayDTM());
		showDTMCheckBox3D->setDisabled(true);
		QObject::connect(showDTMCheckBox3D, SIGNAL(stateChanged(int)), this, SLOT(showDTMDisplaySlot(int)));
		
		showTriCheckBox3D = new QCheckBox("Show Triangles", this);
		showTriCheckBox3D->setChecked(openGLWidget->getDisplayTriangles());
		showTriCheckBox3D->setDisabled(true);
		QObject::connect(showTriCheckBox3D, SIGNAL(stateChanged(int)), this, SLOT(showTriDisplaySlot(int)));
		
		showLightingCheckBox = new QCheckBox("Use Lighting", this);
		showLightingCheckBox->setChecked(openGLWidget->useLighting());
		showLightingCheckBox->setDisabled(true);
		QObject::connect(showLightingCheckBox, SIGNAL(stateChanged(int)), this, SLOT(showLightingSlot(int)));
		
		showAsWireframeCheckBox = new QCheckBox("Show Wireframe", this);
		showAsWireframeCheckBox->setChecked(openGLWidget->showWireframe());
		showAsWireframeCheckBox->setDisabled(true);
		QObject::connect(showAsWireframeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(showWireframeSlot(int)));
		
		showSHPCheckBox3D = new QCheckBox("Show Shapefile", this);
		showSHPCheckBox3D->setChecked(openGLWidget->showSHP());
		showSHPCheckBox3D->setDisabled(true);
		QObject::connect(showSHPCheckBox3D, SIGNAL(stateChanged(int)), this, SLOT(showSHPDisplaySlot(int)));
		
		QVBoxLayout *column4 = new QVBoxLayout();
		column4->insertWidget(0, new QLabel("Control Layers:"), 0, Qt::AlignLeft);
		column4->insertWidget(1, showPtsCheckBox, 0, Qt::AlignLeft);
		column4->insertWidget(2, showLinesCheckBox, 0, Qt::AlignLeft);
		column4->insertWidget(3, showWaveformCheckBox3D, 0, Qt::AlignLeft);
		column4->insertWidget(4, showDTMCheckBox3D, 0, Qt::AlignLeft);
		column4->insertWidget(5, showSHPCheckBox3D, 0, Qt::AlignLeft);
		column4->insertWidget(6, showTriCheckBox3D, 0, Qt::AlignLeft);
		column4->insertWidget(7, showLightingCheckBox, 0, Qt::AlignLeft);
		column4->insertWidget(8, showAsWireframeCheckBox, 0, Qt::AlignLeft);
		
		QVBoxLayout *vLayout3DViewControls = new QVBoxLayout();
		vLayout3DViewControls->insertLayout(0, column2, 0);
		vLayout3DViewControls->insertLayout(1, column4, 0);
		vLayout3DViewControls->insertStretch(2, 1);
		vLayout3DViewControls->insertLayout(3, column1, 0);
		
		QVBoxLayout *vLayout3DViewAndRange = new QVBoxLayout();
		vLayout3DViewAndRange->insertWidget(0, openGLWidget, 0);
		vLayout3DViewAndRange->insertWidget(1, rangeSlider, 0);
		
		QHBoxLayout *hLayout3DView = new QHBoxLayout();
		hLayout3DView->insertLayout(0, vLayout3DViewControls, 0);
		hLayout3DView->insertLayout(1, vLayout3DViewAndRange, 0);
		
		/***************** END 3D TAB *****************/
		
		
		/************* SETUP OVERVIEW TAB *************/
		QPushButton *zoomInButton = new QPushButton("+");
		QObject::connect(zoomInButton, SIGNAL(clicked()), this, SLOT(upZoom()));
		zoomInButton->setMaximumSize(75, 30);
		QPushButton *zoomOutButton = new QPushButton("-");
		QObject::connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(downZoom()));
		zoomOutButton->setMaximumSize(75, 30);
		QPushButton *loadAllButton = new QPushButton("Load All Data");
		QObject::connect(loadAllButton, SIGNAL(clicked()), this, SLOT(loadAllData()));
		loadAllButton->setMaximumSize(150, 30);
        QPushButton *reloadDataButton = new QPushButton("Reload Data");
		QObject::connect(reloadDataButton, SIGNAL(clicked()), this, SLOT(reloadData()));
		reloadDataButton->setMaximumSize(150, 30);
		genProfileCheckBox = new QCheckBox("Generate Profile", this);
		genProfileCheckBox->setChecked(false);
		QObject::connect(genProfileCheckBox, SIGNAL(stateChanged(int)), this, SLOT(generateProfileSlot()));
		comboColourPoints = new QComboBox();
		QStringList items;
		items  << "Amplitude" << "Classification" << "Height" << "RGB Values" << "Returns" << "Source" << "Elevation" << "Width";
		comboColourPoints->insertItems(0, items);
		comboColourPoints->setEditable(false);
		QObject::connect(comboColourPoints, SIGNAL(activated(const QString)), this, SLOT(selectColourTypeSlot(const QString)));
        
        comboColourTables = new QComboBox();
        comboColourTables->insertItems(0, colourTablesFac->getAvailableColourTableNames());
        comboColourTables->setEditable(false);
		QObject::connect(comboColourTables, SIGNAL(activated(const QString)), this, SLOT(selectClrTabSlot(const QString)));
        colourTable = colourTablesFac->getColourTable("Hue");
		
        comboZFieldPoints = new QComboBox();
		QStringList zItems;
		zItems  << "Topo Height" << "Norm Height";
		comboZFieldPoints->insertItems(0, zItems);
		comboZFieldPoints->setEditable(false);
		QObject::connect(comboZFieldPoints, SIGNAL(activated(const QString)), this, SLOT(selectZFieldSlot(const QString)));
        zFieldType = spdpointsviewer::topoHeightType;
        
		showPointsCheckBoxOverview = new QCheckBox("Read Points", this);
		showPointsCheckBoxOverview->setChecked(false);
		showPointsCheckBoxOverview->setEnabled(false);
		QObject::connect(showPointsCheckBoxOverview, SIGNAL(stateChanged(int)), this, SLOT(showPointsSlot(int)));
		
		showLinesCheckBoxOverview = new QCheckBox("Read Lines", this);
		showLinesCheckBoxOverview->setChecked(false);
		showLinesCheckBoxOverview->setEnabled(false);
		QObject::connect(showLinesCheckBoxOverview, SIGNAL(stateChanged(int)), this, SLOT(showLinesSlot(int)));
		
		showWaveformCheckBoxOverview = new QCheckBox("Read Waveforms", this);
		showWaveformCheckBoxOverview->setChecked(false);
		showWaveformCheckBoxOverview->setEnabled(false);
		QObject::connect(showWaveformCheckBoxOverview, SIGNAL(stateChanged(int)), this, SLOT(showWaveformSlot(int)));
		
		normWaveformCheckBox = new QCheckBox("Normalise Waveform", this);
		normWaveformCheckBox->setChecked(false);
		normWaveformCheckBox->setEnabled(false);
		QObject::connect(normWaveformCheckBox, SIGNAL(stateChanged(int)), this, SLOT(normWaveformSlot(int)));
				
		showDTMCheckBoxOverview = new QCheckBox("Read DTM", this);
		showDTMCheckBoxOverview->setChecked(false);
		showDTMCheckBoxOverview->setDisabled(true);
		QObject::connect(showDTMCheckBoxOverview, SIGNAL(stateChanged(int)), this, SLOT(showDTMSlot(int)));

		showTriCheckBoxOverview = new QCheckBox("Read Triangles", this);
		showTriCheckBoxOverview->setChecked(false);
		showTriCheckBoxOverview->setDisabled(true);
		QObject::connect(showTriCheckBoxOverview, SIGNAL(stateChanged(int)), this, SLOT(showTriSlot(int)));
		
		showSHPCheckBoxOverview = new QCheckBox("Read Shapefile", this);
		showSHPCheckBoxOverview->setChecked(false);
		showSHPCheckBoxOverview->setDisabled(true);
		QObject::connect(showSHPCheckBoxOverview, SIGNAL(stateChanged(int)), this, SLOT(showSHPSlot(int)));
        
        onlyGrdCheckBox = new QCheckBox("Ground Returns Only", this);
        onlyGrdCheckBox->setChecked(false);
		onlyGrdCheckBox->setDisabled(false);
		
		QHBoxLayout *zoomControls = new QHBoxLayout();
		zoomControls->insertWidget(0, zoomInButton, 0, Qt::AlignCenter);
		zoomControls->insertWidget(1, zoomOutButton, 0, Qt::AlignCenter);
		
		QVBoxLayout *overControls = new QVBoxLayout();	
		overControls->insertWidget(0, new QLabel("Point Colour:"), 0, Qt::AlignLeft);
		overControls->insertWidget(1, comboColourPoints, 0, Qt::AlignLeft);
        overControls->insertWidget(2, new QLabel("Z Field:"), 0, Qt::AlignLeft);
		overControls->insertWidget(3, comboZFieldPoints, 0, Qt::AlignLeft);
        overControls->insertWidget(4, new QLabel("Colour Table:"), 0, Qt::AlignLeft);
		overControls->insertWidget(5, comboColourTables, 0, Qt::AlignLeft);
		overControls->insertWidget(6, new QLabel("Options:"), 0, Qt::AlignLeft);
		overControls->insertWidget(7, showPointsCheckBoxOverview, 0, Qt::AlignLeft);
		overControls->insertWidget(8, showLinesCheckBoxOverview, 0, Qt::AlignLeft);
		overControls->insertWidget(9, showWaveformCheckBoxOverview, 0, Qt::AlignLeft);
		overControls->insertWidget(10, showDTMCheckBoxOverview, 0, Qt::AlignLeft);
		overControls->insertWidget(11, showTriCheckBoxOverview, 0, Qt::AlignLeft);
		overControls->insertWidget(12, showSHPCheckBoxOverview, 0, Qt::AlignLeft);
		overControls->insertWidget(13, normWaveformCheckBox, 1, Qt::AlignLeft);
		overControls->insertWidget(14, genProfileCheckBox, 1, Qt::AlignLeft);
        overControls->insertWidget(15, onlyGrdCheckBox, 1, Qt::AlignLeft);
		overControls->insertStretch(16, 1);
		overControls->insertLayout(17, zoomControls,0);
		overControls->insertWidget(18, loadAllButton, 0, Qt::AlignCenter);
        overControls->insertWidget(19, reloadDataButton, 0, Qt::AlignCenter);
		
		overviewWidget = new SPDPointsViewerOverviewWidget(this);
		QObject::connect(overviewWidget, SIGNAL(selectedRegion(unsigned int*)), this, SLOT(read3DData(unsigned int*)));
		QScrollArea *overviewScrollArea = new QScrollArea(this);
		overviewScrollArea->setWidget(overviewWidget);
		overviewScrollArea->setWidgetResizable(true);
		
		QHBoxLayout *hLayoutOverview = new QHBoxLayout();
		hLayoutOverview->insertLayout(0, overControls, 0);
		hLayoutOverview->insertWidget(1, overviewScrollArea, 1);
		
		/************** END OVERVIEW TAB **************/
		
		QWidget *combinedWidgetOverview = new QWidget();
		combinedWidgetOverview->setLayout(hLayoutOverview);
		
		QWidget *combinedWidget3D = new QWidget();
		combinedWidget3D->setLayout(hLayout3DView);
		
		tabs = new QTabWidget();
		tabs->addTab(combinedWidgetOverview, "Image Overview");
		tabs->addTab(combinedWidget3D, "3D View");
		
		setCentralWidget(tabs);
		
		createActions();
		createMenus();
				
		inputDTM = "";
		inputTris = "";
		inputSHP = "";
		loadPoints = false;
		loadVectors = false;
		loadDTM = false;
		loadTris = false;
		loadSHP = false;
		loadWaveform = false;
		spdFile = NULL;
		clrPtType = spdpointsviewer::amplitudeColourType;
		
		classDisplay = new QMap<boost::uint_fast16_t, CatDisplayInfo>();
		returnDisplay = new QMap<boost::uint_fast16_t, CatDisplayInfo>();
		sourceDisplay = new QMap<boost::uint_fast16_t, CatDisplayInfo>();
		
		QColor color = QColor();
		CatDisplayInfo return1Dis;
		return1Dis.pointSize = 1;
		color.setHsv(0, 255, 255, 255);
		return1Dis.red = color.redF();
		return1Dis.green = color.greenF();
		return1Dis.blue = color.blueF();
		returnDisplay->insert(1, return1Dis);
		CatDisplayInfo return2Dis;
		return2Dis.pointSize = 1;
		color.setHsv(240, 255, 255, 255);
		return2Dis.red = color.redF();
		return2Dis.green = color.greenF();
		return2Dis.blue = color.blueF();
		returnDisplay->insert(2, return2Dis);
		CatDisplayInfo return3Dis;
		return3Dis.pointSize = 1;
		color.setHsv(120, 255, 255, 255);
		return3Dis.red = color.redF();
		return3Dis.green = color.greenF();
		return3Dis.blue = color.blueF();
		returnDisplay->insert(3, return3Dis);
		CatDisplayInfo return4Dis;
		return4Dis.pointSize = 1;
		color.setHsv(60, 255, 255, 255);
		return4Dis.red = color.redF();
		return4Dis.green = color.greenF();
		return4Dis.blue = color.blueF();
		returnDisplay->insert(4, return4Dis);
		CatDisplayInfo return5Dis;
		return5Dis.pointSize = 1;
		color.setHsv(180, 255, 255, 255);
		return5Dis.red = color.redF();
		return5Dis.green = color.greenF();
		return5Dis.blue = color.blueF();
		returnDisplay->insert(5, return5Dis);
		CatDisplayInfo return6Dis;
		return6Dis.pointSize = 1;
		color.setHsv(300, 255, 255, 255);
		return6Dis.red = color.redF();
		return6Dis.green = color.greenF();
		return6Dis.blue = color.blueF();
		returnDisplay->insert(6, return6Dis);
		
		CatDisplayInfo source0Dis;
		source0Dis.pointSize = 1;
		color.setHsv(0, 255, 255, 255);
		source0Dis.red = color.redF();
		source0Dis.green = color.greenF();
		source0Dis.blue = color.blueF();
		sourceDisplay->insert(0, source0Dis);
		CatDisplayInfo source1Dis;
		source1Dis.pointSize = 1;
		color.setHsv(240, 255, 255, 255);
		source1Dis.red = color.redF();
		source1Dis.green = color.greenF();
		source1Dis.blue = color.blueF();
		sourceDisplay->insert(1, source1Dis);
		CatDisplayInfo source2Dis;
		source2Dis.pointSize = 1;
		color.setHsv(120, 255, 255, 255);
		source2Dis.red = color.redF();
		source2Dis.green = color.greenF();
		source2Dis.blue = color.blueF();
		sourceDisplay->insert(2, source2Dis);
		CatDisplayInfo source3Dis;
		source3Dis.pointSize = 1;
		color.setHsv(60, 255, 255, 255);
		source3Dis.red = color.redF();
		source3Dis.green = color.greenF();
		source3Dis.blue = color.blueF();
		sourceDisplay->insert(3, source3Dis);
		CatDisplayInfo source4Dis;
		source4Dis.pointSize = 1;
		color.setHsv(180, 255, 255, 255);
		source4Dis.red = color.redF();
		source4Dis.green = color.greenF();
		source4Dis.blue = color.blueF();
		sourceDisplay->insert(4, source4Dis);
		CatDisplayInfo source5Dis;
		source5Dis.pointSize = 1;
		color.setHsv(300, 255, 255, 255);
		source5Dis.red = color.redF();
		source5Dis.green = color.greenF();
		source5Dis.blue = color.blueF();
		sourceDisplay->insert(5, source5Dis);
		
		CatDisplayInfo unclassifiedDis;
		unclassifiedDis.pointSize = 1;
		color.setRgb(255, 255, 255, 255);
		unclassifiedDis.red = color.redF();
		unclassifiedDis.green = color.greenF();
		unclassifiedDis.blue = color.blueF();
		classDisplay->insert(SPD_UNCLASSIFIED, unclassifiedDis);
		
		CatDisplayInfo createdDis;
		createdDis.pointSize = 1;
		color.setRgb(0, 229, 238, 255); 
		createdDis.red = color.redF();
		createdDis.green = color.greenF();
		createdDis.blue = color.blueF();
		classDisplay->insert(SPD_CREATED, createdDis);
		
		CatDisplayInfo groundDis;
		//groundDis.pointSize = 1;
		//color.setRgb(195, 176, 145, 255);
		groundDis.pointSize = 2;
		color.setRgb(255, 0, 0, 255);
		groundDis.red = color.redF();
		groundDis.green = color.greenF();
		groundDis.blue = color.blueF();
		classDisplay->insert(SPD_GROUND, groundDis);
		
		CatDisplayInfo lowVegDis;
		lowVegDis.pointSize = 1;
		color.setRgb(133, 187, 101, 255);
		lowVegDis.red = color.redF();
		lowVegDis.green = color.greenF();
		lowVegDis.blue = color.blueF();
		classDisplay->insert(SPD_LOW_VEGETATION, lowVegDis);
		
		CatDisplayInfo medVegDis;
		medVegDis.pointSize = 1;
		color.setRgb(3, 192, 60, 255);
		medVegDis.red = color.redF();
		medVegDis.green = color.greenF();
		medVegDis.blue = color.blueF();
		classDisplay->insert(SPD_MEDIUM_VEGETATION, medVegDis);
		
		CatDisplayInfo highVegDis;
		highVegDis.pointSize = 1;
		color.setRgb(23, 114, 69, 255);
		highVegDis.red = color.redF();
		highVegDis.green = color.greenF();
		highVegDis.blue = color.blueF();
		classDisplay->insert(SPD_HIGH_VEGETATION, highVegDis);
		
		CatDisplayInfo buildingDis;
		buildingDis.pointSize = 1;
		color.setRgb(192, 64, 0, 255);
		buildingDis.red = color.redF();
		buildingDis.green = color.greenF();
		buildingDis.blue = color.blueF();
		classDisplay->insert(SPD_BUILDING, buildingDis);
		
		CatDisplayInfo waterDis;
		waterDis.pointSize = 1;
		color.setRgb(0, 0, 205, 255);
		waterDis.red = color.redF();
		waterDis.green = color.greenF();
		waterDis.blue = color.blueF();
		classDisplay->insert(SPD_WATER, waterDis);
		
		CatDisplayInfo trunkDis;
		trunkDis.pointSize = 1;
		color.setRgb(176, 101, 0, 255);
		trunkDis.red = color.redF();
		trunkDis.green = color.greenF();
		trunkDis.blue = color.blueF();
		classDisplay->insert(SPD_TRUNK, trunkDis);
		
		CatDisplayInfo foilageDis;
		foilageDis.pointSize = 1;
		color.setRgb(173, 255, 47, 255);
		foilageDis.red = color.redF();
		foilageDis.green = color.greenF();
		foilageDis.blue = color.blueF();
		classDisplay->insert(SPD_FOILAGE, foilageDis);
		
		CatDisplayInfo branchDis;
		branchDis.pointSize = 1;
		color.setRgb(218, 165, 32, 255);
		branchDis.red = color.redF();
		branchDis.green = color.greenF();
		branchDis.blue = color.blueF();
		classDisplay->insert(SPD_BRANCH, branchDis);
		
		CatDisplayInfo wallDis;
		wallDis.pointSize = 1;
		color.setRgb(128, 128, 128, 255);
		wallDis.red = color.redF();
		wallDis.green = color.greenF();
		wallDis.blue = color.blueF();
		classDisplay->insert(SPD_WALL, wallDis);
				
		selectionMade = false;
		bboxSelection = NULL;
	}

	void SPDPointsViewer::loadSPDFile(QString file)
	{
		QFileInfo inFileInfo(file);
		if(!inFileInfo.exists())
		{
			// ERROR MESSAGE...
			QErrorMessage *errMessage = new QErrorMessage(this);
			errMessage->showMessage(QString("File does not exist..."));
		}
		else if(!inFileInfo.isReadable())
		{
			// ERROR MESSAGE
			QErrorMessage *errMessage = new QErrorMessage(this);
			errMessage->showMessage(QString("File is not readable..."));
		}
		else
		{
			QString titleName = "SPDPointsViewer - ";
			titleName += inFileInfo.fileName();
			this->setWindowTitle(titleName);
			string inputSPDFile = file.toStdString();
			
			spdFile = new SPDFile(inputSPDFile);
			
			SPDFileReader reader = SPDFileReader();
			reader.readHeaderInfo(inputSPDFile, spdFile);
			
			if((spdFile->getDecomposedPtDefined() == SPD_FALSE) &
			   (spdFile->getDiscretePtDefined() == SPD_FALSE) &
			   (spdFile->getReceiveWaveformDefined() == SPD_TRUE))
			{
				loadPoints = false;
				loadVectors = true;
				loadWaveform = true;
				normWaveform = true;
				
				showPointsCheckBoxOverview->setCheckState(Qt::Unchecked);
				showPointsCheckBoxOverview->setEnabled(false);
				showLinesCheckBoxOverview->setCheckState(Qt::Checked);
				showLinesCheckBoxOverview->setEnabled(true);
				showWaveformCheckBoxOverview->setCheckState(Qt::Checked);
				showWaveformCheckBoxOverview->setEnabled(true);
				normWaveformCheckBox->setCheckState(Qt::Checked);
				normWaveformCheckBox->setEnabled(true);
				
				showPtsCheckBox->setCheckState(Qt::Unchecked);
				showPtsCheckBox->setEnabled(false);
				showLinesCheckBox->setCheckState(Qt::Unchecked);
				showLinesCheckBox->setEnabled(true);
				showWaveformCheckBox3D->setCheckState(Qt::Checked);
				showWaveformCheckBoxOverview->setEnabled(true);	
				
				openGLWidget->setShowPoints(false);
				openGLWidget->setShowLines(false);
				openGLWidget->setShowWaveforms(true);
			}
			else if(((spdFile->getDecomposedPtDefined() == SPD_TRUE) |
					 (spdFile->getDiscretePtDefined() == SPD_TRUE)) &
					(spdFile->getReceiveWaveformDefined() == SPD_TRUE))
			{
				loadPoints = true;
				loadVectors = true;
				loadWaveform = true;
				normWaveform = true;
				
				showPointsCheckBoxOverview->setCheckState(Qt::Checked);
				showPointsCheckBoxOverview->setEnabled(true);
				showLinesCheckBoxOverview->setCheckState(Qt::Checked);
				showLinesCheckBoxOverview->setEnabled(true);
				showWaveformCheckBoxOverview->setCheckState(Qt::Checked);
				showWaveformCheckBoxOverview->setEnabled(true);
				normWaveformCheckBox->setCheckState(Qt::Checked);
				normWaveformCheckBox->setEnabled(true);
				
				showPtsCheckBox->setCheckState(Qt::Checked);
				showPtsCheckBox->setEnabled(true);
				showLinesCheckBox->setCheckState(Qt::Unchecked);
				showLinesCheckBox->setEnabled(true);
				showWaveformCheckBox3D->setCheckState(Qt::Unchecked);
				showWaveformCheckBoxOverview->setEnabled(true);
				
				openGLWidget->setShowPoints(true);
				openGLWidget->setShowLines(false);
				openGLWidget->setShowWaveforms(false);
			}
			else if((spdFile->getDecomposedPtDefined() == SPD_TRUE) |
					(spdFile->getDiscretePtDefined() == SPD_TRUE))
			{
				loadPoints = true;
				loadVectors = true;
				loadWaveform = false;
				normWaveform = false;
				
				showPointsCheckBoxOverview->setCheckState(Qt::Checked);
				showPointsCheckBoxOverview->setEnabled(true);
				showLinesCheckBoxOverview->setCheckState(Qt::Checked);
				showLinesCheckBoxOverview->setEnabled(true);
				showWaveformCheckBoxOverview->setCheckState(Qt::Unchecked);
				showWaveformCheckBoxOverview->setEnabled(false);
				normWaveformCheckBox->setCheckState(Qt::Unchecked);
				normWaveformCheckBox->setEnabled(false);
				
				showPtsCheckBox->setCheckState(Qt::Checked);
				showPtsCheckBox->setEnabled(true);
				showLinesCheckBox->setCheckState(Qt::Unchecked);
				showLinesCheckBox->setEnabled(true);
				showWaveformCheckBox3D->setCheckState(Qt::Unchecked);
				showWaveformCheckBox3D->setEnabled(false);
				
				openGLWidget->setShowPoints(true);
				openGLWidget->setShowLines(false);
				openGLWidget->setShowWaveforms(false);
			}
			
			progressDialog = new QProgressDialog(this);
			progressDialog->setLabel(new QLabel("Generating Overview Image..."));
			progressDialog->setRange(0, ((spdFile->getNumberBinsY()*2)+1));
			progressDialog->setCancelButtonText(QString());
			progressDialog->setWindowModality(Qt::WindowModal);
			progressDialog->setValue(0);
			
			loadImageThread = new SPDPointsViewerLoadOverviewImage(spdFile);
			QObject::connect(loadImageThread, SIGNAL(finished()), this, SLOT(finishedLoadingImage()));
			QObject::connect(loadImageThread, SIGNAL(valueChanged(int)), this, SLOT(feedbackValue(int)));
			loadImageThread->start(QThread::HighPriority);
		}
	}
	
	void SPDPointsViewer::finishedLoadingImage()
	{
		overviewImage = loadImageThread->getImage();
		overviewWidget->setImage(overviewImage);
		progressDialog->setValue((loadImageThread->getSPDFile()->getNumberBinsY()*2)+1);
		overviewWidget->repaint();
		screenshotAction->setEnabled(true);
		saveOverviewAction->setEnabled(true);
		//delete progressDialog;
	}
	
	void SPDPointsViewer::feedbackValue(int value)
	{
        if(progressDialog != NULL)
        {
            progressDialog->setValue(value);
        }
	}
	
	void SPDPointsViewer::xRotMovement(int value)
	{
		openGLWidget->setXRotation(value);
	}

	void SPDPointsViewer::yRotMovement(int value)
	{
		openGLWidget->setYRotation(value);
	}

	void SPDPointsViewer::zRotMovement(int value)
	{
		openGLWidget->setZRotation(value);
	}
	
	void SPDPointsViewer::xShiftMovement(int value)
	{
		openGLWidget->setXShift(value);
	}
	
	void SPDPointsViewer::yShiftMovement(int value)
	{
		openGLWidget->setYShift(value);
	}
	
	void SPDPointsViewer::zShiftMovement(int value)
	{
		openGLWidget->setZShift(value);
	}

	void SPDPointsViewer::rangeMovement(int value)
	{
		float rangeVal = exp(float(value)/10);
		
		//cout << "Range = " << rangeVal << endl;
		
		openGLWidget->setRange(rangeVal);
		if(rangeVal <= 50)
		{
			xShiftSlider->setRange(-20, 20);
			yShiftSlider->setRange(-20, 20);
			zShiftSlider->setRange(-20, 20);
			xShiftSlider->setTickInterval(1);
			yShiftSlider->setTickInterval(1);
			zShiftSlider->setTickInterval(1);
		}
		else if((rangeVal > 50) & (rangeVal <= 100))
		{
			xShiftSlider->setRange(-80, 80);
			yShiftSlider->setRange(-80, 80);
			zShiftSlider->setRange(-80, 80);
			xShiftSlider->setTickInterval(5);
			yShiftSlider->setTickInterval(5);
			zShiftSlider->setTickInterval(5);
		}
		else if((rangeVal > 10) & (rangeVal <= 200))
		{
			xShiftSlider->setRange(-160, 160);
			yShiftSlider->setRange(-160, 160);
			xShiftSlider->setTickInterval(15);
			yShiftSlider->setTickInterval(15);
		}
		else if((rangeVal > 200) & (rangeVal <= 350))
		{
			xShiftSlider->setRange(-225, 225);
			yShiftSlider->setRange(-225, 225);
			zShiftSlider->setRange(-225, 225);
			xShiftSlider->setTickInterval(20);
			yShiftSlider->setTickInterval(20);
			zShiftSlider->setTickInterval(20);
		}
		else if(rangeVal > 350)
		{
			xShiftSlider->setRange(-300, 300);
			yShiftSlider->setRange(-300, 300);
			zShiftSlider->setRange(-300, 300);
			xShiftSlider->setTickInterval(25);
			yShiftSlider->setTickInterval(25);
			zShiftSlider->setTickInterval(25);
		}
	}
	
	void SPDPointsViewer::pointSizeMovement(int value)
	{
		float pointSizeMulti = ((float)value)/10;
		if(pointSizeMulti <= 0)
		{
			pointSizeMulti = 0.1;
		}
		openGLWidget->setPointSizeMulti(pointSizeMulti);
	}
	
	void SPDPointsViewer::reset3DTransformation()
	{
		xRotSlider->setValue(120);
		yRotSlider->setValue(180);
		zRotSlider->setValue(180);
		
		rangeSlider->setValue(40);
		xShiftSlider->setValue(0);
		yShiftSlider->setValue(0);
		zShiftSlider->setValue(0);
		pointSizeSlider->setValue(10);
		
		openGLWidget->reset3DTrans();
	}

	void SPDPointsViewer::createMenus()
	{
		fileMenu = menuBar()->addMenu(tr("&File"));
		fileMenu->addAction(openAction);
		fileMenu->addAction(openDTMAction);
		fileMenu->addAction(openSHPAction);
        fileMenu->addAction(openPTxtAction);
		fileMenu->addAction(convertAction);
		fileMenu->addAction(screenshotAction);
		screenshotAction->setEnabled(false);
		fileMenu->addAction(savePlotAction);
		savePlotAction->setEnabled(false);
		fileMenu->addAction(saveOverviewAction);
		saveOverviewAction->setEnabled(false);
		
		utilsMenu = menuBar()->addMenu(tr("&Utilities"));
		utilsMenu->addAction(subsetAction);
		utilsMenu->addAction(mergeAction);
		utilsMenu->addAction(statsAction);
		utilsMenu->addAction(proj4Action);
		
		optionsMenu = menuBar()->addMenu(tr("&Options"));
		optionsMenu->addAction(optionsAction);
		
		helpMenu = menuBar()->addMenu(tr("&Help"));
		helpMenu->addAction(helpAction);
		helpMenu->addAction(aboutAction);
	}

	void SPDPointsViewer::createActions()
	{
		openAction = new QAction(tr("&Open"), this);
		openAction->setShortcut(QKeySequence::Open);
		openAction->setStatusTip(tr("Open SPD File"));
		connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
		
		openDTMAction = new QAction(tr("&Open DTM"), this);
		openDTMAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
		openDTMAction->setStatusTip(tr("Open DTM Image File"));
		connect(openDTMAction, SIGNAL(triggered()), this, SLOT(openDTM()));
		
        openPTxtAction = new QAction(tr("&Open Triangles"), this);
		openPTxtAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
		openPTxtAction->setStatusTip(tr("Open PTxt triangles File"));
		connect(openPTxtAction, SIGNAL(triggered()), this, SLOT(openPTxt()));
        
		openSHPAction = new QAction(tr("&Open Shapefile"), this);
		openSHPAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
		openSHPAction->setStatusTip(tr("Open shapefile"));
		connect(openSHPAction, SIGNAL(triggered()), this, SLOT(openShapefile()));
		
		convertAction = new QAction(tr("&Convert"), this);
		convertAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
		convertAction->setStatusTip(tr("Convert File"));
		connect(convertAction, SIGNAL(triggered()), this, SLOT(convert()));
		
		screenshotAction = new QAction(tr("&Screenshot"), this);
		screenshotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
		screenshotAction->setStatusTip(tr("Take Screenshot"));
		connect(screenshotAction, SIGNAL(triggered()), this, SLOT(screenshot()));
		
		savePlotAction = new QAction(tr("&Save Profile"), this);
		savePlotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_P));
		savePlotAction->setStatusTip(tr("Save Profile Plot (as PDF)"));
		connect(savePlotAction, SIGNAL(triggered()), this, SLOT(saveProfilePlot()));
		
		saveOverviewAction = new QAction(tr("&Save Overview"), this);
		saveOverviewAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
		saveOverviewAction->setStatusTip(tr("Save Overview Image (as PNG)"));
		connect(saveOverviewAction, SIGNAL(triggered()), this, SLOT(saveOverviewImage()));
				
		subsetAction = new QAction(tr("&Subset"), this);
		subsetAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_K));
		subsetAction->setStatusTip(tr("Subset Points File"));
		connect(subsetAction, SIGNAL(triggered()), this, SLOT(subset()));
		
		statsAction = new QAction(tr("&Statistics"), this);
		statsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
		statsAction->setStatusTip(tr("Export Statistics Image"));
		connect(statsAction, SIGNAL(triggered()), this, SLOT(stats()));
		
		mergeAction = new QAction(tr("&Merge"), this);
		mergeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
		mergeAction->setStatusTip(tr("Merge Points Files"));
		connect(mergeAction, SIGNAL(triggered()), this, SLOT(merge()));
		
		proj4Action = new QAction(tr("&Proj4"), this);
		proj4Action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
		proj4Action->setStatusTip(tr("Print Proj4 String"));
		connect(proj4Action, SIGNAL(triggered()), this, SLOT(proj4()));
		
		optionsAction = new QAction(tr("&Options"), this);
		optionsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
		optionsAction->setStatusTip(tr("Options"));
		connect(optionsAction, SIGNAL(triggered()), this, SLOT(options()));
		
		helpAction = new QAction(tr("&Help"), this);
		helpAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
		helpAction->setStatusTip(tr("Help"));
		connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
		
		aboutAction = new QAction(tr("&About"), this);
		aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
		aboutAction->setStatusTip(tr("About"));
		connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
	}

	void SPDPointsViewer::open()
	{
		QFileDialog fileDialog;
		fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
		fileDialog.setWindowTitle("Open SPD file");
		
		QStringList filters;
		filters << "SPD File (*.spd)";
		// << "Points File (*.pts)" << "ASCII File (*.asc)" 
		// << "XYZ File (*.xyz)" << "XYZI File (*.xyzi)" 
		// << "CSV File (*.csv)" << "Any files (*)";
		fileDialog.setNameFilters(filters);
		if(fileDialog.exec() == QDialog::Accepted)
		{
			QStringList files = fileDialog.selectedFiles();
			//delete fileDialog;
			if(files.size() == 1)
			{
				this->loadSPDFile(files[0]);
			}
			else
			{
				// ERROR MESSAGE
				QErrorMessage *errMessage = new QErrorMessage(this);
				errMessage->showMessage(QString("You can only select a single file..."));
			}
		}
	}
	
	void SPDPointsViewer::openDTM()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
		fileDialog->setWindowTitle("Open DTM file");
		
		QStringList filters;
		filters << "ENVI File (*.env)" << "GEOTIFF (*.tif)" << "Any files (*)";
		fileDialog->setNameFilters(filters);
		if(fileDialog->exec() == QDialog::Accepted)
		{	
			QStringList files = fileDialog->selectedFiles();
			if(files.size() == 1)
			{
				QFileInfo inFileInfo(files[0]);
				if(!inFileInfo.exists())
				{
					// ERROR MESSAGE...
					QErrorMessage *errMessage = new QErrorMessage(this);
					errMessage->showMessage(QString("File does not exist..."));
				}
				else if(!inFileInfo.isReadable())
				{
					// ERROR MESSAGE
					QErrorMessage *errMessage = new QErrorMessage(this);
					errMessage->showMessage(QString("File is not readable..."));
				}
				else
				{
					this->inputDTM = files[0].toStdString();
					loadDTM = true;
					
					showDTMCheckBoxOverview->setDisabled(false);
					showDTMCheckBoxOverview->setChecked(true);
					
					showAsWireframeCheckBox->setDisabled(false);
					showLightingCheckBox->setDisabled(false);
					showDTMCheckBox3D->setDisabled(false);
				}
			}
		}
		delete fileDialog;
	}
    
    void SPDPointsViewer::openShapefile()
    {
        QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
		fileDialog->setWindowTitle("Open Shapefile file");
		
		QStringList filters;
		filters << "ESRI Shapefile (*.shp)";
		fileDialog->setNameFilters(filters);
		if(fileDialog->exec() == QDialog::Accepted)
		{	
			QStringList files = fileDialog->selectedFiles();
			if(files.size() == 1)
			{
				QFileInfo inFileInfo(files[0]);
				if(!inFileInfo.exists())
				{
					// ERROR MESSAGE...
					QErrorMessage *errMessage = new QErrorMessage(this);
					errMessage->showMessage(QString("File does not exist..."));
				}
				else if(!inFileInfo.isReadable())
				{
					// ERROR MESSAGE
					QErrorMessage *errMessage = new QErrorMessage(this);
					errMessage->showMessage(QString("File is not readable..."));
				}
				else
				{
					this->inputSHP = files[0].toStdString();
					loadSHP = true;
					
					showSHPCheckBoxOverview->setDisabled(false);
					showSHPCheckBoxOverview->setChecked(true);
					
					showSHPCheckBox3D->setDisabled(false);
                    showSHPCheckBox3D->setChecked(true);
				}
			}
		}
		delete fileDialog;
    }
	
	void SPDPointsViewer::openPTxt()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
		fileDialog->setWindowTitle("Open Triangles file (*ptxt)");
		
		QStringList filters;
		filters << "PTxt File (*.ptxt)";
		fileDialog->setNameFilters(filters);
		if(fileDialog->exec() == QDialog::Accepted)
		{
			QStringList files = fileDialog->selectedFiles();
			
			if(files.size() == 1)
			{
				QFileInfo inFileInfo(files[0]);
				if(!inFileInfo.exists())
				{
					// ERROR MESSAGE...
					QErrorMessage *errMessage = new QErrorMessage(this);
					errMessage->showMessage(QString("File does not exist..."));
				}
				else if(!inFileInfo.isReadable())
				{
					// ERROR MESSAGE
					QErrorMessage *errMessage = new QErrorMessage(this);
					errMessage->showMessage(QString("File is not readable..."));
				}
				else
				{
					//openGLWidget->setPTxtFilePath(files[0].toStdString());
					
					showTriCheckBoxOverview->setDisabled(false);
					showTriCheckBoxOverview->setChecked(true);
					openGLWidget->setShowTriangles(true);
					
					showAsWireframeCheckBox->setDisabled(false);
					showLightingCheckBox->setDisabled(false);
					showTriCheckBox3D->setDisabled(false);
				}
			}
		}
		delete fileDialog;
	}

	void SPDPointsViewer::convert()
	{
		SPDPointsViewerConvertDialog *convertDialog = new SPDPointsViewerConvertDialog(this);
		convertDialog->exec();
	}

	void SPDPointsViewer::screenshot()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptSave);
		fileDialog->setWindowTitle("Save As - Screenshot (*.png)");
		
		QStringList filters;
		filters << "PNG File (*.png)";
		fileDialog->setNameFilters(filters);
		if(fileDialog->exec() == QDialog::Accepted)
		{
			QStringList files = fileDialog->selectedFiles();
			
			if(files.size() == 1)
			{
				//cout << files[0].toStdString() << endl;
				//openGLWidget->savePlotAsPDF(files[0]);
				QImage image = openGLWidget->grabFrameBuffer(true);
				image.save(files[0], "PNG", -1);
			}
		}
	}

	void SPDPointsViewer::saveProfilePlot()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptSave);
		fileDialog->setWindowTitle("Save As - Profile (*.pdf)");
		
		QStringList filters;
		filters << "PDF File (*.pdf)";
		fileDialog->setNameFilters(filters);
		if(fileDialog->exec() == QDialog::Accepted)
		{
			QStringList files = fileDialog->selectedFiles();
			
			if(files.size() == 1)
			{
				openGLWidget->savePlotAsPDF(files[0]);
			}
		}
	}
	
	void SPDPointsViewer::saveOverviewImage()
	{
		QFileDialog *fileDialog = new QFileDialog();
		fileDialog->setAcceptMode(QFileDialog::AcceptSave);
		fileDialog->setWindowTitle("Save As - Overview (*.png)");
		
		QStringList filters;
		filters << "PNG File (*.png)";
		fileDialog->setNameFilters(filters);
		if(fileDialog->exec() == QDialog::Accepted)
		{
			QStringList files = fileDialog->selectedFiles();
			
			if(files.size() == 1)
			{
				//cout << files[0].toStdString() << endl;
				overviewImage->save(files[0], "PNG", -1);
			}
		}
	}

	void SPDPointsViewer::subset()
	{
		SPDPointsViewerSubsetDialog *subsetDialog = new SPDPointsViewerSubsetDialog(spdFile, bboxSelection, this);
		subsetDialog->exec();
	}

	void SPDPointsViewer::stats()
	{
		
	}

	void SPDPointsViewer::merge()
	{
		
	}

	void SPDPointsViewer::proj4()
	{
		
	}

	void SPDPointsViewer::options()
	{
		SPDPointsViewerPreferences *optionsDialog = new SPDPointsViewerPreferences(NULL, classDisplay, returnDisplay, sourceDisplay, openGLWidget->getBGColour());

		if(optionsDialog->exec() == QDialog::Accepted)
		{
			openGLWidget->updateView();
		}
		delete optionsDialog;
	}

	void SPDPointsViewer::help()
	{
		
	}

	void SPDPointsViewer::about()
	{
		cout << "about\n";
	}

	void SPDPointsViewer::downZoom()
	{
		this->overviewWidget->downZoom();
		overviewWidget->repaint();
	}

	void SPDPointsViewer::upZoom()
	{
		this->overviewWidget->upZoom();
		overviewWidget->repaint();
	}
	
	void SPDPointsViewer::loadAllData()
	{
		unsigned int *bbox = new unsigned int[4];
		bbox[0] = 0;
		bbox[1] = 0;
		bbox[2] = spdFile->getNumberBinsX();
		bbox[3] = spdFile->getNumberBinsY();
		
		overviewWidget->defineStartEndWholeImage();
		this->read3DData(bbox);
	}
    
    void SPDPointsViewer::reloadData()
    {
        if(this->selectionMade)
        {
            unsigned int *bbox = new unsigned int[4];
            bbox[0] = this->bboxSelection[0];
            bbox[1] = this->bboxSelection[1];
            bbox[2] = this->bboxSelection[2];
            bbox[3] = this->bboxSelection[3];
            this->read3DData(bbox);
        }
    }

	void SPDPointsViewer::generateProfileSlot()
	{
		if(genProfileCheckBox->isChecked())
		{
			openGLWidget->setGenerateProfile(true);
			savePlotAction->setEnabled(true);
		}
		else
		{
			openGLWidget->setGenerateProfile(false);
			savePlotAction->setEnabled(false);
		}
	}
	
	void SPDPointsViewer::normWaveformSlot(int)
	{
		if(normWaveformCheckBox->isChecked())
		{
			normWaveform = true;
		}
		else
		{
			normWaveform = false;
		}
	}
	
	void SPDPointsViewer::selectColourTypeSlot(const QString &text)
	{
		QString classificationStr = QString("Classification");
		QString amplitudeStr = QString("Amplitude");
		QString heightStr = QString("Height");
		QString rgbValuesStr = QString("RGB Values");
		QString returnsValuesStr = QString("Returns");
		QString sourceStr = QString("Source");
		QString elevationStr = QString("Elevation");
		QString widthStr = QString("Width");
		
		if(text.compare(text, classificationStr) == 0)
		{
			clrPtType = spdpointsviewer::classColourType;
		}
		else if(text.compare(text, amplitudeStr) == 0)
		{
			clrPtType = spdpointsviewer::amplitudeColourType;
		}
		else if(text.compare(text, rgbValuesStr) == 0)
		{
			clrPtType = spdpointsviewer::rgbColourType;
		}
		else if(text.compare(text, heightStr) == 0)
		{
			clrPtType = spdpointsviewer::heightColourType;
		}
		else if(text.compare(text, returnsValuesStr) == 0)
		{
			clrPtType = spdpointsviewer::returnColourType;
		}
		else if(text.compare(text, sourceStr) == 0)
		{
			clrPtType = spdpointsviewer::sourceColourType;
		}
		else if(text.compare(text, elevationStr) == 0)
		{
			clrPtType = spdpointsviewer::elevationColourType;
		}
		else if(text.compare(text, widthStr) == 0)
		{
			clrPtType = spdpointsviewer::widthColourType;
		}
		else
		{
			this->showErrorMessage("Colour type is not recognised.");
		}
	}
    
    void SPDPointsViewer::selectZFieldSlot(const QString &text)
    {
        QString topoHeightStr = QString("Topo Height");
		QString normHeightStr = QString("Norm Height");
        if(text.compare(text, topoHeightStr) == 0)
		{
			zFieldType = spdpointsviewer::topoHeightType;
		}
		else if(text.compare(text, normHeightStr) == 0)
		{
			zFieldType = spdpointsviewer::normHeightType;
		}
        else
		{
			this->showErrorMessage("Z Field is not recognised.");
		}

    }
    
    void SPDPointsViewer::selectClrTabSlot(const QString &text)
    {
       colourTable = colourTablesFac->getColourTable(text); 
    }

	void SPDPointsViewer::startAnimation()
	{
		QString animationScreenshotPath = "";
		bool takeScreenshots = false;
		bool singleIteration = true;
		bool startAnimation = true;
		
		if(screenshotsCheckBox->isChecked())
		{
			QFileDialog *fileDialog = new QFileDialog();
			fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
			fileDialog->setFileMode(QFileDialog::DirectoryOnly);
			
			if(fileDialog->exec() == QDialog::Accepted)
			{
				QStringList files = fileDialog->selectedFiles();
				
				if(files.size() >= 1)
				{
					animationScreenshotPath = files[0];
					takeScreenshots = true;
				}
			}
			else 
			{
				takeScreenshots = false;
				startAnimation = false;
			}
			delete fileDialog;
		}
		else
		{
			takeScreenshots = false;
		}
		
		if(continuousCheckBox->isChecked())
		{
			singleIteration = false;
		}
		else
		{
			singleIteration = true;
		}
		
		if(startAnimation)
		{
			startAnimationButton->setDisabled(true);
			stopAnimationButton->setDisabled(false);
			
			xRotSlider->setDisabled(true);
			yRotSlider->setDisabled(true);
			zRotSlider->setDisabled(true);
			xShiftSlider->setDisabled(true);
			yShiftSlider->setDisabled(true);
			zShiftSlider->setDisabled(true);
			pointSizeSlider->setDisabled(true);
			rangeSlider->setDisabled(true);
			
			animateThread->reset(singleIteration, takeScreenshots, animationScreenshotPath, degreesMovement);
			QObject::connect(animateThread, SIGNAL(finished()), this, SLOT(finishedAnimation()));
			animateThread->start(QThread::NormalPriority);
		}
		
	}

	void SPDPointsViewer::stopAnimation()
	{
		animateThread->setContinueLoop(false);
		
		startAnimationButton->setDisabled(false);
		stopAnimationButton->setDisabled(true);
		
		xRotSlider->setDisabled(false);
		yRotSlider->setDisabled(false);
		zRotSlider->setDisabled(false);
		xShiftSlider->setDisabled(false);
		yShiftSlider->setDisabled(false);
		zShiftSlider->setDisabled(false);
		pointSizeSlider->setDisabled(false);
		rangeSlider->setDisabled(false);
	}
	
	void SPDPointsViewer::finishedAnimation()
	{
		startAnimationButton->setDisabled(false);
		stopAnimationButton->setDisabled(true);
		
		xRotSlider->setDisabled(false);
		yRotSlider->setDisabled(false);
		zRotSlider->setDisabled(false);
		xShiftSlider->setDisabled(false);
		yShiftSlider->setDisabled(false);
		zShiftSlider->setDisabled(false);
		pointSizeSlider->setDisabled(false);
		rangeSlider->setDisabled(false);
	}
	
	void SPDPointsViewer::degreesMovementSlot(int value)
	{
		degreesMovement = ((float)value)/10;
			
		QString strVal = QString::number(degreesMovement, 'g', 6);
		degreesMovementLabel->setText(strVal);
	}
	
	void SPDPointsViewer::showPointsSlot(int state)
	{
		if(state == Qt::Unchecked)
		{	
			showPtsCheckBox->setCheckState(Qt::Unchecked);
			showPtsCheckBox->setEnabled(false);
			openGLWidget->setShowPoints(false);
			this->loadPoints = false;
		}
		else
		{
			showPtsCheckBox->setCheckState(Qt::Unchecked);
			showPtsCheckBox->setEnabled(true);
			openGLWidget->setShowPoints(true);
			this->loadPoints = true;
		}
	}

	void SPDPointsViewer::showLinesSlot(int state)
	{
		if(state == Qt::Unchecked)
		{	
			showLinesCheckBox->setCheckState(Qt::Unchecked);
			showLinesCheckBox->setEnabled(false);
			openGLWidget->setShowLines(false);
			this->loadVectors = false;
		}
		else
		{
			showLinesCheckBox->setCheckState(Qt::Unchecked);
			showLinesCheckBox->setEnabled(true);
			openGLWidget->setShowLines(true);
			this->loadVectors = true;
		}
	}
	
	void SPDPointsViewer::showWaveformSlot(int state)
	{
		if(state == Qt::Unchecked)
		{	
			showWaveformCheckBox3D->setCheckState(Qt::Unchecked);
			showWaveformCheckBox3D->setEnabled(false);
			openGLWidget->setShowWaveforms(false);
			this->loadWaveform = false;
		}
		else
		{
			showWaveformCheckBox3D->setCheckState(Qt::Unchecked);
			showWaveformCheckBox3D->setEnabled(true);
			openGLWidget->setShowWaveforms(true);
			this->loadWaveform = true;
		}
	}
	
	void SPDPointsViewer::showDTMSlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			loadDTM = false;
		}
		else
		{
			loadDTM = true;
		}
	}
	
	void SPDPointsViewer::showTriSlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowTriangles(false);
			showTriCheckBox3D->setDisabled(true);
			
			showAsWireframeCheckBox->setDisabled(true);
			showLightingCheckBox->setDisabled(true);
		}
		else
		{
			openGLWidget->setShowTriangles(true);
			showTriCheckBox3D->setDisabled(false);
			
			showAsWireframeCheckBox->setDisabled(false);
			showLightingCheckBox->setDisabled(false);
		}
	}
	
	void SPDPointsViewer::showSHPSlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowSHP(false);
			showSHPCheckBox3D->setDisabled(true);
            this->loadSHP = false;
		}
		else
		{
			openGLWidget->setShowSHP(true);
			showSHPCheckBox3D->setDisabled(false);
            this->loadSHP = true;
		}
	}
	
	void SPDPointsViewer::showWaveformDisplaySlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowWaveforms(false);
		}
		else
		{
			openGLWidget->setShowWaveforms(true);
		}
	}
	
	void SPDPointsViewer::showDTMDisplaySlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setDisplayDTM(false);
		}
		else
		{
			openGLWidget->setDisplayDTM(true);
		}
	}
	
	void SPDPointsViewer::showTriDisplaySlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setDisplayTriangles(false);
		}
		else
		{
			openGLWidget->setDisplayTriangles(true);
		}	
	}
	
	void SPDPointsViewer::showSHPDisplaySlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowSHP(false);
		}
		else
		{
			openGLWidget->setShowSHP(true);
		}	
	}
	
	void SPDPointsViewer::showPTSSlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowPoints(false);
		}
		else
		{
			openGLWidget->setShowPoints(true);
		}
	}
	
	void SPDPointsViewer::showLinesDisplaySlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowLines(false);
		}
		else
		{
			openGLWidget->setShowLines(true);
		}
	}
	
	void SPDPointsViewer::showLightingSlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setUseLighting(false);
		}
		else
		{
			openGLWidget->setUseLighting(true);
		}
		
	}
	
	void SPDPointsViewer::showWireframeSlot(int state)
	{
		if(state == Qt::Unchecked)
		{			
			openGLWidget->setShowWireframe(false);
		}
		else
		{
			openGLWidget->setShowWireframe(true);
		}
		
	}
	
	
	void SPDPointsViewer::read3DData(unsigned int *bbox)
	{
		//cout << "\nBBOX (IMG): [" << bbox[0] << "," << bbox[1] << "," << bbox[2] << "," << bbox[3] << "]" << endl;
		
		if(spdFile != NULL)
		{
			openGLWidget->clearData();
			
			progressUpRange  = 1;
			if(loadPoints | loadVectors | loadWaveform)
			{
				progressUpRange += 10;
			}
			if(loadDTM)
			{
				progressUpRange += 10;
			}
			if(loadTris)
			{
				progressUpRange += 10;
			}
			if(loadSHP)
			{
				progressUpRange += 10;
			}
			
			//cout << "progressUprange = " << progressUpRange << endl;
			
			if(selectionMade)
			{
				delete[] bboxSelection;
			}
			selectionMade = true;
			bboxSelection = bbox;
            bool grdReturnsOnly = false;
            if(onlyGrdCheckBox->checkState() == Qt::Checked)
            {
                grdReturnsOnly = true;
            }
			
            //cout << "Create dialog... bbox [" << bbox[0] << "," << bbox[1] << "," << bbox[2] << "," << bbox[3] << "]\n";
			progressDialog = new QProgressDialog(this);
			progressDialog->setLabel(new QLabel("Loading 3D Data..."));
			progressDialog->setRange(0, progressUpRange);
			progressDialog->setCancelButtonText(QString("Ignore"));
			progressDialog->setWindowModality(Qt::WindowModal);
			progressDialog->setValue(0);
            progressDialog->setAutoClose(true);
            progressDialog->setAutoReset(true);
			
			load3DDataThread = new SPDPointsViewerLoad3DData(bbox, openGLWidget, colourTable, spdFile, inputDTM, inputTris, inputSHP, loadPoints, loadVectors, loadDTM, loadTris, loadSHP, loadWaveform, normWaveform, clrPtType, classDisplay, returnDisplay, sourceDisplay, zFieldType, grdReturnsOnly);
			QObject::connect(load3DDataThread, SIGNAL(finished()), this, SLOT(finishedRead3DData()));
			QObject::connect(load3DDataThread, SIGNAL(valueChanged(int)), this, SLOT(feedbackValue(int)));
			QObject::connect(load3DDataThread, SIGNAL(errorMessages(QString)), this, SLOT(showErrorMessage(QString)));
			load3DDataThread->start(QThread::HighPriority);
		}	
	}
	
	void SPDPointsViewer::finishedRead3DData()
	{
        if(progressDialog != NULL)
        {
            progressDialog->setValue(progressUpRange);
        }
		
		//delete progressDialog;
		openGLWidget->updateView();
		tabs->setCurrentIndex(1);
	}
	
	void SPDPointsViewer::showErrorMessage(QString message)
	{
		QErrorMessage *errorDialog = new QErrorMessage(this);
		errorDialog->showMessage(message);
	}

	SPDPointsViewer::~SPDPointsViewer()
	{
		//delete control3DObj;
	}

}
