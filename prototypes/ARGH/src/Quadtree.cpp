#include "Quadtree.h"
#include "QuadtreeObject.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Quadtree::Quadtree(
    float _x, float _y, float _width, float _height, int _level, int _maxLevel
) : x(_x), y(_y),
    width(_width), height(_height),
    level(_level), maxLevel(_maxLevel)
{
    if (level == maxLevel) {
        return;
    }
    NW = new Quadtree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
    NE = new Quadtree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
    SW = new Quadtree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
    SE = new Quadtree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
}

Quadtree::~Quadtree()
{
    if (level == maxLevel) {
        return;
    }
    delete NW;
    delete NE;
    delete SW;
    delete SE;
}

void Quadtree::AddObject(QuadtreeObject *object)
{
    if (level == maxLevel) {
        objects.push_back(object);
        return;
    }
    if (contains(NW, object)) {
        NW->AddObject(object); return;
    } else if (contains(NE, object)) {
        NE->AddObject(object); return;
    } else if (contains(SW, object)) {
        SW->AddObject(object); return;
    } else if (contains(SE, object)) {
        SE->AddObject(object); return;
    }
    if (contains(this, object)) {
        objects.push_back(object);
    }
}
std::vector<QuadtreeObject*> Quadtree::GetObjectsAt(float _x, float _y)
{
    if (level == maxLevel) {
        return objects;
    }
    
    std::vector<QuadtreeObject*> returnObjects, childReturnObjects;
    if (!objects.empty()) {
        returnObjects = objects;
    }
    if (_x > x + width / 2.0f && _x < x + width) {
        if (_y > y + height / 2.0f && _y < y + height) {
            childReturnObjects = SE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        } else if (_y > y && _y <= y + height / 2.0f) {
            childReturnObjects = NE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    } else if (_x > x && _x <= x + width / 2.0f) {
        if (_y > y + height / 2.0f && _y < y + height) {
            childReturnObjects = SW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        } else if (_y > y && _y <= y + height / 2.0f) {
            childReturnObjects = NW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    }
    return returnObjects;
}

void Quadtree::RemoveObject(QuadtreeObject *object)
{
    std::vector<QuadtreeObject*>::iterator iter = objects.begin();
    for(; iter != objects.end(); iter++) {
        QuadtreeObject *ob = *iter;
        if(ob == object) {
            objects.erase(iter);
            break;
        }
    }
    if (level == maxLevel) {
        return;
    }
    NW->RemoveObject(object);
    NE->RemoveObject(object);
    SW->RemoveObject(object);
    SE->RemoveObject(object);
}

void Quadtree::RemoveObjectWithData(void *data)
{
    std::vector<QuadtreeObject*>::iterator iter = objects.begin();
    for(; iter != objects.end(); iter++) {
        QuadtreeObject *ob = *iter;
        if(ob->data == data) {
            objects.erase(iter);
            break;
        }
    }
    if (level == maxLevel) {
        return;
    }
    NW->RemoveObjectWithData(data);
    NE->RemoveObjectWithData(data);
    SW->RemoveObjectWithData(data);
    SE->RemoveObjectWithData(data);
}

void Quadtree::RemoveAllObjects()
{
    if (level == maxLevel) {
        objects.clear();
        return;
    } else {
        NW->RemoveAllObjects();
        NE->RemoveAllObjects();
        SW->RemoveAllObjects();
        SE->RemoveAllObjects();
    }
    if (!objects.empty()) {
        objects.clear();
    }
}

bool Quadtree::contains(Quadtree *child, QuadtreeObject *object)
{
    return   !(object->x < child->x ||
                object->y < child->y ||
                object->x > child->x + child->width  ||
                object->y > child->y + child->height ||
                object->x + object->width < child->x ||
                object->y + object->height < child->y ||
                object->x + object->width > child->x + child->width ||
                object->y + object->height > child->y + child->height);
}