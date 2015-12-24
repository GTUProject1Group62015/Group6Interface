/*
 * Graph.h
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include "Edge.h"
#include "Define.h"
#include <vector>
using namespace std;

class Graph {
public:

    /*default constructor*/
    Graph() {
        numV = 0;
        directed = false;
    }

    Graph(bool direct, int num);/*constructor*/
    /** Return the number of vertices.
     @return The number of vertices
     */
    inline int getNumV() const {
        return numV;
    }

    /*return vertex list*/
    inline vector<Vertex>& getVertexList() {
        return vertexList;
    }

    /** Determine whether this is a directed graph.
     @return true if this is a directed graph
     */
    inline bool isDirected() {
        return directed;
    }

    /** Insert a new edge into the graph.
     @param edge The new edge
     */
    void insert(Edge &edge);

    /** Determine whether an edge exists.
     @param source The source vertex
     @param dest The destination vertex
     @return true if there is an edge from source to dest
     */
    bool isEdge(int source, int dest) const;

    /** Get the edge between two vertices.
     @param source The source vertex
     @param dest The destination vertex
     @return The Edge between these two vertices
     */
    Edge getEdge(int source, int dest) const;

    /**	get edge list
     * 	@return return edge list
     */
    inline vector<vector<Edge> >& getData() {
        return data;
    }

    /** insert new two Vertex and Edge between given two Vertex into the graph,
     *  if given source and dest Coor exist, no addition
     * @param source The source coordinate
     * @param dest The destination coordinate
     */
    void add(Coor &source, Coor &dest);

    /** return shortest path from start vertex to finish vertex
     * @param start
     * @param finish
     * @return vertex vector
     */
    vector<Vertex> shortestPath(const Vertex &start,const Vertex &finish)const;

    /** add vertex,if addition is successful, return this Vertex reference,else returns 0*/
    Vertex* addVertex(const Coor &coor);

    /** set edge */
    bool setEdge(Vertex vSource, Vertex vDest);

    /*set given vertex,no return value*/
    void setVertex(Vertex &v, Coor newCoor);

    /**remove connection of given Vertex,return true if successful*/
    bool removeEdge(Vertex &v);

    /**
     * @param list vertex list
     * @param node target node
     * @return return nearest vertex index
     */
    int nearestVertex(Vertex node);

    /**
     *@param list vertex list
     *@return Edge list
     */
    vector<Edge> getEdgeList(const vector<Vertex> &list);

    vector<Edge> getAllEdge();

    /** find Rotation
     * @param source  The source node on the graph
     * @param next   The next node on the graph
     * @return rotation value 1,2,3,4,5
     * 1-> sol
     * 2-> dur yönü buldun
     * 3-> sağ
     * 4-> ileri
     * 5-> geri
     * 0-> node yerlesim hatasi
     */

    int findRotation(Vertex source, Vertex next, double rotation);

    //Eger node un ustune gelip, bize bilgi vermeden gecerse patlar
    //tam node un ustune geldiginde 5 gonderdik
    int moveRotation(Vertex source, Vertex next);

    //Server kullanım sekli
    //int flag=0;
    //while true
    //if(flag==2)
    //	moveRotation
    //else
    //	flag=findRotation

    /** move compass by finding rotation coordinate
     */
    //void moveCompass(void);
private:
    int directed;
    int numV;
    vector<vector<Edge> > data;
    vector<Vertex> vertexList;
};

#endif /* GRAPH_H_ */
