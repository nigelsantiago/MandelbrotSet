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

	m_aspectRatio = pixelHeight / pixelWidth; 
	m_plane_center = (0,0);

	m_plane_size= (BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);

	m_zoomCount = 0;

	m_state = State::CALCULATING;
    
	m_vArray(Points type, size_t vertexCount = 0);
	size_t vertexCount = pixelWidth*pixelHeight;
	resize(vertexCount);
	
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

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    
}
