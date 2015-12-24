/*
 * SuperVertex.h
 *
 *  Created on: 11 Ara 2015
 *      Author: Guner
 */

#ifndef SUPERVERTEX_H_
#define SUPERVERTEX_H_

#include "Vertex.h"

class SuperVertex: public Vertex {
public:
    /**
     * default constructor
     */
    SuperVertex() :
            Vertex() {

    }

    /**
     * constructor,take four coordinate
     */
    SuperVertex(const int &no, const Coor &ileftTop, const Coor &ileftBottom,
            const Coor &irightTop, const Coor &irightBottom);

    /**
     * set vertex
     */
    virtual inline void setVertex(const Coor &ileftTop, const Coor &ileftBottom,
            const Coor &irightTop, const Coor &irightBottom);


    /**
     * equals operator
     */
    virtual bool operator==(const SuperVertex &comp) const ;

    /*
     * get leftTop
     * @return Coor
     */
    inline Coor getLeftTop() {
        return leftTop;
    }

    /**
     * get leftBottom
     * @return Coor
     */
    inline Coor getLeftBottom() {
        return leftBottom;
    }

    /*
     * get leftTop
     * @return Coor
     */
    inline Coor getRightTop() {
        return rightTop;
    }

    /**
     * get leftBottom
     * @return Coor
     */
    inline Coor getRightBottom() {
        return rightBottom;
    }

    /**
     * destructor
     */
    virtual ~SuperVertex() {
    }
    ;
protected:
    Coor leftTop;
    Coor leftBottom;
    Coor rightTop;
    Coor rightBottom;
};

#endif /* SUPERVERTEX_H_ */
