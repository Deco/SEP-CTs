#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>

#include "QuadtreeObject.h"

class Quadtree;
class QuadtreeObject;

class Quadtree {
public:
    Quadtree(
        float x, float y, float width, float height, int level, int maxLevel
    );
    ~Quadtree();

    void AddObject(QuadtreeObject *object);
    void RemoveObject(QuadtreeObject *object);
    void RemoveObjectWithData(void *data);
    void RemoveAllObjects();
    std::vector<QuadtreeObject*> GetObjectsAt(float x, float y);


public:
    float x, y, width, height;
    int level, maxLevel;
    std::vector<QuadtreeObject*> objects;

    Quadtree *parent, *NW, *NE, *SW, *SE;

    bool contains(Quadtree *child, QuadtreeObject *object);
};

#endif