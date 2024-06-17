#pragma once
#include "Graph.h"
#include "CrossRoad.h"
#include "Link.h"

static std::string nameOfFile = "CrossRoads";


class Menu
{
private:

	std::string index = "";
	std::string location = "";
	std::string move = "";
	std::string closed = "";

	
	void neighbours(const std::vector<Link>&) const;
	void printClosed(const std::vector<std::string>&) const;
	void printTour(Graph&) const;
	bool checkLocation(const std::string&, Graph&) const;

public:

	void printMenu(Graph&);
};

