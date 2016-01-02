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
#include <iostream>
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
 void Graph::insert(Edge &edge) {
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
void Graph::add(Coor &source, Coor &dest) {
    int source_coor_index = -1;
    int dest_coor_index = -1;
    for (unsigned int i = 0; i < vertexList.size(); ++i) {
        if (source_coor_index == -1 && vertexList[i] == source ) {
            source_coor_index = i;
        }
        if (dest_coor_index == -1
                && data[i][0].getSourceVertex() == dest) {
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

vector<Vertex> Graph::shortestPath(const Vertex &start, const Vertex &finish)const {
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
Vertex* Graph::addVertex(const Coor &coor) {
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

    cerr<<"FindRotation\n";


    //next source un solundaysa

    if(next.getX()<source.getX() && next.getY()==source.getY())
    {

        cerr<<"next source un solunda\n";

        if((rotation>BATI -FARK) && (rotation < BATI +FARK))
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

        cerr<<"next source un haritada yukarısında\n";

        if((rotation>KUZEY -FARK) || (rotation< ZERO +FARK))
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

        cerr<<"next source un haritada saginda\n";
        cerr<<"rotation "<<rotation<<"\n";
        cerr<<"DOGU: "<<DOGU<<" BATI: "<<BATI<<" KUZEY: "<<KUZEY<<" GUNEY"<<GUNEY<<endl;
        if((rotation>DOGU -FARK) && (rotation < DOGU +FARK))
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
        cerr<<"next source un haritada asagisinda\n";

        if((rotation>GUNEY -FARK) && (rotation < GUNEY +FARK))
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


int Graph::findRotNoCompass(int source, int next, double rotation)
{
    //1 den 2 ye gidiyorsa
    if(source==0 && next==1)
    {
        if(rotation<ONE_TO_TWO + FARK && rotation > ONE_TO_TWO - FARK)
        {
            return 2;
        }
        else if(rotation>ONE_TO_TWO)
        {
            return 3;
        }
        else if(rotation<ONE_TO_TWO)
        {
            return 1;
        }
    }
    //2 den 3 e gidiyorsa
    else if(source==1 && next==2)
    {
        if(rotation<TWO_TO_THREE + FARK && rotation > TWO_TO_THREE - FARK)
        {
            return 2;
        }
        else if(rotation>TWO_TO_THREE)
        {
            return 3;
        }
        else if(rotation<TWO_TO_THREE)
        {
            return 1;
        }

    }
    //3 den 4 e gidiyorsa
    else if(source==2 && next==3)
    {
        if(rotation<THREE_TO_FOUR + FARK && rotation > THREE_TO_FOUR - FARK)
        {
            return 2;
        }
        else if(rotation>THREE_TO_FOUR)
        {
            return 3;
        }
        else if(rotation<THREE_TO_FOUR)
        {
            return 1;
        }
    }
    //4 den 5 e gidiyorsa
    else if(source==3 && next==4)
    {
        if(rotation<FOUR_TO_FIVE + FARK && rotation > FOUR_TO_FIVE - FARK)
        {
            return 2;
        }
        else if(rotation>FOUR_TO_FIVE)
        {
            return 1;
        }
        else if(rotation<FOUR_TO_FIVE)
        {
            return 3;
        }

    }//5 den 6 ya gidiyorsa
    else if(source==4 && next==5)
    {
        if(rotation<FIVE_TO_SIX + FARK && rotation > FIVE_TO_SIX - FARK)
        {
            return 2;
        }
        else if(rotation>FIVE_TO_SIX)
        {
            return 1;
        }
        else if(rotation<FIVE_TO_SIX)
        {
            return 3;
        }

    }
    //6 dan 7 ye gidiyorsa
    else if(source==5 && next==6)
    {
        if((rotation<SIX_TO_SEVEN + FARK && rotation > SIX_TO_SEVEN - FARK) || rotation>350)
        {
            return 2;
        }
        else if(rotation>SIX_TO_SEVEN)
        {
            return 3;
        }
        else if(rotation<SIX_TO_SEVEN || rotation<350 )
        {
            return 1;
        }

    }
    //7 den 8 e gidiyorsa
    else if(source==6 && next==7)
    {
        if((rotation<SEVEN_TO_EIGHT + FARK && rotation > SEVEN_TO_EIGHT - FARK) || rotation>350)
        {
            return 2;
        }
        else if(rotation>SEVEN_TO_EIGHT)
        {
            return 3;
        }
        else if(rotation<SEVEN_TO_EIGHT)
        {
            return 1;
        }
    }
    //8 den 9 a gidiyorsa
    else if(source==7 && next==8)
    {
        if((rotation<EIGHT_TO_NINE + FARK && rotation > EIGHT_TO_NINE - FARK) || rotation<=20)
        {
            return 2;
        }
        else if(rotation>EIGHT_TO_NINE)
        {
            return 3;
        }
        else if(rotation<EIGHT_TO_NINE)
        {
            return 1;
        }
    }
    //9 dan 10 e gidiyorsa
    else if(source==8 && next==9)
    {
        if(rotation<NINE_TO_TEN + FARK && rotation > NINE_TO_TEN - FARK)
        {
            return 2;
        }
        else if(rotation>NINE_TO_TEN)
        {
            return 3;
        }
        else if(rotation<NINE_TO_TEN)
        {
            return 1;
        }
    }
    //10 dan 11 e gidiyorsa
    else if(source==9 && next==10)
    {
        if(rotation<TEN_TO_ELEVEN + FARK && rotation > TEN_TO_ELEVEN - FARK)
        {
            return 2;
        }
        else if(rotation>TEN_TO_ELEVEN)
        {
            return 3;
        }
        else if(rotation<TEN_TO_ELEVEN)
        {
            return 1;
        }
    }
    //11 den 1 e gidiyorsa
    else if(source==10 && next==0)
    {
        if(rotation<ELEVEN_TO_ONE + FARK && rotation > ELEVEN_TO_ONE - FARK)
        {
            return 2;
        }
        else if(rotation>ELEVEN_TO_ONE)
        {
            return 3;
        }
        else if(rotation<ELEVEN_TO_ONE)
        {
            return 1;
        }
    }


    /*********************************/


    //11 den 10 a gidiyorsa
    else if(source==10 && next==9)
    {
        if(rotation<ELEVEN_TO_TEN + FARK && rotation > ELEVEN_TO_TEN - FARK)
        {
            return 2;
        }
        else if(rotation>ELEVEN_TO_TEN)
        {
            return 3;
        }
        else if(rotation<ELEVEN_TO_TEN)
        {
            return 1;
        }
    }
    //10 dan 9 a gidiyorsa
    else if(source==9 && next==8)
    {
        if(rotation<TEN_TO_NINE + FARK && rotation > TEN_TO_NINE - FARK)
        {
            return 2;
        }
        else if(rotation>TEN_TO_NINE)
        {
            return 3;
        }
        else if(rotation<TEN_TO_NINE)
        {
            return 1;
        }
    }
    //9 dan 8 e gidiyorsa
    else if(source==8 && next==7)
    {
        if(rotation<NINE_TO_EIGHT + FARK && rotation > NINE_TO_EIGHT - FARK)
        {
            return 2;
        }
        else if(rotation>NINE_TO_EIGHT)
        {
            return 3;
        }
        else if(rotation<NINE_TO_EIGHT)
        {
            return 1;
        }
    }
    //8 den 7 ye gidiyorsa
    else if(source==7 && next==6)
    {
        if(rotation<EIGHT_TO_SEVEN + FARK && rotation > EIGHT_TO_SEVEN - FARK)
        {
            return 2;
        }
        else if(rotation>EIGHT_TO_SEVEN)
        {
            return 3;
        }
        else if(rotation<EIGHT_TO_SEVEN)
        {
            return 1;
        }
    }
    //7 den 6 ya gidiyorsa
    else if(source==6 && next==5)
    {
        if(rotation<SEVEN_TO_SIX + FARK && rotation > SEVEN_TO_SIX - FARK)
        {
            return 2;
        }
        else if(rotation>SEVEN_TO_SIX)
        {
            return 3;
        }
        else if(rotation<SEVEN_TO_SIX)
        {
            return 1;
        }
    }
    //6 dan 5 e gidiyorsa
    else if(source==5 && next==4)
    {
        if(rotation<SIX_TO_FIVE + FARK && rotation > SIX_TO_FIVE - FARK)
        {
            return 2;
        }
        else if(rotation>SIX_TO_FIVE)
        {
            return 3;
        }
        else if(rotation<SIX_TO_FIVE)
        {
            return 1;
        }
    }
    //5 den 4 e gidiyorsa
    else if(source==4 && next==3)
    {
        if(rotation<FIVE_TO_FOUR + FARK && rotation > FIVE_TO_FOUR - FARK)
        {
            return 2;
        }
        else if(rotation>FIVE_TO_FOUR)
        {
            return 3;
        }
        else if(rotation<FIVE_TO_FOUR)
        {
            return 1;
        }
    }
    //4 den 3 e gidiyorsa
    else if(source==3 && next==2)
    {
        if((rotation<FOUR_TO_THREE + FARK && rotation > FOUR_TO_THREE - FARK) || rotation>=340)
        {
            return 2;
        }
        else if(rotation>FOUR_TO_THREE)
        {
            return 3;
        }
        else if(rotation<FOUR_TO_THREE)
        {
            return 1;
        }
    }
    //3 den 2 ye gidiyorsa
    else if(source==2 && next==1)
    {
        if((rotation<THREE_TO_TWO + FARK && rotation > THREE_TO_TWO - FARK) || rotation>=350)
        {
            return 2;
        }
        else if(rotation>THREE_TO_TWO)
        {
            return 3;
        }
        else if(rotation<THREE_TO_TWO)
        {
            return 1;
        }
    }
    //2 den 1 e gidiyorsa
    else if(source==1 && next==0)
    {
        if((rotation<TWO_TO_ONE + FARK && rotation > TWO_TO_ONE - FARK) || rotation>=350)
        {
            return 2;
        }
        else if(rotation>TWO_TO_ONE)
        {
            return 3;
        }
        else if(rotation<TWO_TO_ONE)
        {
            return 1;
        }
    }
    //1 den 11 e gidiyorsa
    else if(source==0 && next==10)
    {
        if(rotation<ONE_TO_ELEVEN + FARK && rotation > ONE_TO_ELEVEN - FARK)
        {
            return 2;
        }
        else if(rotation>ONE_TO_ELEVEN)
        {
            return 3;
        }
        else if(rotation<ONE_TO_ELEVEN)
        {
            return 1;
        }
    }

    return 0;

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


Coor gpsCoorToPixel(int x,int y){

}



