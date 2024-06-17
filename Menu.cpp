#include "Menu.h"


void Menu::neighbours(const std::vector<Link>& crossRoads) const
{
	for (int i = 0; i < crossRoads.size(); i++)
	{
		std::cout << crossRoads[i].getName() << " ";
	}
	std::cout << std::endl;
}
void Menu::printClosed(const std::vector<std::string>& crossRoads) const
{
	for (int i = 0; i < crossRoads.size(); i++)
	{
		std::cout << crossRoads[i] << " ";
	}
	std::cout << std::endl;
}
void Menu::printTour(Graph& graph) const
{
	for (int i = 0; i < graph.getSize(); i++)
	{
		graph.tour(graph.getNameOfACrossRoad(i));
	}
}
bool Menu::checkLocation(const std::string& name, Graph& graph) const
{
	for (int i = 0; i < graph.getSize(); i++)
	{
		if (graph.getCrossRoads()[i].getName() == name)
		{
			return true;
		}
	}
	return false;
}


void Menu::printMenu(Graph& graph)
{
	graph.readTheFile(nameOfFile);
	if (graph.getSize() > 0)
	{
		std::cout << "All possible locations: ";
		for (int i = 0; i < graph.getSize(); i++)
		{
			std::cout << graph.getNameOfACrossRoad(i) << " ";
		}
		std::cout << std::endl;
		std::cout << "Chose: ";
		std::cin >> location;
		while (!checkLocation(location, graph))
		{
			std::cout << "Invalid location please put another one: ";
			std::cin >> location;
		}
		std::cout << std::endl;
		while (index != "9")
		{
			std::cout << "1. Location" << std::endl;
			std::cout << "2. Change" << std::endl;
			std::cout << "3. Neighbours" << std::endl;
			std::cout << "4. Move" << std::endl;
			std::cout << "5. Close" << std::endl;
			std::cout << "6. Open" << std::endl;
			std::cout << "7. Closed" << std::endl;
			std::cout << "8. Tour" << std::endl;
			std::cout << "9. Stop the program" << std::endl;
			std::cin >> index;

			if (index == "1")
			{
				std::cout << "Your location is " << location;
				std::cout << std::endl;
			}
			else if (index == "2")
			{
				std::cout << "Chose new location:";
				std::cin >> location;
				while (!checkLocation(location, graph))
				{
					std::cout << "Invalid location please put another one: ";
					std::cin >> location;
				}
				std::cout << std::endl;
			}
			else if (index == "3")
			{
				std::cout << "Crossroad " << location << " is connected with those crossroads: ";
				neighbours(graph.getLinks(location));
			}
			else if (index == "4")
			{
				std::cout << "Chose location you want to go:";
				std::cin >> move;
				if (graph.checkTheConnection(location, move))
				{
					if(graph.shortestPathWithoutClosed(location, move))
						location = move;

					std::cout << std::endl;
				}
				else
				{
					std::cout << "There is no path that connect " << location << " with " << move << std::endl;
				}
			}
			else if (index == "5")
			{
				std::cout << "Chose crossroad that you want to mark as closed: ";
				std::cin >> closed;
				graph.addClosedCrossRoads(closed);
				std::cout << "There is the list of closed crossroads: ";
				printClosed(graph.getClosedCrossRoads());
			}
			else if (index == "6")
			{
				std::cout << "Closed ones: ";
				printClosed(graph.getClosedCrossRoads());
				std::cout << "Chose crossroad that you want to remove from closed: ";
				std::cin >> closed;
				graph.removeFromClosed(closed);
			}
			else if (index == "7")
			{
				std::cout << "There are the closed crossroads: ";
				printClosed(graph.getClosedCrossRoads());
			}
			else if (index == "8")
			{
				std::cout << "There are all possible tours:" << std::endl;
				printTour(graph);
			}
			else if (index == "9")
			{
				return;
			}
			else
			{
				std::cout << "Invalid index. Chose another one: ";

				std::cin >> index;
			}
		}
	}
	else
	{
		std::cout << "There is no information in the file";
	}
}