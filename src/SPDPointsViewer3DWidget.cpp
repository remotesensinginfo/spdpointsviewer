/*
 *  SPDPointsViewer3DWidget.cpp
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

#include "SPDPointsViewer3DWidget.h"

namespace spdpointsviewer
{

	SPDPointsViewer3DWidget::SPDPointsViewer3DWidget(QWidget *parent): QGLWidget(parent)
	{
		setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
		
		rotationX = 120.0;
		rotationY = 180.0;
		rotationZ = 180.0;
		
		shiftX = 0;
		shiftY = 0;
		shiftZ = 0;
		
		nRange = 100.0f;
		
		pointSizeMulti = 1.0f;
		
		bgColor = new QColor(Qt::black);
		
		dataRead = false;
		
		lineColor = new QColor(Qt::blue);
		lines = NULL;
		showLines = false;
		linesRead = false;
		
		points = NULL;
		showPoints = false;
		pointsRead = false;
		
		waveforms = NULL;
		showWaveforms = false;
		waveformsRead = false;
		
		numTriDTMVertInRow = 0;
		numTrisDTMInRow = 0;
		numTriDTMRows = 0;
		coordsXTriDTM = NULL;
		coordsYTriDTM = NULL;
		coordsZTriDTM = NULL;
		normXTriDTM = NULL;
		normYTriDTM = NULL;
		normZTriDTM = NULL;
		
		dtmReadIn = false;
		displayDTM = false;
		
		dtmColour = new QColor(Qt::red);
		
		surfaceWireframe = false;
		surfaceLighting = true;
		
        shpLineColor = new QColor(Qt::red);
		shpPointlines = NULL;
		showSHPLines = false;
        shpLinesRead = false;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		generateProfile = false;
		displayProfile = NULL;
		
		
		showTrisVal = false;
		trisReadIn = false;
		
		
		displayTris = true;

		
	}

	void SPDPointsViewer3DWidget::setXRotation(GLfloat xRot)
	{
		this->rotationX = xRot;
		updateGL();
	}

	void SPDPointsViewer3DWidget::setYRotation(GLfloat yRot)
	{
		this->rotationY = yRot;
		updateGL();
	}

	void SPDPointsViewer3DWidget::setZRotation(GLfloat zRot)
	{
		this->rotationZ = zRot;
		updateGL();
	}
		
	void SPDPointsViewer3DWidget::setXShift(GLfloat xShift)
	{
		this->shiftX = xShift;
		updateGL();
	}

	void SPDPointsViewer3DWidget::setYShift(GLfloat yShift)
	{
		this->shiftY = yShift;
		updateGL();
	}

	void SPDPointsViewer3DWidget::setZShift(GLfloat zShift)
	{
		this->shiftZ = zShift;
		updateGL();
	}

	void SPDPointsViewer3DWidget::setRange(GLfloat range)
	{
		this->nRange = range;
		updateGL();
	}
	
	void SPDPointsViewer3DWidget::reset3DTrans()
	{
		rotationX = 120.0;
		rotationY = 180.0;
		rotationZ = 180.0;
		
		shiftX = 0;
		shiftY = 0;
		shiftZ = 0;
		
		pointSizeMulti = 1;
		
		nRange = 100.0f;
		updateGL();
	}
	
	void SPDPointsViewer3DWidget::clearData()
	{
		delete this->points;
		delete this->lines;
		this->pointsRead = false;
		this->dataRead = false;
		this->linesRead = false;
        
        if(this->shpLinesRead)
        {
            delete this->shpPointlines;
            this->shpLinesRead = false;
        }
	}

	void SPDPointsViewer3DWidget::setBGColour(QColor bgColour)
	{
		this->bgColor->setRed(bgColour.red());
		this->bgColor->setGreen(bgColour.green());
		this->bgColor->setBlue(bgColour.blue());
	}

	QColor* SPDPointsViewer3DWidget::getBGColour()
	{
		return bgColor;
	}
	
	void SPDPointsViewer3DWidget::setPointSizeMulti(float sizeMulti)
	{
		this->pointSizeMulti = sizeMulti;
		updateGL();
	}
	
	
	void SPDPointsViewer3DWidget::setPoints(vector<SimpleColour3DPoint> *points)
	{
		this->points = points;
		this->pointsRead = true;
		this->dataRead = true;
	}
	
	void SPDPointsViewer3DWidget::setShowPoints(bool showPoints)
	{
		this->showPoints = showPoints;
		updateGL();
	}
	
	bool SPDPointsViewer3DWidget::getShowPoints()
	{
		return showPoints;
	}
	
	void SPDPointsViewer3DWidget::setLineColour(QColor *lineColour)
	{
		this->lineColor = lineColour;
	}
	
	QColor* SPDPointsViewer3DWidget::getLineColour()
	{
		return lineColor;
	}
	
	void SPDPointsViewer3DWidget::setLines(vector<Simple3DPoint> *lines)
	{
		this->lines = lines;
		this->linesRead = true;
		this->dataRead = true;
	}
	
	void SPDPointsViewer3DWidget::setShowLines(bool showLines)
	{
		this->showLines = showLines;
		updateGL();
	}
	
	bool SPDPointsViewer3DWidget::getShowLines()
	{
		return showLines;
	}
	
	void SPDPointsViewer3DWidget::setWaveforms(vector<SimpleColour3DPoint> *waveforms)
	{
		this->waveforms = waveforms;
		this->waveformsRead = true;
		this->dataRead = true;
	}
	
	void SPDPointsViewer3DWidget::setShowWaveforms(bool showWaveforms)
	{
		this->showWaveforms = showWaveforms;
		updateGL();
	}
	
	bool SPDPointsViewer3DWidget::getShowWaveforms()
	{
		return showWaveforms;
	}
	
	void SPDPointsViewer3DWidget::setDTMSurface(unsigned long numTriDTMVertInRow, unsigned long numTrisDTMInRow, unsigned long numTriDTMRows, GLfloat **coordsXTriDTM, GLfloat **coordsYTriDTM, GLfloat **coordsZTriDTM, GLfloat **normXTriDTM, GLfloat **normYTriDTM, GLfloat **normZTriDTM)
	{
		this->numTriDTMVertInRow = numTriDTMVertInRow;
		this->numTrisDTMInRow = numTrisDTMInRow;
		this->numTriDTMRows = numTriDTMRows;
		this->coordsXTriDTM = coordsXTriDTM;
		this->coordsYTriDTM = coordsYTriDTM;
		this->coordsZTriDTM = coordsZTriDTM;
		this->normXTriDTM = normXTriDTM;
		this->normYTriDTM = normYTriDTM;
		this->normZTriDTM = normZTriDTM;
		
		this->dtmReadIn = true;
	}
	
	void SPDPointsViewer3DWidget::setDisplayDTM(bool displayDTM)
	{
		this->displayDTM = displayDTM;
		this->updateGL();
	}
	
	bool SPDPointsViewer3DWidget::getDisplayDTM()
	{
		return displayDTM;
	}
	
	QColor* SPDPointsViewer3DWidget::getDTMColour()
	{
		return dtmColour;
	}
	
	void SPDPointsViewer3DWidget::setShowWireframe(bool showWireframe)
	{
		this->surfaceWireframe = showWireframe;
		this->updateGL();
	}
	
	bool SPDPointsViewer3DWidget::showWireframe()
	{
		return surfaceWireframe;
	}
	
	void SPDPointsViewer3DWidget::setUseLighting(bool useLighting)
	{
		this->surfaceLighting = useLighting;
		this->updateGL();
	}
	
	bool SPDPointsViewer3DWidget::useLighting()
	{
		return surfaceLighting;
	}
	
	void SPDPointsViewer3DWidget::setSHPLineColour(QColor *shpLineColour)
    {
        this->shpLineColor = shpLineColour;
    }
    
    QColor* SPDPointsViewer3DWidget::getSPDLineColour()
    {
        return this->shpLineColor;
    }
    
    void SPDPointsViewer3DWidget::setSHPLines(vector<Simple3DPoint> *lines)
    {
        this->shpPointlines = lines;
		this->shpLinesRead = true;
    }
    
    void SPDPointsViewer3DWidget::setShowSHP(bool showSHP)
    {
        showSHPLines = showSHP;
        this->updateGL();
    }
    
    bool SPDPointsViewer3DWidget::showSHP()
    {
        return this->showSHPLines;
    }

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	void SPDPointsViewer3DWidget::setShowTriangles(bool showTris)
	{
		this->showTrisVal = showTris;
	}
	
	bool SPDPointsViewer3DWidget::showTriangles()
	{
		return this->showTrisVal;
	}
	
	
		
	void SPDPointsViewer3DWidget::setDisplayTriangles(bool displayTriangles)
	{
		this->displayTris = displayTriangles;
		this->updateGL();
	}
	
	bool SPDPointsViewer3DWidget::getDisplayTriangles()
	{
		return displayTris;
	}
	
	
	
	
	


	void SPDPointsViewer3DWidget::updateView()
	{
		updateGL();
	}

	void SPDPointsViewer3DWidget::setGenerateProfile(bool generateProfile)
	{
		this->generateProfile = generateProfile;
	}

	void SPDPointsViewer3DWidget::savePlotAsPDF(QString filepath)
	{
		displayProfile->savePlot(filepath);
	}

	void SPDPointsViewer3DWidget::initializeGL()
	{
		qglClearColor(bgColor->rgb());
		//glShadeModel(GL_FLAT);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
	}

	void SPDPointsViewer3DWidget::resizeGL(int widthIn, int heightIn)
	{
		this->heightStored = heightIn;
		this->widthStored = widthIn;
		
		if(heightStored == 0)
		{
			heightStored = 1;
		}
		
		glViewport(0, 0, widthStored, heightStored);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		if (widthStored <= heightStored)
		{
			glOrtho (-nRange, nRange, -nRange*heightStored/widthStored, nRange*heightStored/widthStored, -nRange, nRange);
		}
		else
		{
			glOrtho (-nRange*widthStored/heightStored, nRange*widthStored/heightStored, -nRange, nRange, -nRange, nRange);
		}
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void SPDPointsViewer3DWidget::paintGL()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
	}

	void SPDPointsViewer3DWidget::mousePressEvent(QMouseEvent *event)
	{
		lastPos = event->pos();
	}

	void SPDPointsViewer3DWidget::mouseMoveEvent(QMouseEvent *event)	
	{
		GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
		GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
		if (event->buttons() & Qt::LeftButton) 
		{
			rotationX += 180 * dy;
			rotationY += 180 * dx;
			updateGL();
		} 
		else if (event->buttons() & Qt::RightButton) 
		{
			rotationX += 180 * dy;
			rotationZ += 180 * dx;
			updateGL();
		}
		lastPos = event->pos();
	}
    
    void SPDPointsViewer3DWidget::wheelEvent(QWheelEvent *event)
    {
        int numDegrees = event->delta() / 8;
        
        if (event->orientation() == Qt::Horizontal) 
        {
            this->setZRotation(this->rotationZ + numDegrees);
        } 
        else 
        {
            GLfloat tmpRange = this->nRange + numDegrees/2;
            if(tmpRange < 0)
            {
                tmpRange = 1;
            }
            this->setRange(tmpRange);
        }
        event->accept();
    }

	void SPDPointsViewer3DWidget::draw()
	{
		if(pointSizeMulti > 4)
		{
			glEnable(GL_POINT_SMOOTH);
		}
		else
		{
			glDisable(GL_POINT_SMOOTH);
		}
		
		qglClearColor(bgColor->rgb());
		
		if(heightStored == 0)
		{
			heightStored = 1;
		}
		glViewport(0, 0, widthStored, heightStored);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
				
		if(nRange > 4)
		{
			if (widthStored <= heightStored)
			{
				glOrtho(-nRange, nRange, -nRange*heightStored/widthStored, nRange*heightStored/widthStored, -nRange, nRange);
			}
			else
			{
				glOrtho (-nRange*widthStored/heightStored, nRange*widthStored/heightStored, -nRange, nRange, -nRange, nRange);
			}
		}
		else if(nRange < 1)
		{
			if (widthStored <= heightStored)
			{
				glOrtho(-nRange, nRange, -nRange*heightStored/widthStored, nRange*heightStored/widthStored, -nRange-2, nRange+4);
			}
			else
			{
				glOrtho (-nRange*widthStored/heightStored, nRange*widthStored/heightStored, -nRange, nRange, -nRange-2, nRange+4);
			}
		}
		else
		{
			if (widthStored <= heightStored)
			{
				glOrtho(-nRange, nRange, -nRange*heightStored/widthStored, nRange*heightStored/widthStored, -nRange, nRange+2);
			}
			else
			{
				glOrtho (-nRange*widthStored/heightStored, nRange*widthStored/heightStored, -nRange, nRange, -nRange, nRange+2);
			}
			
		}
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// Clear the window with current clearing color
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Save matrix state and do the rotation
		glPushMatrix();
		glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
		glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
		
		glTranslatef(shiftX, shiftY, shiftZ);
		
		if(dataRead)
		{
			if(showPoints & (points != NULL))
			{
				bool first = true;
				float ptSize = 0;
				
				vector<SimpleColour3DPoint>::iterator iterPts;
				for(iterPts = points->begin(); iterPts != points->end(); ++iterPts)
				{
					if(first)
					{
						glPointSize((((*iterPts).ptSize) * pointSizeMulti));
						glBegin(GL_POINTS);
						ptSize = (*iterPts).ptSize;
						first = false;
					}
					else if(ptSize != (*iterPts).ptSize)
					{
						glEnd();
						glPointSize((((*iterPts).ptSize) * pointSizeMulti));
						glBegin(GL_POINTS);
						ptSize = (*iterPts).ptSize;
					}					
					glColor3f((*iterPts).r, (*iterPts).g, (*iterPts).b);
					glVertex3f((*iterPts).x, (*iterPts).y, (*iterPts).z);
					
				}
				glEnd();
			}
			
			if(showLines & (lines != NULL))
			{
				glColor3f(lineColor->red(), lineColor->green(), lineColor->blue());
				glBegin(GL_LINES);
				vector<Simple3DPoint>::iterator iterPts;
				for(iterPts = lines->begin(); iterPts != lines->end(); ++iterPts)
				{
					glVertex3f((*iterPts).x, (*iterPts).y, (*iterPts).z);
				}
				glEnd();
			}
			
			if(showWaveforms & (waveforms != NULL))
			{
				bool first = true;
				float ptSize = 0;
				
				vector<SimpleColour3DPoint>::iterator iterPts;
				for(iterPts = waveforms->begin(); iterPts != waveforms->end(); ++iterPts)
				{
					if(first)
					{
						glPointSize((((*iterPts).ptSize) * pointSizeMulti));
						glBegin(GL_POINTS);
						ptSize = (*iterPts).ptSize;
						first = false;
					}
					else if(ptSize != (*iterPts).ptSize)
					{
						glEnd();
						glPointSize((((*iterPts).ptSize) * pointSizeMulti));
						glBegin(GL_POINTS);
						ptSize = (*iterPts).ptSize;
					}					
					glColor3f((*iterPts).r, (*iterPts).g, (*iterPts).b);
					glVertex3f((*iterPts).x, (*iterPts).y, (*iterPts).z);
				}
				glEnd();
			}
			
			if(dtmReadIn & displayDTM)
			{
				GLfloat prev2X = 0;
				GLfloat prev2Y = 0;
				GLfloat prev2Z = 0;
				
				GLfloat prev1X = 0;
				GLfloat prev1Y = 0;
				GLfloat prev1Z = 0;
				
				qreal red = 0;
				qreal blue = 0;
				qreal green = 0;
				qreal alpha = 0;
				
				dtmColour->getRgbF(&red, &green, &blue, &alpha);
				
				if(surfaceLighting)
				{
					// Enable lighting
					glEnable(GL_LIGHTING);
					
					GLfloat  ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
					GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
					
					glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
					glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
					glEnable(GL_LIGHT0);
					
					glEnable(GL_COLOR_MATERIAL);
					glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
				}
				else
				{
					glDisable(GL_LIGHTING);
				}
				
				if(surfaceWireframe)
				{
					glPolygonMode(GL_FRONT,GL_LINE);
					glPolygonMode(GL_BACK,GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT,GL_FILL);
					glPolygonMode(GL_BACK,GL_FILL);
				}
				
				unsigned long normVecCount = 0;
				
				for(unsigned int i = 0; i < numTriDTMRows; ++i)
				{
					prev2X = coordsXTriDTM[i][0];
					prev2Y = coordsYTriDTM[i][0];
					prev2Z = coordsZTriDTM[i][0];
					
					prev1X = coordsXTriDTM[i][1];
					prev1Y = coordsYTriDTM[i][1];
					prev1Z = coordsZTriDTM[i][1];
					
					normVecCount = 0;
					
					
					glColor3f(red, green, blue);
					for(unsigned int j = 2; j < numTriDTMVertInRow; ++j)
					{
						glBegin(GL_TRIANGLES);
						glNormal3f(normXTriDTM[i][normVecCount], normYTriDTM[i][normVecCount], normZTriDTM[i][normVecCount]);
						++normVecCount;
						
						if((j % 2) == 0)
						{
							glVertex3f(prev2X, prev2Y, prev2Z);
							glVertex3f(prev1X, prev1Y, prev1Z);
							glVertex3f(coordsXTriDTM[i][j], coordsYTriDTM[i][j], coordsZTriDTM[i][j]);
						}
						else 
						{
							glVertex3f(prev2X, prev2Y, prev2Z);
							glVertex3f(coordsXTriDTM[i][j], coordsYTriDTM[i][j], coordsZTriDTM[i][j]);
							glVertex3f(prev1X, prev1Y, prev1Z);
						}
						glEnd();
						
						prev2X = prev1X;
						prev2Y = prev1Y;
						prev2Z = prev1Z;
						
						prev1X = coordsXTriDTM[i][j];
						prev1Y = coordsYTriDTM[i][j];
						prev1Z = coordsZTriDTM[i][j];
					}
				}
			}
            
            if(showSHPLines & (shpPointlines != NULL))
            {
                glColor3f(shpLineColor->red(), shpLineColor->green(), shpLineColor->blue());
				glBegin(GL_LINES);
				vector<Simple3DPoint>::iterator iterPts;
				for(iterPts = shpPointlines->begin(); iterPts != shpPointlines->end(); ++iterPts)
				{
					glVertex3f((*iterPts).x, (*iterPts).y, (*iterPts).z);
				}
				glEnd();
            }
			
			if(trisReadIn & displayTris)
			{
				
			}
		}
		else 
		{
			glPointSize((10 * pointSizeMulti));
			glBegin(GL_POINTS);
			glColor3f(1, 0, 0);
			glVertex3f(-50, -30, 0);
			glVertex3f(-40, -30, 0);
			glVertex3f(-30, -20, 0);
			glVertex3f(-30, -10, 0);
			glVertex3f(-40, 0, 0);
			glVertex3f(-50, 10, 0);
			glVertex3f(-50, 20, 0);
			glVertex3f(-40, 30, 0);
			glVertex3f(-30, 30, 0);
			glColor3f(0, 1, 0);
			glVertex3f(-10, -30, 0);
			glVertex3f(-10, -20, 0);
			glVertex3f(-10, -10, 0);
			glVertex3f(-10, 0, 0);
			glVertex3f(-10, 10, 0);
			glVertex3f(-10, 20, 0);
			glVertex3f(-10, 30, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(10, 10, 0);
			glVertex3f(10, 20, 0);
			glVertex3f(0, 30, 0);
			glColor3f(0, 0, 1);
			glVertex3f(30, -30, 0);
			glVertex3f(30, -20, 0);
			glVertex3f(30, -10, 0);
			glVertex3f(30, 0, 0);
			glVertex3f(30, 10, 0);
			glVertex3f(30, 20, 0);
			glVertex3f(30, 30, 0);
			glVertex3f(40, -30, 0);
			glVertex3f(50, -20, 0);
			glVertex3f(60, -10, 0);
			glVertex3f(60, 0, 0);
			glVertex3f(60, 10, 0);
			glVertex3f(50, 20, 0);
			glVertex3f(40, 30, 0);
			glEnd();
		}
		
	
		// Restore transformations
		glPopMatrix();
	}

	SPDPointsViewer3DWidget::~SPDPointsViewer3DWidget()
	{
		
	}

}
 
