#pragma once
#include <SFML/Graphics.hpp>

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

    private:
        VertexArray m_Array;
        State m_state;
        Vector 2f m_mouseLocation;
        Vector 2i m_pixel_size;
        Vector 2f m_plane_center;
        Vector 2f m_plane_size;
        int m_zoomCount;
        float m_aspectRatio;
}