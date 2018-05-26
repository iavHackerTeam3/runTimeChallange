//
// Created by emrea on 26.05.2018.
//

#ifndef RTCHALLENGE_TARGETS_H
#define RTCHALLENGE_TARGETS_H

#include "../utils/tinyxml2.h"

class Target {
public:
    Target();
    explicit Target(tinyxml2::XMLElement* element);
    explicit Target(const char* ts, const char* lat, const char* lng);

    const char* tsString;
    double ts; // time in seconds on this day
    double lat;
    double lng;
};

#endif //RTCHALLENGE_TARGETS_H
