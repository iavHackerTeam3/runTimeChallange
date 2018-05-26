//
// Created by emrea on 26.05.2018.
//

#include "Cross.h"

Cross::Cross() {};
Cross::Cross(tinyxml2::XMLElement* cross) {
    Cross::id = atoi(cross->FirstChildElement("id")->GetText());
    Cross::lat = atof(cross->FirstChildElement("lat")->GetText());
    Cross::lng = atof(cross->FirstChildElement("lng")->GetText());
    Cross::network = cross->FirstChildElement("network")->GetText();
}
