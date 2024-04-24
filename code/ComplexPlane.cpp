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
	m_plane_center = (0,0);

	m_plane_size= (BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);

	m_zoomCount = 0;

	m_state = State::CALCULATING;
    
	m_vArray.setPrimitiveType(Points);
	resize(pixelWidth*pixelHeight);
	
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void complexPlane::updateRender()
{
    if (m_state = CAlCULATING)
    {
	    for (int i = 0; i < pixelHeight; ++i)
	    {
	        for (int j = 0; j < pixelWidth; ++i)
		    {
			    vArray[j + i * pixelWidth].position = {(float)j,(float)i};
				m_plane_size = mapPixelToCoords(mousePixel);
				size_t count = countIterations(mousePixel);
	
				Uint8 r, g, b;
	
				iterationsToRGB(count, Uint8& r, Uint8& g, Uint8& b);
	
				vArray[j + i * pixelWidth].color = { r,g,b };
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
    m_plane_size = (x, y);
    m_State = CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = (x, y);
    m_State = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    m_State = CALCULATING;
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
	int count = 0;
	float z = 0;
	float c = pow((coord.x*coord.x + coord.y*coord.y), 0.5)
	int i = 0;
	while (int i < MAX_ITER && z <= 2.0)
	{
		z = pow(z, 2) + c;
		i++;
	}
	return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{	
	if (count >= MAX_ITER) // black
	{
		r = 230;
		g = 0;
		b = 255;
	}
	else if (count < 10) // following the color scheme from canvas page for now --purple
	{
		r = 200;
		g = 200;
		b = 200;
	}
	else if (count < 21) // --blue
	{
		r = 0;
		g = 30;
		b = 255;
	}
	else if (count < 31) // --turquoise
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

	newCoord.x = ((static_cast<float>(mousePixel.x) - 0) / (pixelWidth - 0)) * m_plane_size.x + offset_x;
	newCoord.y = ((static_cast<float>(mousePixel.y) - pixelHeight) / (0 - pixelHeight)) * m_plane_size.y + offset_y;

	return newCoord;
}
