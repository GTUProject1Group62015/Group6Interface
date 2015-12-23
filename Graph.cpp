/*
 * Graph.cpp
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#include "Graph.h"
#include "Edge.h"
#include "DijkstrasAlgorithm.h"
#include <cstddef>
#include <cmath>
using namespace std;

Graph::Graph(bool direct = true, int num = 0) :
        directed(direct), numV(num) {
    vector<Edge> e;
    for (int i = 0; i < numV; ++i) {
        data.push_back(e);
        ++numV;
    }
}
/*
 void Graph::insert(Edge edge) {
 if (edge.getSource() > numV) {
 vector<Edge> e;
 data.push_back(e);
 ++numV;
 }
 data[edge.getSource()].push_back(edge);
 if (!directed) {
 data[edge.getDest()].push_back(
 Edge(edge.getDest(), edge.getSource(), edge.getWeight()));
 }
 }
 */
bool Graph::isEdge(int source, int dest) const {
    if (source < 0 || dest < 0 || source > numV || dest > numV) {
        return false;
    }
    for (unsigned int i = 0; i < data[source].size(); ++i) {
        if (data[source][i].getDest() == dest) {
            return true;
        }
    }
    return false;
}

Edge Graph::getEdge(int source, int dest) const {
    for (unsigned int i = 0; i < data[source].size(); ++i) {
        if (data[source][i].getDest() == dest) {
            return data[source][i];
        }
    }
    return Edge(Vertex(), Vertex());
}

//not finished....
void Graph::add(Coor source, Coor dest) {
    int source_coor_index = -1;
    int dest_coor_index = -1;
    for (unsigned int i = 0; i < vertexList.size(); ++i) {
        if (source_coor_index == -1 && vertexList[i].getX() == source.x
                && vertexList[i].getY() == source.y) {
            source_coor_index = i;
        }
        if (dest_coor_index == -1
                && data[i][0].getSourceVertex().getX() == dest.x
                && data[i][0].getSourceVertex().getY() == dest.y) {
            dest_coor_index = i;
        }

        if (source_coor_index != -1 && dest_coor_index != -1) {
            break;
        }
    }

    if (source_coor_index == -1) {
        vector<Edge> e;
        data.push_back(e);
        source_coor_index = numV;
        vertexList.push_back(Vertex(source_coor_index, source));
        ++numV;

    }
    if (dest_coor_index == -1) {
        vector<Edge> e;
        data.push_back(e);
        dest_coor_index = numV;
        vertexList.push_back(Vertex(dest_coor_index, dest));

        ++numV;

    }

    data[source_coor_index].push_back(
            Edge(Vertex(source_coor_index, source),
                    Vertex(dest_coor_index, dest)));

    if (!directed) {
        data[dest_coor_index].push_back(
                Edge(Vertex(dest_coor_index, dest),
                        Vertex(source_coor_index, source)));
    }
}

vector<Vertex> Graph::shortestPath(Vertex start, Vertex finish) {
    int pred[numV];
    double dist[numV];
    vector<Vertex> result;
    int index = start.getNo();
    DijkstrasAlgorithm::dijkstrasAlgorithm(*this, finish.getNo(), pred, dist);
    for (int i = 0; i < numV; ++i) {
        result.push_back(vertexList[index]);
        index = pred[index];
        if (index == finish.getNo()) {
            result.push_back(vertexList[index]);
            break;
        }
    }
    return result;
}

/** add vertex*/
Vertex* Graph::addVertex(Coor coor) {
    int source_coor_index = -1;
    for (unsigned int i = 0; i < vertexList.size(); ++i) {
        if (source_coor_index == -1 && vertexList[i].getX() == coor.x
                && vertexList[i].getY() == coor.y) {
            source_coor_index = i;
        }
        if (source_coor_index != -1) {
            break;
        }
    }
    if (source_coor_index == -1) {
        vector<Edge> e;
        data.push_back(e);
        source_coor_index = numV;
        vertexList.push_back(Vertex(source_coor_index, coor));
        ++numV;
        return &vertexList[numV - 1];
    }
    return NULL;
}

/** set edge */
bool Graph::setEdge(Vertex vSource, Vertex vDest) {
    if (isEdge(vSource.getNo(), vDest.getNo())) {
        return false;
    }

    data[vSource.getNo()].push_back(
            Edge(Vertex(vSource.getNo(), vSource.getX(), vSource.getY()),
                    Vertex(vDest.getNo(), vDest.getX(), vDest.getY())));

    if (!directed) {
        data[vDest.getNo()].push_back(
                Edge(Vertex(vDest.getNo(), vDest.getX(), vDest.getY()),
                        Vertex(vSource.getNo(), vSource.getX(),
                                vSource.getY())));
    }
    return true;
}

