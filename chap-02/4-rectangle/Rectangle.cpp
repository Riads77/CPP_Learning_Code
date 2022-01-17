// Implement Rectangle functions here.
#include "Rectangle.h"

Rectangle::Rectangle(float length, float width)
    : _length { length }
    , _width { width }
{}

Rectangle::Rectangle(float size)
    : Rectangle { size, size }
{}

void Rectangle::scale(float ratio)
{
    _length *= ratio;
    _width *= ratio;
}