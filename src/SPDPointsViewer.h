/*
 *  SPDPointsViewer.h
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

#ifndef POINTSVIEWER_H
#define POINTSVIEWER_H

#include <QtWidgets>

#include "SPDPointsViewerOverviewWidget.h"
#include "SPDPointsViewer3DWidget.h"
#include "SPDPointsViewerPreferences.h"
#include "SPDPointsViewerConvertDialog.h"
#include "SPDPointsViewerControl.h"
#include "SPDPointsViewerLoadOverviewImage.h"
#include "SPDPointsViewerLoad3DData.h"
#include "SPDPointsViewerSubsetDialog.h"
#include "SPDPointsViewerCommon.h"
#include "SPDPointsViewerColourTable.h"

#include "spd/SPDFile.h"
#include "spd/SPDFileReader.h"

using namespace std;
using namespace spdlib;

namespace spdpointsviewer
{
	class SPDPointsViewer : public QMainWindow
	{	
		Q_OBJECT	
	public:
		SPDPointsViewer();
		void loadSPDFile(QString file);
		~SPDPointsViewer();
	private slots:	
		// Slots File Menu
		void open();
		void openDTM();
        void openShapefile();
		void openPTxt();
		void convert();
		void screenshot();
		void saveProfilePlot();
		void saveOverviewImage();
		// Slots Utilities Menu
		void subset();
		void stats();
		void merge();
		void proj4();	
		// Slots Options Menu
		void options();
		// Slots Help Menu
		void help();
		void about();
		// Slots Zoom Level
		void downZoom();
		void upZoom();
		void loadAllData();
        void reloadData();
		void generateProfileSlot();
		void normWaveformSlot(int state);
		void selectColourTypeSlot(const QString &text);
        void selectZFieldSlot(const QString &text);
        void selectClrTabSlot(const QString &text);
		//Slides Slots
		void xRotMovement(int value);
		void yRotMovement(int value);
		void zRotMovement(int value);
		void xShiftMovement(int value);
		void yShiftMovement(int value);
		void zShiftMovement(int value);
		void rangeMovement(int value);
		void pointSizeMovement(int value);
		void reset3DTransformation();
		// Slots Animation
		void startAnimation();
		void stopAnimation();
		void degreesMovementSlot(int value);
		void finishedAnimation();
		// 3D features
		void showPointsSlot(int state);
		void showLinesSlot(int state);
		void showWaveformSlot(int state);
		void showDTMSlot(int state);
		void showTriSlot(int state);
		void showSHPSlot(int state);
		void showWaveformDisplaySlot(int state);
		void showDTMDisplaySlot(int state);
		void showTriDisplaySlot(int state);
		void showSHPDisplaySlot(int state);
		void showPTSSlot(int state);
		void showLinesDisplaySlot(int state);
		void showLightingSlot(int state);
		void showWireframeSlot(int state);
		// Finished Loading Image
		void finishedLoadingImage();
		//User progress feedback
		void feedbackValue(int value);
		//Read 3D data
		void read3DData(unsigned int *bbox);
		void finishedRead3DData();
		void showErrorMessage(QString message);
	private:
		void createMenus();
		void createActions();
		
		QMenu *fileMenu;
		QMenu *optionsMenu;
		QMenu *utilsMenu;
		QMenu *helpMenu;
		
		QAction *openAction;
		QAction *openDTMAction;
		QAction *openSHPAction;
        QAction *openPTxtAction;
		QAction *convertAction;
		QAction *screenshotAction;
		QAction *savePlotAction;
		QAction *saveOverviewAction;
		
		QAction *subsetAction;
		QAction *statsAction;
		QAction *mergeAction;
		QAction *proj4Action;
		
		QAction *optionsAction;
		
		QAction *helpAction;
		QAction *aboutAction;
		
		QPushButton *startAnimationButton;
		QPushButton *stopAnimationButton;
		QCheckBox *genProfileCheckBox;
		QCheckBox *showPointsCheckBoxOverview;
		QCheckBox *showLinesCheckBoxOverview;
		QCheckBox *showWaveformCheckBoxOverview;
		QCheckBox *showWaveformCheckBox3D;
		QCheckBox *showDTMCheckBoxOverview;
		QCheckBox *showDTMCheckBox3D;
		QCheckBox *showTriCheckBoxOverview;
		QCheckBox *showTriCheckBox3D;
		QCheckBox *showSHPCheckBoxOverview;
		QCheckBox *showSHPCheckBox3D;
		QCheckBox *showPtsCheckBox;
		QCheckBox *showLinesCheckBox;
		QCheckBox *showAsWireframeCheckBox;
		QCheckBox *showLightingCheckBox;
		QCheckBox *normWaveformCheckBox;
		QComboBox *comboColourPoints;
        QComboBox *comboZFieldPoints;
        QComboBox *comboColourTables;
		QSlider *xRotSlider;
		QSlider *yRotSlider;
		QSlider *zRotSlider;
		QSlider *xShiftSlider;
		QSlider *yShiftSlider;
		QSlider *zShiftSlider;
		QSlider *rangeSlider;
		QSlider *pointSizeSlider;
		QCheckBox *screenshotsCheckBox;
		QCheckBox *continuousCheckBox;
        QCheckBox *onlyGrdCheckBox;
		QLabel *degreesMovementLabel;
		QProgressDialog *progressDialog;
        unsigned int progressUpRange;
		
		QTabWidget *tabs;
		
		float degreesMovement;
		
		QImage *overviewImage;
		
		SPDPointsViewerOverviewWidget *overviewWidget;
		SPDPointsViewer3DWidget *openGLWidget;
		SPDPointsViewerLoadOverviewImage *loadImageThread;
		SPDPointsViewerLoad3DData *load3DDataThread;
		SPDPointsViewer3DControlObj *animateThread;
        SPDPointsViewerColourTableFactory *colourTablesFac;
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
		bool normWaveform;
		
		ColourPtsType clrPtType;
        
        ZFieldType zFieldType;
		
		QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay;
		QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay;
		QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay;
		
		bool selectionMade;
		unsigned int *bboxSelection;
	};
}
#endif



