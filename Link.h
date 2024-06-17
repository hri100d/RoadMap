#pragma once
#include <string>

class Link
{
private:

	std::string _name;
	int _weight;
public:

	Link(const std::string&, const int);
	std::string getName() const;
	int getWeight() const;

};

