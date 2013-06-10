/*
 *  SPDPointsViewerPreferences.cpp
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

#include "SPDPointsViewerPreferences.h"

namespace spdpointsviewer
{

	SPDPointsViewerPreferences::SPDPointsViewerPreferences(QWidget *parent, 
                                                           QMap<boost::uint_fast16_t, CatDisplayInfo> *classDisplay,
                                                           QMap<boost::uint_fast16_t, CatDisplayInfo> *returnDisplay,
                                                           QMap<boost::uint_fast16_t, CatDisplayInfo> *sourceDisplay,
                                                           QColor *bgColour): QDialog(parent)
	{
        this->classDisplay = classDisplay;
        this->returnDisplay = returnDisplay;
        this->sourceDisplay = sourceDisplay;
        this->bgColour = bgColour;
        
        classDisInfo = new CatDisplayInfo();
        returnDisInfo = new CatDisplayInfo();
        sourcesDisInfo = new CatDisplayInfo();
        
        // Get info.
        CatDisplayInfo tmpInfo = classDisplay->value(SPD_UNCLASSIFIED);
        classDisInfo->pointSize = tmpInfo.pointSize;
        classDisInfo->red = tmpInfo.red;
        classDisInfo->green = tmpInfo.green;
        classDisInfo->blue = tmpInfo.blue;
        
        tmpInfo = returnDisplay->value(1);
        returnDisInfo->pointSize = tmpInfo.pointSize;
        returnDisInfo->red = tmpInfo.red;
        returnDisInfo->green = tmpInfo.green;
        returnDisInfo->blue = tmpInfo.blue;
        
        tmpInfo = sourceDisplay->value(0);
        sourcesDisInfo->pointSize = tmpInfo.pointSize;
        sourcesDisInfo->red = tmpInfo.red;
        sourcesDisInfo->green = tmpInfo.green;
        sourcesDisInfo->blue = tmpInfo.blue;
        
        setMinimumSize(475, 500);
        setMaximumSize(475, 500);
        
        int sliderControlMinSize = 200;
        
		// Loop through the classes and make list
        QStringList classesList;
        classesList << "Unclassified" << "Created" << "Ground" << "Low Vegetation" << "Medium Vegetation" << "High Vegetation" << "Building" << "Water" << "Trunk" << "Foliage" << "Branch" << "Wall";
        comboClasses = new QComboBox();
        comboClasses->insertItems(0, classesList);
		comboClasses->setEditable(false);
		QObject::connect(comboClasses, SIGNAL(activated(const QString)), this, SLOT(classComboSlot(const QString)));
        classPointSlider = new QSlider(Qt::Horizontal);
        classPointSlider->setTickInterval(1);
		classPointSlider->setTickPosition(QSlider::TicksBothSides);
		classPointSlider->setRange(1, 10);
		classPointSlider->setMinimumSize(sliderControlMinSize, 10);
		classPointSlider->setTracking(true);
		classPointSlider->setValue(classDisInfo->pointSize);
		connect(classPointSlider, SIGNAL(valueChanged(int)), this, SLOT(classesSliderSlot(int)));
        classPtSizeLabel = new QLineEdit(QString::number(classDisInfo->pointSize));
        classPtSizeLabel->setMaxLength(5);
        connect(classPtSizeLabel, SIGNAL(editingFinished()), this, SLOT(classFinishEditSlot()));
        classColourButton = new QPushButton("Colour");
        connect(classColourButton, SIGNAL(clicked()), this, SLOT(classColourSlot()));
        classApplyButton = new QPushButton("Apply");
        connect(classApplyButton, SIGNAL(clicked()), this, SLOT(classApplySlot()));
                
        QHBoxLayout *hLayoutClassesPart1 = new QHBoxLayout();
		hLayoutClassesPart1->insertWidget(0, comboClasses, 0, Qt::AlignLeft);
		hLayoutClassesPart1->insertWidget(1, classPointSlider, 0, Qt::AlignLeft);
        hLayoutClassesPart1->insertWidget(2, classPtSizeLabel, 0, Qt::AlignLeft);
        QHBoxLayout *hLayoutClassesPart2 = new QHBoxLayout();
        hLayoutClassesPart2->insertSpacing(0, 1);
        hLayoutClassesPart2->insertWidget(1, classColourButton, 0, Qt::AlignRight);
		hLayoutClassesPart2->insertWidget(2, classApplyButton, 0, Qt::AlignRight);
        QVBoxLayout *vLayoutClasses = new QVBoxLayout();
        vLayoutClasses->insertWidget(0, new QLabel("Classes:"), 0, Qt::AlignLeft);
        vLayoutClasses->insertLayout(1, hLayoutClassesPart1, 0);
        vLayoutClasses->insertLayout(2, hLayoutClassesPart2, 0);
        
        // Loop through returns make list
        QStringList returnsList;
        QList<boost::uint_fast16_t> returnsKeys = returnDisplay->keys();
        for(QList<boost::uint_fast16_t>::iterator iterKeys = returnsKeys.begin(); iterKeys != returnsKeys.end(); ++iterKeys)
        {
            returnsList << QString::number(*iterKeys);
        }
        comboReturns = new QComboBox();
        comboReturns->insertItems(0, returnsList);
		comboReturns->setEditable(false);
		QObject::connect(comboReturns, SIGNAL(activated(const QString)), this, SLOT(returnsComboSlot(const QString)));
        returnPointSlider = new QSlider(Qt::Horizontal);
        returnPointSlider->setTickInterval(1);
		returnPointSlider->setTickPosition(QSlider::TicksBothSides);
		returnPointSlider->setRange(1, 10);
		returnPointSlider->setMinimumSize(sliderControlMinSize, 10);
		returnPointSlider->setTracking(true);
		returnPointSlider->setValue(returnDisInfo->pointSize);
		connect(returnPointSlider, SIGNAL(valueChanged(int)), this, SLOT(returnsSliderSlot(int)));
        returnsPtSizeLabel = new QLineEdit(QString::number(returnDisInfo->pointSize));
        returnsPtSizeLabel->setMaxLength(5);
        connect(returnsPtSizeLabel, SIGNAL(editingFinished()), this, SLOT(returnsFinishEditSlot()));
        returnsColourButton = new QPushButton("Colour");
        connect(returnsColourButton, SIGNAL(clicked()), this, SLOT(returnsColourSlot()));
        returnsApplyButton = new QPushButton("Apply");
        connect(returnsApplyButton, SIGNAL(clicked()), this, SLOT(returnsApplySlot()));
        
        QHBoxLayout *hLayoutReturnsPart1 = new QHBoxLayout();
		hLayoutReturnsPart1->insertWidget(0, comboReturns, 0, Qt::AlignLeft);
		hLayoutReturnsPart1->insertWidget(1, returnPointSlider, 0, Qt::AlignLeft);
        hLayoutReturnsPart1->insertWidget(2, returnsPtSizeLabel, 0, Qt::AlignLeft);
        QHBoxLayout *hLayoutReturnsPart2 = new QHBoxLayout();
        hLayoutReturnsPart2->insertSpacing(0, 1);
        hLayoutReturnsPart2->insertWidget(1, returnsColourButton, 0, Qt::AlignRight);
		hLayoutReturnsPart2->insertWidget(2, returnsApplyButton, 0, Qt::AlignRight);
        QVBoxLayout *vLayoutReturns = new QVBoxLayout();
        vLayoutReturns->insertWidget(0, new QLabel("Returns:"), 0, Qt::AlignLeft);
        vLayoutReturns->insertLayout(1, hLayoutReturnsPart1, 0);
        vLayoutReturns->insertLayout(2, hLayoutReturnsPart2, 0);
        
        // Loop through sources and make list
        QStringList sourcesList;
        QList<boost::uint_fast16_t> sourcesKeys = sourceDisplay->keys();
        for(QList<boost::uint_fast16_t>::iterator iterKeys = sourcesKeys.begin(); iterKeys != sourcesKeys.end(); ++iterKeys)
        {
            sourcesList << QString::number(*iterKeys);
        }
        comboSources = new QComboBox();
        comboSources->insertItems(0, sourcesList);
		comboSources->setEditable(false);
		QObject::connect(comboSources, SIGNAL(activated(const QString)), this, SLOT(sourcesComboSlot(const QString)));
        sourcesPointSlider = new QSlider(Qt::Horizontal);
        sourcesPointSlider->setTickInterval(1);
		sourcesPointSlider->setTickPosition(QSlider::TicksBothSides);
		sourcesPointSlider->setRange(1, 10);
		sourcesPointSlider->setMinimumSize(sliderControlMinSize, 10);
		sourcesPointSlider->setTracking(true);
		sourcesPointSlider->setValue(sourcesDisInfo->pointSize);
		connect(sourcesPointSlider, SIGNAL(valueChanged(int)), this, SLOT(sourcesSliderSlot(int)));
        sourcesPtSizeLabel = new QLineEdit(QString::number(sourcesDisInfo->pointSize));
        sourcesPtSizeLabel->setMaxLength(5);
        connect(sourcesPtSizeLabel, SIGNAL(editingFinished()), this, SLOT(sourcesFinishEditSlot()));
        sourcesColourButton = new QPushButton("Colour");
        connect(sourcesColourButton, SIGNAL(clicked()), this, SLOT(sourcesColourSlot()));
        sourcesApplyButton = new QPushButton("Apply");
        connect(sourcesApplyButton, SIGNAL(clicked()), this, SLOT(sourcesApplySlot()));
        
        QHBoxLayout *hLayoutSourcesPart1 = new QHBoxLayout();
		hLayoutSourcesPart1->insertWidget(0, comboSources, 0, Qt::AlignLeft);
		hLayoutSourcesPart1->insertWidget(1, sourcesPointSlider, 0, Qt::AlignLeft);
        hLayoutSourcesPart1->insertWidget(2, sourcesPtSizeLabel, 0, Qt::AlignLeft);
        QHBoxLayout *hLayoutSourcesPart2 = new QHBoxLayout();
        hLayoutSourcesPart2->insertSpacing(0, 1);
        hLayoutSourcesPart2->insertWidget(1, sourcesColourButton, 0, Qt::AlignRight);
		hLayoutSourcesPart2->insertWidget(2, sourcesApplyButton, 0, Qt::AlignRight);
        QVBoxLayout *vLayoutSources = new QVBoxLayout();
        vLayoutSources->insertWidget(0, new QLabel("Sources:"), 0, Qt::AlignLeft);
        vLayoutSources->insertLayout(1, hLayoutSourcesPart1, 0);
        vLayoutSources->insertLayout(2, hLayoutSourcesPart2, 0);
        
        
        // Loop through returns make list
        backgroundColourButton = new QPushButton("Colour");
        connect(backgroundColourButton, SIGNAL(clicked()), this, SLOT(backgroundColourSlot()));

        QHBoxLayout *hLayoutBackground = new QHBoxLayout();
        hLayoutBackground->insertSpacing(0, 1);
        hLayoutBackground->insertWidget(1, new QLabel("Background Colour:"), 0, Qt::AlignLeft);
        hLayoutBackground->insertWidget(2, backgroundColourButton, 0, Qt::AlignRight);
        
        // OK Button
        OKButton = new QPushButton("OK");
        connect(OKButton, SIGNAL(clicked()), this, SLOT(reject()));
        QHBoxLayout *hLayoutOKButton = new QHBoxLayout();
        hLayoutOKButton->insertSpacing(0, 1);
        hLayoutOKButton->insertWidget(1, OKButton, 0, Qt::AlignRight);
        
        /**************** SETUP Final Layout ****************/
		QVBoxLayout *layout = new QVBoxLayout();
		layout->insertLayout(1, vLayoutClasses, 0);
		layout->insertLayout(2, vLayoutReturns, 0);
		layout->insertLayout(3, vLayoutSources, 0);
        layout->insertLayout(4, hLayoutBackground, 0);
		layout->insertLayout(5, hLayoutOKButton, 0);
		setLayout(layout);
		/**************** END Final Layout ****************/
        
	}
    
    void SPDPointsViewerPreferences::classesSliderSlot(int value)
    {
        classDisInfo->pointSize = value;
        classPtSizeLabel->setText(QString::number(value));
    }
    
    void SPDPointsViewerPreferences::returnsSliderSlot(int value)
    {
        returnDisInfo->pointSize = value;
        returnsPtSizeLabel->setText(QString::number(value));
    }
    
    void SPDPointsViewerPreferences::sourcesSliderSlot(int value)
    {
        sourcesDisInfo->pointSize = value;
        sourcesPtSizeLabel->setText(QString::number(value));
    }
    
    void SPDPointsViewerPreferences::classFinishEditSlot()
    {
        classDisInfo->pointSize = classPtSizeLabel->displayText().toUInt();
        classPointSlider->setValue(classDisInfo->pointSize);
    }
    
    void SPDPointsViewerPreferences::returnsFinishEditSlot()
    {
        returnDisInfo->pointSize = returnsPtSizeLabel->displayText().toUInt();
        returnPointSlider->setValue(returnDisInfo->pointSize);
    }
    
    void SPDPointsViewerPreferences::sourcesFinishEditSlot()
    {
        sourcesDisInfo->pointSize = sourcesPtSizeLabel->displayText().toUInt();
        sourcesPointSlider->setValue(sourcesDisInfo->pointSize);
    }
    
    void SPDPointsViewerPreferences::classComboSlot(const QString &text)
    {
        bool found = true;
        uint_fast16_t keyValue = 0;
        if(text == "Unclassified")
        {
            keyValue = SPD_UNCLASSIFIED;
        }
        else if(text == "Created")
        {
            keyValue = SPD_CREATED;
        }
        else if(text == "Ground")
        {
            keyValue = SPD_GROUND;
        }
        else if(text == "Low Vegetation")
        {
            keyValue = SPD_LOW_VEGETATION;
        }
        else if(text == "Medium Vegetation")
        {
            keyValue = SPD_MEDIUM_VEGETATION;
        }
        else if(text == "High Vegetation")
        {
            keyValue = SPD_HIGH_VEGETATION;
        }
        else if(text == "Building")
        {
            keyValue = SPD_BUILDING;
        }
        else if(text == "Water")
        {
            keyValue = SPD_WATER;
        }
        else if(text == "Trunk")
        {
            keyValue = SPD_TRUNK;
        }
        else if(text == "Foliage")
        {
            keyValue = SPD_FOILAGE;
        }
        else if(text == "Branch")
        {
            keyValue = SPD_BRANCH;
        }
        else if(text == "Wall")
        {
            keyValue = SPD_WALL;
        }
        else
        {
            found = false;
        }
        
        if(found)
        {
            CatDisplayInfo tmpInfo = classDisplay->value(keyValue);
            classDisInfo->pointSize = tmpInfo.pointSize;
            classDisInfo->red = tmpInfo.red;
            classDisInfo->green = tmpInfo.green;
            classDisInfo->blue = tmpInfo.blue;
            
            classPointSlider->setValue(classDisInfo->pointSize);
            classPtSizeLabel->setText(QString::number(classDisInfo->pointSize));
        }
    }
    
    void SPDPointsViewerPreferences::returnsComboSlot(const QString &text)
    {
        uint_fast16_t keyValue = text.toInt();
        CatDisplayInfo tmpInfo = returnDisplay->value(keyValue);
        returnDisInfo->pointSize = tmpInfo.pointSize;
        returnDisInfo->red = tmpInfo.red;
        returnDisInfo->green = tmpInfo.green;
        returnDisInfo->blue = tmpInfo.blue;
        
        returnPointSlider->setValue(returnDisInfo->pointSize);
        returnsPtSizeLabel->setText(QString::number(returnDisInfo->pointSize));
    }
    
    void SPDPointsViewerPreferences::sourcesComboSlot(const QString &text)
    {
        uint_fast16_t keyValue = text.toInt();
        CatDisplayInfo tmpInfo = sourceDisplay->value(keyValue);
        sourcesDisInfo->pointSize = tmpInfo.pointSize;
        sourcesDisInfo->red = tmpInfo.red;
        sourcesDisInfo->green = tmpInfo.green;
        sourcesDisInfo->blue = tmpInfo.blue;
        
        sourcesPointSlider->setValue(sourcesDisInfo->pointSize);
        sourcesPtSizeLabel->setText(QString::number(sourcesDisInfo->pointSize));
    }
    
    void SPDPointsViewerPreferences::classColourSlot()
    {
        QColor tmpColor;
        tmpColor.setRgbF(classDisInfo->red, classDisInfo->green, classDisInfo->blue);
        
        QColorDialog *colorDialog = new QColorDialog(tmpColor, this);
		if(colorDialog->exec() == QDialog::Accepted)
		{
			tmpColor = colorDialog->selectedColor();
            classDisInfo->red = tmpColor.redF();
            classDisInfo->green = tmpColor.greenF();
            classDisInfo->blue = tmpColor.blueF();
		}
		delete colorDialog;
    }
    
    void SPDPointsViewerPreferences::returnsColourSlot()
    {
        QColor tmpColor;
        tmpColor.setRgbF(returnDisInfo->red, returnDisInfo->green, returnDisInfo->blue);
        
        QColorDialog *colorDialog = new QColorDialog(tmpColor, this);
		if(colorDialog->exec() == QDialog::Accepted)
		{
			tmpColor = colorDialog->selectedColor();
            returnDisInfo->red = tmpColor.redF();
            returnDisInfo->green = tmpColor.greenF();
            returnDisInfo->blue = tmpColor.blueF();
		}
		delete colorDialog;
    }
    
    void SPDPointsViewerPreferences::sourcesColourSlot()
    {
        QColor tmpColor;
        tmpColor.setRgbF(sourcesDisInfo->red, sourcesDisInfo->green, sourcesDisInfo->blue);
        
        QColorDialog *colorDialog = new QColorDialog(tmpColor, this);
		if(colorDialog->exec() == QDialog::Accepted)
		{
			tmpColor = colorDialog->selectedColor();
            sourcesDisInfo->red = tmpColor.redF();
            sourcesDisInfo->green = tmpColor.greenF();
            sourcesDisInfo->blue = tmpColor.blueF();
		}
		delete colorDialog;
    }
    
    void SPDPointsViewerPreferences::backgroundColourSlot()
    {       
        QColorDialog *colorDialog = new QColorDialog(*bgColour, this);
		if(colorDialog->exec() == QDialog::Accepted)
		{
			*bgColour = colorDialog->selectedColor();
		}
		delete colorDialog;
    }
    
    void SPDPointsViewerPreferences::classApplySlot()
    {
        QString text = comboClasses->currentText();
        bool found = true;
        uint_fast16_t keyValue = 0;
        if(text == "Unclassified")
        {
            keyValue = SPD_UNCLASSIFIED;
        }
        else if(text == "Created")
        {
            keyValue = SPD_CREATED;
        }
        else if(text == "Ground")
        {
            keyValue = SPD_GROUND;
        }
        else if(text == "Low Vegetation")
        {
            keyValue = SPD_LOW_VEGETATION;
        }
        else if(text == "Medium Vegetation")
        {
            keyValue = SPD_MEDIUM_VEGETATION;
        }
        else if(text == "High Vegetation")
        {
            keyValue = SPD_HIGH_VEGETATION;
        }
        else if(text == "Building")
        {
            keyValue = SPD_BUILDING;
        }
        else if(text == "Water")
        {
            keyValue = SPD_WATER;
        }
        else if(text == "Trunk")
        {
            keyValue = SPD_TRUNK;
        }
        else if(text == "Foliage")
        {
            keyValue = SPD_FOILAGE;
        }
        else if(text == "Branch")
        {
            keyValue = SPD_BRANCH;
        }
        else if(text == "Wall")
        {
            keyValue = SPD_WALL;
        }
        else
        {
            found = false;
        }
        
        if(found)
        {
            classDisplay->remove(keyValue);
            CatDisplayInfo tmpInfoNew;
            tmpInfoNew.pointSize = classDisInfo->pointSize;
            tmpInfoNew.red = classDisInfo->red;
            tmpInfoNew.green = classDisInfo->green;
            tmpInfoNew.blue = classDisInfo->blue;
            classDisplay->insert(keyValue, tmpInfoNew);
        }
    }
    
    void SPDPointsViewerPreferences::returnsApplySlot()
    {
        uint_fast16_t keyValue = comboReturns->currentText().toInt();
        
        returnDisplay->remove(keyValue);
        CatDisplayInfo tmpInfoNew;
        tmpInfoNew.pointSize = returnDisInfo->pointSize;
        tmpInfoNew.red = returnDisInfo->red;
        tmpInfoNew.green = returnDisInfo->green;
        tmpInfoNew.blue = returnDisInfo->blue;
        returnDisplay->insert(keyValue, tmpInfoNew);
    }
    
    void SPDPointsViewerPreferences::sourcesApplySlot()
    {
        uint_fast16_t keyValue = comboSources->currentText().toInt();
        
        sourceDisplay->remove(keyValue);
        CatDisplayInfo tmpInfoNew;
        tmpInfoNew.pointSize = sourcesDisInfo->pointSize;
        tmpInfoNew.red = sourcesDisInfo->red;
        tmpInfoNew.green = sourcesDisInfo->green;
        tmpInfoNew.blue = sourcesDisInfo->blue;
        sourceDisplay->insert(keyValue, tmpInfoNew);
    }
    
    SPDPointsViewerPreferences::~SPDPointsViewerPreferences()
    {
        
    }
}

