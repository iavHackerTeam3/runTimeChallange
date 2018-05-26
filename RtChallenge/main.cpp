#include <iostream>
#include <fstream>
#include "utils/tinyxml2.h"
#include "model/Target.h"
#include "model/Cross.h"
#include "model/TargetData.h"
#include "model/Map.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if defined( _MSC_VER ) || defined (WIN32)
#include <crtdbg.h>
    #include <windows.h>
    #define WIN32_LEAN_AND_MEAN

    _CrtMemState startMemState;
    _CrtMemState endMemState;
#else
    #include <sys/stat.h>
	#include <sys/types.h>
#endif

#include <vector>
#define EPS 0.0000005

namespace tinyxml2 {
    class XMLDocument;
    class XMLElement;
    class XMLAttribute;
    class XMLComment;
    class XMLNode;
    class XMLText;
    class XMLDeclaration;
    class XMLUnknown;
    class XMLPrinter;
}  // namespace tinyxml2
using namespace std;

bool couldBeOnEdge(Target, Target);
vector<Target> routeToTargets(tinyxml2::XMLElement*);

void printVector(set<pair<const char *, double>> set);

int main() {
    string fileDir = "../data_0";

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( string(fileDir + "/targetData.xml").c_str() );
    if (error != tinyxml2::XML_SUCCESS) {
        cerr << "TargetData konnte nicht geladen werden" << endl;
        return 1;
    }

    tinyxml2::XMLElement* targetsElement = doc.FirstChildElement("targets");
    // Navigate to the title, using the convenience function,
    // with a dangerous lack of error checking.
    TargetData targetData(targetsElement);

    tinyxml2::XMLDocument mapDoc;
    tinyxml2::XMLError mapError = mapDoc.LoadFile( string(fileDir + "/map.xml").c_str() );

    if (mapError != tinyxml2::XML_SUCCESS) {
        cerr << "Konnte Map nicht laden." << endl;
        return 2;
    }

    tinyxml2::XMLElement* mapElement = mapDoc.FirstChildElement("map");
    Map map(mapElement);


    tinyxml2::XMLDocument carsDocs;
    tinyxml2::XMLError carsError = carsDocs.LoadFile( string( fileDir + "/carData_small.xml").c_str() );
    if (carsError != tinyxml2::XML_SUCCESS) {
        cerr << "Konnta Fahrzeuge nicht laden." << endl;
        return 3;
    }

    tinyxml2::XMLElement* cars = carsDocs.FirstChildElement( "cars" );
    tinyxml2::XMLElement* start = cars->FirstChildElement("start");
    tinyxml2::XMLElement* destination = cars->FirstChildElement("destination");
    tinyxml2::XMLElement* route = cars->FirstChildElement("route");
    for (; start != nullptr; ) {
        Target startTarget(start);
        Target destinationTarget(destination);
        vector<Target> waypoints = routeToTargets(route);

        Target t_first = waypoints.at(0);
        if (couldBeOnEdge(startTarget, t_first)) {

            for(auto edgeMap: map.edges) {
                Edge* edge = &edgeMap.second;

                if (edge->insertIfOnEdge(startTarget, t_first)) {
                    break;
                }
            }
        }
        unsigned int i;
        for(i = 0; i < waypoints.size() - 1; i++) {
            Target t1 = waypoints.at(i);
            Target t2 = waypoints.at(i + 1);

            if (couldBeOnEdge(t1, t2)) {
                for(auto edgeMap: map.edges) {
                    Edge* edge = &edgeMap.second;

                    if (edge->insertIfOnEdge(t1, t2)) {
                        //printVector( edge->timetable );
                        break;
                    }
                }
            }
        }

        Target t_last = waypoints.at(i);
        if (couldBeOnEdge(t_last, destinationTarget)) {
            for(auto edgeMap: map.edges) {
                Edge edge = edgeMap.second;

                if (edge.insertIfOnEdge(t_last, destinationTarget)) {
                    break;
                }
            }
        }

        start = start->NextSiblingElement("start");
        destination = destination->NextSiblingElement("destination");
        route = route->NextSiblingElement("route");
    }

    // READY For the Exercise now --> 26.05.2018 16:26

    Cross crossStart = map.findCross(targetData.start);
    Cross crossDestination = map.findCross(targetData.destination);

    double startTime = targetData.start.ts;
    double finalTime = targetData.destination.ts;
    vector<int> path;

    map.recursiveSearch(crossStart, crossDestination, 0, finalTime, path);

    return 0;
}

void printVector(set<pair<const char *, double>> set) {
    cout << "Print set" << endl;

    for(auto i: set) {
        cout << i.first << ": " << i.second << endl;
    }
}

bool couldBeOnEdge(Target t1, Target t2) {
    return (abs(t1.lat - t2.lat) < EPS) || (abs(t1.lng - t2.lng) < EPS);
}

vector<Target> routeToTargets(tinyxml2::XMLElement* route) {
    tinyxml2::XMLElement* ts = route->FirstChildElement("ts");
    tinyxml2::XMLElement* lat = route->FirstChildElement("lat");
    tinyxml2::XMLElement* lng = route->FirstChildElement("lng");

    vector<Target> targets;

    for(; ts != nullptr; ){
        Target target(ts->GetText(), lat->GetText(), lng->GetText());
        targets.push_back(target);

        ts = ts->NextSiblingElement("ts");
        lat = lat->NextSiblingElement("lat");
        lng = lng->NextSiblingElement("lng");
    }
    return targets;
}