#include "QuadtreeObject.h"

QuadtreeObject::QuadtreeObject(
    float _x, float _y, float _width, float _height,
    void *_data
) : 
    x       ( _x ),
    y       ( _y ),
    width   ( _width ),
    height  ( _height )
{
    data = _data;
}
