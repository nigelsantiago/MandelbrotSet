#pragma once
#include <SFML/Graphics.hpp>
#include <complex>
#include <cmath>
using namespace sf;
using namespace std;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State {CALCULATING, DISPLAYING};

class ComplexPlane : public Drawable
{
    public:

    ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight);
    void ComplexPlane::draw(RenderTarget& target, RenderStates states) const;
    void complexPlane::updateRender();
    void ComplexPlane::zoomIn();
    void ComplexPlane::zoomOut();
    void ComplexPlane::setCenter(Vector2i mousePixel);
    void ComplexPlane::setMouseLocation(Vector2i mousePixel);
    void ComplexPlane::loadText(Text& text);



    private:
    VertexArray m_Array;
    State m_state;
    Vector 2f m_mouseLocation;
    Vector 2i m_pixel_size;
    Vector 2f m_plane_center;
    Vector 2f m_plane_size;
    int m_zoomCount;
    float m_aspectRatio;

    size_t ComplexPlane::countIterations(Vector2f coord);
    void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel);
}