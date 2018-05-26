//
// Created by emrea on 26.05.2018.
//

#ifndef RTCHALLENGE_TARGETDATA_H
#define RTCHALLENGE_TARGETDATA_H

#include "../utils/tinyxml2.h"
#include "Target.h"

class TargetData {

public:
    TargetData(tinyxml2::XMLElement* element);

    Target start;
    Target destination;
};

#endif //RTCHALLENGE_TARGETDATA_H
