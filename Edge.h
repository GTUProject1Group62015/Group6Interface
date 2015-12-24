/*
 * Edge.h
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#ifndef EDGE_H_
#define EDGE_H_
#include "Vertex.h"
#include <cmath>
#define PI 3.14159265
class Edge {
public:
    /*constructors*/

    Edge(const Vertex &s,const Vertex &d){
        source=s;
        dest=d;
        int x_dis=s.getX()-d.getX();
        int y_dis=(s.getY()-d.getY());
        int result=(x_dis*x_dis)+(y_dis*y_dis);
        weight = result;
        if(x_dis==0)
        {
            m=0.0;
        }
        else if(y_dis==0)
        {
            m=1.0;
        }
        else
        {
            m=y_dis/x_dis;
        }
        degree=atan(m)*180.0/PI;
        if(y_dis<0)
        {
            degree+=180;
        }
    }

    /*return weight of edge*/
    inline unsigned int getWeight()const {
        return weight;
    }

    /*set weight*/
    inline void setWeight(unsigned int value){
        weight = value;
    }

    /*return source vertex*/
    inline int getSource()const {
        return source.getNo();
    }

    /*return destination vertex*/
    inline int getDest()const {
        return dest.getNo();
    }

    /*set source vertex*/
    inline void setSource(Vertex v1) {
        source = v1;
    }

    /*set destination vertex*/
    inline void setDest(Vertex v2) {
        dest = v2;
    }

    /* get source vertex*/
    inline Vertex& getSourceVertex(){return source;}

    /* get dest vertex*/
    inline Vertex& getDestVertex(){return dest;}

    /* get slope*/
    inline double getSlope(){return m;}

    /*get degree*/
    inline int getDegree(){return degree;}
    ~Edge() {
    }
    // destructor
private:
    Vertex source;                 // a vertex on one side of the edge
    Vertex dest;                // a vertex on the other side of the edge
    unsigned int weight;              // the value of the edge ( or its weight )
    double m;/*slope*/
    int degree;/* hold degree*/

};

#endif /* EDGE_H_ */
