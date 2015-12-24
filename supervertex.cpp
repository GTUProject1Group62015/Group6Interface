/*
 * SuperVertex.cpp
 *
 *  Created on: 11 Ara 2015
 *      Author: Guner
 */

#include "SuperVertex.h"

SuperVertex::SuperVertex(const int &no, const Coor &ileftTop,
        const Coor &ileftBottom, const Coor &irightTop,
        const Coor &irightBottom) :
        Vertex() {
    Vertex::vertex_no = no;
    leftTop = ileftTop;
    leftBottom = ileftBottom;
    rightTop = irightTop;
    rightBottom = irightBottom;
    int x1 = (rightTop.x - leftTop.x) / 2;
    int y1 = (leftBottom.y - leftTop.y) / 2;
    Vertex::coor_x = leftTop.x + x1;
    Vertex::coor_y = leftTop.y + y1;

}

void SuperVertex::setVertex(const Coor &ileftTop, const Coor &ileftBottom,
        const Coor &irightTop, const Coor &irightBottom) {
    leftTop = ileftTop;
    leftBottom = ileftBottom;
    rightTop = irightTop;
    rightBottom = irightBottom;
}

bool SuperVertex::operator==(const SuperVertex &comp) const {
    if (this->leftTop == comp.leftTop && this->leftBottom == comp.leftBottom
            && this->rightTop == comp.rightTop && this->rightBottom == comp.rightBottom) {
        return true;
    }
    return false;
}
