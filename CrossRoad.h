#pragma once
#include <string>
#include <vector>
#include "Link.h"

class CrossRoad
{
private:

	std::string _name;
	std::vector<Link> _links;

public:

	void setName(const std::string&);
	int getNumberOfLinks() const;
	void addLink(Link& link);
	std::string getName() const;
	std::vector<Link> getLinks() const;
};

