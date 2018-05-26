//
// Created by emrea on 26.05.2018.
//

#ifndef RTCHALLENGE_EDGE_H
#define RTCHALLENGE_EDGE_H

#include <utility>
#include <set>
#include "Cross.h"
#include "Target.h"

using namespace std;

class Edge {
public:
    Edge(Cross from, Cross to);
    Cross from;
    Cross to;
    vector<pair< const char*, double>> timetable;

    bool isTargetOnEdge(Target);

    bool insertIfOnEdge(Target, Target);
};

struct {
    bool operator()(pair<const char*, double> a, pair<const char*, double> b) {
        return a.second < b.second;
    };
} timetableComparator;

#endif //RTCHALLENGE_EDGE_H
