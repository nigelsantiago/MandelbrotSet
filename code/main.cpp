#include <iostream>
#include <complex>
#include <cmath>
#include <sstream>
#include <string>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;

unsigned int desktop_w = VideoMode::getDesktopMode().width / 2;    // 2
unsigned int desktop_h = VideoMode::getDesktopMode().height / 2;    // divided by 2 temp edit
VideoMode vm(desktop_w, desktop_h);
RenderWindow window(vm, "Mandelbrot Set", Style::Default);
