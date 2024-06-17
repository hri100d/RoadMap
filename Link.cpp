#include "Link.h"

Link::Link(const std::string& name, const int weight) : _name(name), _weight(weight)
{

}
std::string Link::getName() const
{
	return _name;
}
int Link::getWeight() const
{
	return _weight;
}
