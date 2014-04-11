#ifndef __QUADTREEOBJECT_H__
#define __QUADTREEOBJECT_H__

class QuadtreeObject {
public:
    float                   x;
    float                   y;
    float                   width;
    float                   height;
    void                    *data;

    QuadtreeObject( float x, float y, float width, float height, void *data );
};

#endif
