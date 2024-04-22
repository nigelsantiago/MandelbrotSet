#include "ComplexPlane.h"
#include <iostream>
#include <complex>
#include <cmath>
using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{

}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{

}

void complexPlane::updateRender()
{

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
