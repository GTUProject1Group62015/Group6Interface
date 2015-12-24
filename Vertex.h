/*
 * Vertex.h
 *
 *  Created on: 24 Kas 2015
 *      Author: Guner
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "Coor.h"

class Vertex {
public:
    /*default constructors*/
    Vertex() :
            vertex_no(-1), coor_x(-1), coor_y(-1), mark(false) {
    }

    Vertex(int no, int x, int y, bool mark_i = false) :
            vertex_no(no), coor_x(x), coor_y(y), mark(mark_i) {
    }
    Vertex(int no, Coor &c, bool mark_i = false) :
            vertex_no(no), coor_x(c.x), coor_y(c.y), mark(mark_i) {
    }

    Vertex(const int &no, const Coor &c) :
            vertex_no(no), coor_x(c.x), coor_y(c.y), mark(false) {
    }

    /*getters*/
    inline int getX() const {
        return coor_x;
    }
    inline int getY() const {
        return coor_y;
    }
    inline int getNo() const {
        return vertex_no;
    }

    virtual inline void setVertex(int x, int y) {
        coor_x = x, coor_y = y;
    }

    /**
     * check only x-y coordinate,if it equals,return true
     */
    virtual inline bool operator==(const Vertex &a) const {
        if ((this->coor_x == a.coor_x) && (this->coor_y == a.coor_y)) {
            return true;
        }
        return false;
    }

    virtual inline bool operator==(const Coor &c) const {
        if ((this->coor_x == c.x) && (this->coor_y == c.y)) {
            return true;
        }
        return false;
    }
    /** get mark
     * @return return bool, True if Vertex traversed else false
     */
    inline bool getMark() {
        return mark;
    }
    virtual ~Vertex(){};
protected:
    int vertex_no;/*vertex id*/
    int coor_x;/*x coordinate value*/
    int coor_y;/*y coordinate value*/
    bool mark;/*true=uzerinden gecildiginde,false=henuz gecmeyince*/

};

#endif /* VERTEX_H_ */
