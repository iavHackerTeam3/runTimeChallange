//
// Created by emrea on 26.05.2018.
//

#include <vector>
#include <iostream>
#include "Map.h"
#include "Cross.h"
#define EPS 0.000005

double str2double(const char*);

Map::Map() {}
Map::Map(tinyxml2::XMLElement *mapElement) {

    map< int, Cross> crosses;
    tinyxml2::XMLElement* cross;
    for (cross = mapElement->FirstChildElement( "cross" ); cross != nullptr; cross = cross->NextSiblingElement("cross") ) {
        Cross cross1(cross);

        crosses.insert( std::make_pair(cross1.id, cross1));
    }

    Map::crosses = crosses;

    // Erstellen der Kanten
    map< pair<int, int>, Edge> edges;
    for (auto &crosse : Map::crosses) {

        vector<int> networkArray = this->split(crosse.second.network, " ");
        for(int &networkId: networkArray) {
            pair<int, int> key = make_pair(crosse.first, networkId);
            Edge value = Edge(crosse.second, getCross(networkId));

            edges.insert(make_pair(key, value));
        }
    }
    Map::edges = edges;
}

Cross Map::getCross(int id) {
    return this->crosses.at(id);
}

Cross Map::findCross(Target target) {
    for(auto c: this->crosses) {
        if (abs(c.second.lat - target.lat) < EPS && abs(c.second.lng - target.lng) < EPS) {
            return c.second;
        }
    }
}

void Map::recursiveSearch(Cross start, Cross destination, double startTime, double finalTime, vector<int> pathCopy) {
    vector<int> networkArray = this->split(start.network, " ");

    for (auto neighbourId: networkArray) {
        Cross destinationCross = getCross(neighbourId);

        double timeOnEdge = this->timeOnEdge(start, destinationCross, startTime);

        if (startTime + timeOnEdge > finalTime) {
            cout << "Ziel erreicht, jedoch stimmt die Zeit nicht ...." << startTime + timeOnEdge << endl;
            return;
        } else if ( abs(startTime + timeOnEdge - finalTime) < EPS) {
            // TODO printVector

            if (destination.id == neighbourId) {
                cout << "FINISH" << endl;
            } else {
                cout << "hmmmm.." << endl;
            }
            return;
        } else {
            pathCopy.push_back(neighbourId);
            recursiveSearch(getCross(neighbourId), destination, startTime + timeOnEdge, finalTime, pathCopy);
        }
    }
    cout << "Keine Route gefunden." << endl;
}

double Map::timeOnEdge(Cross start, Cross destination, double startTime) {
    Edge edge = edges.at(make_pair(start.id, destination.id));

    double sGefahren = 0;
    double sGesamt = abs(destination.lat - start.lat) + abs(destination.lng - start.lng);
    double timeGesamt = 0;

    for (int i= 1; i < edge.timetable.size(); i++) {
        pair<const char*, double> entryIntervall = edge.timetable.at(i - 1);
        pair<const char*, double> exitIntervall = edge.timetable.at(i);

        if (startTime > str2double(exitIntervall.first)) {
            continue;
        } else if (sGefahren < sGesamt) {
            if (startTime > str2double(entryIntervall.first)) {
                double tDiffIntervall = str2double(exitIntervall.first) - startTime;
                double v = entryIntervall.second;

                sGefahren += v * tDiffIntervall;
                timeGesamt += tDiffIntervall;
            } else {
                double tDiffIntervall = str2double(exitIntervall.first) - str2double(entryIntervall.first);
                double v = entryIntervall.second;

                sGefahren += v * tDiffIntervall;
                timeGesamt += tDiffIntervall;
            }
        } else {
            break;
        }
    }

    return timeGesamt;
}

double str2double(const char* time) {
    struct tm tm1;
    sscanf(time, "%2d.:%2d:%2d", &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    return (3600 * tm1.tm_hour + 60 * tm1.tm_min + tm1.tm_sec);
}

vector<int> Map::split(const string& str, const string& delim)
{
    vector<int> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();

        string token = str.substr(prev, pos-prev);
        if (!token.empty())
            tokens.push_back(atoi(token.c_str()));

        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}