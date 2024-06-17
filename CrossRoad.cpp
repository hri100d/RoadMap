#include "CrossRoad.h"


void CrossRoad::setName(const std::string& name)
{
	_name = name;
}

int CrossRoad::getNumberOfLinks() const
{
	return _links.size();
}

void CrossRoad::addLink(Link& link)
{
	_links.push_back(link);
}

std::string CrossRoad::getName() const
{
	return _name;
}

std::vector<Link> CrossRoad::getLinks() const
{
	return _links;
}