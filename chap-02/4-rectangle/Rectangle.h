#pragma once

class Rectangle
{
public:
    Rectangle(float length, float width);
    Rectangle(float size);

    float get_length() const { return _length; }
    float get_width() const { return _width; }

    void scale(float ratio);

private:
    float _length;
    float _width;
};
