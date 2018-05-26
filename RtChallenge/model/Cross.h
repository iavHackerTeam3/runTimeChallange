//
// Created by emrea on 26.05.2018.
//

#ifndef RTCHALLENGE_CROSS_H
#define RTCHALLENGE_CROSS_H

#include <vector>
#include <string>
#include "../utils/tinyxml2.h"
#include "Target.h"

using namespace std;

class Cross {
public:
    Cross();
    explicit Cross(tinyxml2::XMLElement* element);
    int id;
    double lat;
    double lng;
    const char* network;
};

#endif //RTCHALLENGE_CROSS_H