void Graph::setVertex(Vertex &v, Coor newCoor) {
    v.setVertex(newCoor.x, newCoor.y);
}


bool Graph::removeEdge(Vertex &v){
    if(data.size()<=(unsigned int)v.getNo())
    {
        return false;
    }
    data[v.getNo()].clear();
    return true;
}

vector<Edge> Graph::getEdgeList(const vector<Vertex> & list)
{
    vector<Vertex> sortestPath();
    vector<Edge> edgeList;
    for(unsigned int i=0;i<list.size()-1;i++)
    {
        edgeList.push_back(getEdge(list[i].getNo(), list[i+1].getNo()));
    }
    return edgeList;
}



int Graph::nearestVertex(Vertex node)
{
    int nearestX;
    int nearestY;
    int index=0;

    nearestX=fabs(node.getX()-vertexList.at(0).getX());
    nearestY=fabs(node.getX()-vertexList.at(0).getY());

    for(unsigned int i=1; i<vertexList.size();i++)
    {
        if(abs(node.getX()-vertexList.at(i).getX() )<nearestX)
        {
            if(abs(node.getY()-vertexList.at(i).getY() )<nearestY)
            {
                nearestX=abs(node.getX()-vertexList.at(i).getX() );
                nearestY=abs(node.getY()-vertexList.at(i).getY() );
                index=i;
            }
        }
    }

    return index;
}

int Graph::findRotation(Vertex source, Vertex next, double rotation)
{

    double m; //egim
    double y;
    double x;

    //y=( next.getY()-source.getY() );
    //x=(next.getX()-source.getX());

    //m= y/x;




    //next source un solundaysa

    if(next.getX()<source.getX() && next.getY()==source.getY())
    {


        if((rotation>BATI -15) && (rotation < BATI +15))
        {
            return 2;
        }
        else if(rotation>=ZERO && rotation<DOGU)
        {
            return 1;
        }
        else if(rotation>BATI && rotation<=KUZEY)
        {
            return 1;
        }
        else if(rotation>=GUNEY && rotation<BATI)
        {
            return 3;
        }
        else if(rotation>=DOGU && rotation<GUNEY)
        {
            return 3;
        }

    }

    //next source un ilerisindeyse --> haritada yukarisindaysa

    else if(next.getX()==source.getX() && next.getY()<source.getY())
    {
        if((rotation>KUZEY -15) || (rotation< ZERO +15))
        {
            return 2;
        }
        else if(rotation>ZERO && rotation<DOGU)
        {
            return 1;
        }
        else if(rotation>=BATI && rotation<KUZEY)
        {
            return 3;
        }
        else if(rotation>=GUNEY && rotation<BATI)
        {
            return 3;
        }
        else if(rotation>=DOGU && rotation<GUNEY)
        {
            return 1;
        }
    }

    //next source un sagindaysa

    else if(next.getX()>source.getX() && next.getY()==source.getY())
    {
        if((rotation>DOGU -15) && (rotation < DOGU +15))
        {
            return 2;
        }
        else if(rotation>=ZERO && rotation<DOGU)
        {
            return 3;
        }
        else if(rotation>=BATI && rotation<=KUZEY)
        {
            return 3;
        }
        else if(rotation>=GUNEY && rotation<BATI)
        {
            return 1;
        }
        else if(rotation>DOGU && rotation<GUNEY)
        {
            return 1;
        }
    }

    //next source un gerisindeyse --> haritada asagisinda

    else if(next.getX()==source.getX() && next.getY()>source.getY())
    {
        if((rotation>GUNEY -15) && (rotation < GUNEY +15))
        {
            return 2;
        }
        else if(rotation>=ZERO && rotation<DOGU)
        {
            return 3;
        }
        else if(rotation>=BATI && rotation<=KUZEY)
        {
            return 1;
        }
        else if(rotation>GUNEY && rotation<BATI)
        {
            return 1;
        }
        else if(rotation>=DOGU && rotation<GUNEY)
        {
            return 3;
        }
    }

    return 0;
}

int Graph::moveRotation(Vertex source, Vertex next)
{
    if(next.getX()==source.getX() && next.getY()==source.getY())
    {
        return 5;
    }
    else
    {
        return 4;
    }
}

/*void moveCompass(void)
{
    double rotation;

    while(true)
    {
        cin>>rotation;

        while( i<list.size() )
        {
            findRotation(list[i] , list[i+1], rotation)
            if(rotation==2) //yon dogru
                i++;
        }
    }
}
*/

vector<Edge> Graph::getAllEdge(){
    vector<Edge> result;
    for(unsigned int i = 0 ;i<data.size();++i)
    {
        for(unsigned int j =0;j<data[i].size();++j)
        {
            result.push_back(data[i][j]);
        }
    }
    return result;
}
