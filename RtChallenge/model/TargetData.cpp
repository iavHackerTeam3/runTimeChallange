//
// Created by emrea on 26.05.2018.
//

#include "TargetData.h"

TargetData::TargetData(tinyxml2::XMLElement* element) {
    tinyxml2::XMLElement* startElement = element->FirstChildElement("start");
    tinyxml2::XMLElement* destinationElement = element->FirstChildElement("destination");

    TargetData::start = Target(startElement);
    TargetData::destination  = Target(destinationElement);

}
