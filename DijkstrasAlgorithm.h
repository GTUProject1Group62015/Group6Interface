/*
 * DijkstrasAlgorithm.h
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#ifndef DIJKSTRASALGORITHM_H_
#define DIJKSTRASALGORITHM_H_
#include "Graph.h"
#define DDD 10000000

class DijkstrasAlgorithm {
public:
    static void dijkstrasAlgorithm(const Graph &graph, int start, int pred[],
            double dist[]);
};

#endif /* DIJKSTRASALGORITHM_H_ */
