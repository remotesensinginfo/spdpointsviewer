/*
 *  SPDPointsViewerColourTable.cpp
 *  SPDPointsViewer
 *
 *  Created by Pete Bunting on 10/01/2012.
 *  Copyright 2012 SPD3DPointsViewer.
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

#include "SPDPointsViewerColourTable.h"

namespace spdpointsviewer
{
   
    SPDPointsViewerColourTableFactory::SPDPointsViewerColourTableFactory()
    {
        this->colourTabs = new vector<SPDPointsViewerColourTable*>();
        this->createDefaultColourTables();
    }
    
    QStringList SPDPointsViewerColourTableFactory::getAvailableColourTableNames()
    {
        QStringList names = QStringList();
        for(vector<SPDPointsViewerColourTable*>::iterator iterCTs = this->colourTabs->begin(); iterCTs != this->colourTabs->end(); ++iterCTs)
        {
            names << (*iterCTs)->getName();
        }
        return names;
    }
    
    SPDPointsViewerColourTable* SPDPointsViewerColourTableFactory::getColourTable(QString name)
    {
        SPDPointsViewerColourTable *ct = NULL;
        for(vector<SPDPointsViewerColourTable*>::iterator iterCTs = this->colourTabs->begin(); iterCTs != this->colourTabs->end(); ++iterCTs)
        {
            if((*iterCTs)->getName() == name)
            {
                ct = (*iterCTs);
                break;
            }
        }
        return ct;
    }
        
    void SPDPointsViewerColourTableFactory::createAndAddColourTable(QString file)
    {
        
    }
    
    void SPDPointsViewerColourTableFactory::createDefaultColourTables()
    {
        this->colourTabs->push_back(this->createColourTabHue());
        this->colourTabs->push_back(this->createColourTabGreyscale());
        this->colourTabs->push_back(this->createColourTab16Level());
        this->colourTabs->push_back(this->createColourTabBWLinear());
        this->colourTabs->push_back(this->createColourTabBeach());
        this->colourTabs->push_back(this->createColourTabBGRY());
        this->colourTabs->push_back(this->createColourTabBluePastelRed());
        this->colourTabs->push_back(this->createColourTabBlueRed());
        this->colourTabs->push_back(this->createColourTabBlueWave());
        this->colourTabs->push_back(this->createColourTabBlueWhite());
        this->colourTabs->push_back(this->createColourTabEOSA());
        this->colourTabs->push_back(this->createColourTabEOSB());
        this->colourTabs->push_back(this->createColourTabGreenPink());
        this->colourTabs->push_back(this->createColourTabGreenWhiteLinear());
        this->colourTabs->push_back(this->createColourTabGrnRedBluWht());
        this->colourTabs->push_back(this->createColourTabGrnWhtExp());
        this->colourTabs->push_back(this->createColourTabHardCandy());
        this->colourTabs->push_back(this->createColourTabHaze());
        this->colourTabs->push_back(this->createColourTabHueSatLight1());
        this->colourTabs->push_back(this->createColourTabHueSatLight2());
        this->colourTabs->push_back(this->createColourTabHueSatVal1());
        this->colourTabs->push_back(this->createColourTabHueSatVal2());
        this->colourTabs->push_back(this->createColourTabMacStyle());
        this->colourTabs->push_back(this->createColourTabNature());
        this->colourTabs->push_back(this->createColourTabOcean());
        this->colourTabs->push_back(this->createColourTabPastels());
        this->colourTabs->push_back(this->createColourTabPeppermint());
        this->colourTabs->push_back(this->createColourTabPlasma());
        this->colourTabs->push_back(this->createColourTabPrism());
        this->colourTabs->push_back(this->createColourTabPurpleRedStripes());
        this->colourTabs->push_back(this->createColourTabRainbowBlack());
        this->colourTabs->push_back(this->createColourTabRainbowWhite());
        this->colourTabs->push_back(this->createColourTabRainbow());
        this->colourTabs->push_back(this->createColourTabRainbow18());
        this->colourTabs->push_back(this->createColourTabRedPurple());
        this->colourTabs->push_back(this->createColourTabRedTemp());
        this->colourTabs->push_back(this->createColourTabStdGamma());
        this->colourTabs->push_back(this->createColourTabSteps());
        this->colourTabs->push_back(this->createColourTabSternSpecial());
        this->colourTabs->push_back(this->createColourTabVolcano());
        this->colourTabs->push_back(this->createColourTabWaves());
    }
    
    SPDPointsViewerColourTableFactory::~SPDPointsViewerColourTableFactory()
    {
        
    }
    
    
    
    
    
    SPDPointsViewerColourTable::SPDPointsViewerColourTable()
    {
        clrs = new vector<ClrVals>();
    }
    
    void SPDPointsViewerColourTable::setName(QString name)
    {
        this->name = name;
    }
               
    QString SPDPointsViewerColourTable::getName()
    {
        return this->name;
    }
    
    void SPDPointsViewerColourTable::setMinVal(unsigned int minVal)
    {
        this->minVal = minVal;
    }
    
    unsigned int SPDPointsViewerColourTable::getMinVal()
    {
        return minVal;
    }
    
    void SPDPointsViewerColourTable::setMaxVal(unsigned int maxVal)
    {
        this->maxVal = maxVal;
    }
    
    unsigned int SPDPointsViewerColourTable::getMaxVal()
    {
        return maxVal;
    }
    
    QColor SPDPointsViewerColourTable::findColour(unsigned int val)
    {
        QColor outColor = QColor::fromRgb(0,0,0,255);
        bool foundVal = false;
        
        for(vector<ClrVals>::iterator iterClrs = clrs->begin(); iterClrs != clrs->end(); ++iterClrs)
        {
            if((*iterClrs).val == val)
            {
                outColor.setRgbF((*iterClrs).red, (*iterClrs).green, (*iterClrs).blue);
                foundVal = true;
                break;
            }
        }
        
        if(!foundVal)
        {
            throw SPDPointsViewerException("Couldn't find value within Colour Table!");
        }
        
        return outColor;
    }
    
    void SPDPointsViewerColourTable::addColorValPair(ClrVals clrVal)
    {
        if(clrs->empty())
        {
            this->minVal = clrVal.val;
            this->maxVal = clrVal.val;
        }
        else if(clrVal.val < this->minVal)
        {
            this->minVal = clrVal.val;
        }
        else if (clrVal.val > this->maxVal)
        {
            this->maxVal = clrVal.val;
        }
        
        clrs->push_back(clrVal);
    }
    
    unsigned int SPDPointsViewerColourTable::scaleVal(float val)
    {
        if((val < 0) | (val > 1))
        {
            cout << "Val  = " << val << endl;
            throw SPDPointsViewerException("Input value should be between 0 and 1.");
        }
        
        float outFloatVal = this->minVal + (val * (this->maxVal - this->minVal));
        unsigned int outUIntVal = floor(outFloatVal);
        
        return outUIntVal;
    }
    
    SPDPointsViewerColourTable::~SPDPointsViewerColourTable()
    {
        delete clrs;
    }
}
