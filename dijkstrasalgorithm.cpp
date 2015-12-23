/*
 * DijkstrasAlgorithm.cpp
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#include "DijkstrasAlgorithm.h"

void DijkstrasAlgorithm::dijkstrasAlgorithm(const Graph &graph, int start,
        int pred[], double dist[]){
    int numV = graph.getNumV();
    int rem;
    vector<int> vMinusS ;
    // Initialize V–S.
    for (int i = 0; i < numV; i++) {
        if (i != start) {
            vMinusS.push_back(i);
        }
    }
    numV = vMinusS.size();
    // Initialize pred and dist.
    for (int v = 0; v < numV; ++v) {
        pred[vMinusS[v]] = start;
        if( graph.isEdge(start, vMinusS[v])==true )
            dist[vMinusS[v]] = graph.getEdge(start, vMinusS[v]).getWeight();
        else
        {
            dist[vMinusS[v]]=DDD;
        }
    }
    // Main loop
    while (vMinusS.size() != 0) {
        // Find the value u in V–S with the smallest dist[u].
        double minDist = DDD;
        int u = -1;
        for (int v = 0; v < numV; ++v) {
            if (dist[vMinusS[v]] < minDist) {
                minDist = dist[vMinusS[v]];
                u = vMinusS[v];
            }
        }
        // Remove u from vMinusS.

        for (int i = 0; i < numV; ++i) {
            if (vMinusS[i] == u)
                rem = i;
        }
        vMinusS.erase(vMinusS.begin() + rem);
        // Update the distances.
        numV = vMinusS.size();

        for (int v = 0; v < numV; ++v) {
            if (graph.isEdge(u, vMinusS[v])) {
                double weight = graph.getEdge(u, vMinusS[v]).getWeight();
                if (dist[u] + weight < dist[vMinusS[v]]) {
                    dist[vMinusS[v]] = dist[u] + weight;
                    pred[vMinusS[v]] = u;
                }
            }
        }

    }
}

