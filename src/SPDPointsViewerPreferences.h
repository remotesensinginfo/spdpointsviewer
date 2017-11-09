/*
 *  SPDPointsViewerPreferences.h
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


#ifndef SPDPointsViewerPreferences_H
#define SPDPointsViewerPreferences_H

#include <iostream>
#include <string>
#include <map>

#include "spd/SPDCommon.h"

#include "SPDPointsViewer3DWidget.h"
#include "SPDPointsViewerCommon.h"

#include <QtWidgets>

using namespace std;
using namespace spdlib;

namespace spdpointsviewer
{
	class SPDPointsViewerPreferences : public QDialog
	{
		Q_OBJECT
	public:
		SPDPointsViewerPreferences(QWidget *parent, 
                                   QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay,
                                   QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay,
                                   QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay,
                                   QColor *bgColour);
        ~SPDPointsViewerPreferences();
    private slots:
        void classesSliderSlot(int value);
        void returnsSliderSlot(int value);
        void sourcesSliderSlot(int value);
        
        void classComboSlot(const QString &text);
        void returnsComboSlot(const QString &text);
        void sourcesComboSlot(const QString &text);
        
        void classColourSlot();
        void returnsColourSlot();
        void sourcesColourSlot();
        void backgroundColourSlot();
        
        void classApplySlot();
        void returnsApplySlot();
        void sourcesApplySlot();
        
        void classFinishEditSlot();
        void returnsFinishEditSlot();
        void sourcesFinishEditSlot();
    private:
        // Store data values..
        QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay;
        QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay;
        QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay;
        
        CatDisplayInfo *classDisInfo;
        CatDisplayInfo *returnDisInfo;
        CatDisplayInfo *sourcesDisInfo;
        QColor *bgColour;
    
        QSlider *classPointSlider;
        QSlider *returnPointSlider;
        QSlider *sourcesPointSlider;
        
        QComboBox *comboClasses;
        QComboBox *comboReturns;
        QComboBox *comboSources;
        
        QLineEdit *classPtSizeLabel;
        QLineEdit *returnsPtSizeLabel;
        QLineEdit *sourcesPtSizeLabel;
        
        QPushButton *classColourButton;
        QPushButton *returnsColourButton;
        QPushButton *sourcesColourButton;
        QPushButton *backgroundColourButton;
        
        QPushButton *classApplyButton;
        QPushButton *returnsApplyButton;
        QPushButton *sourcesApplyButton;
        
        QPushButton *OKButton;
	};
}

#endif


