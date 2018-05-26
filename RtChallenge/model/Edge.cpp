//
// Created by emrea on 26.05.2018.
//

#include "Edge.h"
#include <cmath>
#include <algorithm>
#include <functional>
#include <array>
#include <vector>

#define EPS 0.0000005

Edge::Edge(Cross from, Cross to) : from(from), to(to) {}

bool Edge::isTargetOnEdge(Target target) {
    Cross from = this->from;
    Cross to = this->to;

    if (abs(from.lat - to.lat) < EPS) {
        if (  abs(from.lat - target.lat) > EPS) return false;

        return min(from.lng, to.lng) < target.lng && target.lng < max(from.lng, to.lng);

    } else if ( abs(from.lng - to.lng) < EPS){
        if ( abs(from.lng - target.lng) > EPS) return false;

        return min(from.lat,to.lat) < target.lat && target.lat < max(from.lat, to.lat);
    }

    return false;
}

bool Edge::insertIfOnEdge(Target target1, Target target2) {
    if ( isTargetOnEdge(target1) && isTargetOnEdge(target2)) {

        double geschwindikeit =
                (abs(target1.lat - target2.lat) + abs(target1.lng - target2.lng)) * 1. / ( abs(target2.ts - target1.ts) );
        if (!isnan(geschwindikeit)) {
            this->timetable.push_back(make_pair(target1.tsString, geschwindikeit));

            sort(this->timetable.begin(), this->timetable.end(), timetableComparator );
            return true;
        }
    }
    return false;
}
