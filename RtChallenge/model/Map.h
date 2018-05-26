//
// Created by emrea on 26.05.2018.
//

#ifndef RTCHALLENGE_MAP_H
#define RTCHALLENGE_MAP_H


#include <map>
#include <vector>
#include "../utils/tinyxml2.h"
#include "Cross.h"
#include "Edge.h"

class Map {
public:
    Map();
    Map(tinyxml2::XMLElement* element);
    map< int, Cross> crosses;
    map< pair<int, int>, Edge> edges;

    Cross getCross(int);
    Cross findCross(Target);

    void recursiveSearch(Cross start, Cross destination, double startTime, double finalTime, vector<int> pathCopy);
    double timeOnEdge(Cross start, Cross destination, double startTime);
    vector<int> split(const string& str, const string& delim);
};

#endif //RTCHALLENGE_MAP_H
