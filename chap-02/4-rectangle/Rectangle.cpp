// Implement Rectangle functions here.
#include "Rectangle.h"

Rectangle::Rectangle(float length, float width)
    : _length { length }
    , _width { width }
{}

Rectangle::Rectangle(float size)
    : Rectangle { size, size }
{}

Rectangle::Rectangle()
    : Rectangle { _default_size }
{}

void Rectangle::scale(float ratio)
{
    _length *= ratio;
    _width *= ratio;
}

float Rectangle::_default_size = 0.f;