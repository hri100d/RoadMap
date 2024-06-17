#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "CrossRoad.h"

class Graph
{
private:

    std::vector<CrossRoad> _crossRoads;
    std::vector<std::string> _closedCrossRoads;

    int getIndexOfCrossRoad(const std::string&) const;
    void tourHelper(std::string, bool* [], std::vector<std::string>) const;
    int numberOfRoads() const;
    void checkForLoopHelper(std::string, std::string, bool*, std::vector<std::string>, bool) const;
    void dijkstra(const std::string&, const std::string&) const;

public:

    void readTheFile(const std::string&);
    int getSize() const;
    std::string getNameOfACrossRoad(const int&) const;
    std::vector<Link> getLinks(const std::string&) const;
    std::vector<CrossRoad> getCrossRoads() const;
    std::vector<std::string> getClosedCrossRoads();
    bool checkTheConnection(const std::string&, const std::string&) const;
    bool connectedToAll(const std::string&) const;
    void crossRoadsWithoutExit() const;
    void addClosedCrossRoads(const std::string&);
    void removeFromClosed(const std::string&);
    bool checkForLoop(const std::string&) const;
    void tour(const std::string&) const;
    void shortestPath(const std::string&, const std::string&) const;
    bool shortestPathWithoutClosed(const std::string&, const std::string&) const;
};
