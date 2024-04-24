#include "ComplexPlane.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size.x = pixelWidth;
	m_pixel_size.y = pixelHeight;

	m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth; 
	m_plane_center = {0,0};

	m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};

	m_zoomCount = 0;

	m_state = State::CALCULATING;
    
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth*pixelHeight);
	
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
    if (m_state == CALCULATING)
    {
	    for (int i = 0; i < m_pixel_size.y; ++i)
	    {
	        for (int j = 0; j < m_pixel_size.x; ++j) // check: is this really ++i again?
		    {
			    m_vArray[j + i * m_pixel_size.x].position = {(float)j,(float)i};
				Vector2f coord = mapPixelToCoords({j, i});
				size_t count = countIterations(coord);
	
				Uint8 r, g, b;
	
				iterationsToRGB(count, r, g, b);
	
				m_vArray[j + i * m_pixel_size.x].color = {r,g,b}; // replaced pixelheight/width to member function m_pixel_size
		    }
	    }
    }
    m_state = DISPLAYING;
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = {x, y}; // no effect error means change parenthesis to curly brace
    m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = {x, y};
    m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
    ostringstream strm;
    strm << "Mandelbrot Set" << endl << "Center: (" << m_plane_center.x << "," << m_plane_center.y << endl
         << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl
         << "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;
    
    text.setString(strm.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	unsigned int count = 0;
	float z = 0;
	float c = pow((coord.x*coord.x + coord.y*coord.y), 0.5);
	while (count < MAX_ITER && z <= 2.0)
	{
		z = pow(z, 2) + c;
		count++;
	}
	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{	
	if (count >= MAX_ITER) // black
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count < 6) // following the color scheme from canvas page for now --purple
	{
		r = 230;
		g = 0;
		b = 255;
	}
	else if (count < 18) // --blue
	{
		r = 0;
		g = 30;
		b = 255;
	}
	else if (count < 29) // --turquoise
	{
		r = 0;
		g = 255;
		b = 225;
	}
	else if (count < 42) // green
	{
		r = 0;
		g = 255;
		b = 98;
	}
	else if (count < 54) // yellow
	{
		r = 255;
		g = 225;
		b = 0;
	}
	else // red
	{
		r = 255;
		g = 200;
		b = 17;
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    Vector2f newCoord;

	float offset_x = m_plane_center.x - m_plane_size.x * 0.5;
	float offset_y = m_plane_center.y - m_plane_size.y * 0.5;

	newCoord.x = ((static_cast<float>(mousePixel.x) - 0) / (m_pixel_size.x - 0)) * m_plane_size.x + offset_x;
	newCoord.y = ((static_cast<float>(mousePixel.y) - m_pixel_size.y) / (0 - m_pixel_size.y)) * m_plane_size.y + offset_y;

	return newCoord;
}
