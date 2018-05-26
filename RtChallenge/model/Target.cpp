//
// Created by emrea on 26.05.2018.
//

#include <iostream>
#include "Target.h"

Target::Target() {}
Target::Target(tinyxml2::XMLElement *element) {
    struct tm tm1;
    const char* time = element->FirstChildElement("ts")->GetText();
    Target::tsString = time;
    sscanf(time, "%2d.:%2d:%2d", &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    Target::ts = 3600 * tm1.tm_hour + 60 * tm1.tm_min + tm1.tm_sec;
    Target::lat = atof(element->FirstChildElement("lat")->GetText());
    Target::lng = atof(element->FirstChildElement("lng")->GetText());
}

Target::Target(const char *ts, const char *lat, const char *lng) {
    struct tm tm1;
    sscanf(ts, "%2d.:%2d:%2d", &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    Target::tsString = ts;
    Target::ts = 3600 * tm1.tm_hour + 60 * tm1.tm_min + tm1.tm_sec;
    Target::lat = atof(lat);
    Target::lng = atof(lng);
}
