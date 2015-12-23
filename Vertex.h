/*
 * Vertex.h
 *
 *  Created on: 24 Kas 2015
 *      Author: Guner
 */

#ifndef VERTEX_H_
#define VERTEX_H_

class Coor {
public:
    Coor(int x_i,int y_i):x(x_i),y(y_i){}
    int x;
    int y;
};

class Vertex {
public:
    /*default constructors*/
    Vertex() :
            vertex_no(-1), coor_x(-1), coor_y(-1){
    }

    Vertex(int no, int x, int y) :
            vertex_no(no), coor_x(x), coor_y(y) {
    }
    Vertex(int no, Coor c) :
            vertex_no(no), coor_x(c.x), coor_y(c.y) {
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

    inline void setVertex( int x, int y) {
        coor_x = x, coor_y = y;
    }
    inline bool operator==(const Vertex &a) const {
        if ((this->coor_x == a.coor_x) && (this->coor_y == a.coor_y)) {
            return true;
        }
        return false;
    }
private:
    int vertex_no;/*vertex id*/
    int coor_x;/*x coordinate value*/
    int coor_y;/*y coordinate value*/

};

#endif /* VERTEX_H_ */
