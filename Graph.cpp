#include "Graph.h"

bool isNumber(const std::string& temp)
{
	for (int i = 0; i < temp.size(); i++)
	{
		if (!std::isdigit(temp[i]))
			return false;
	}

	return true;
}

int Graph::getIndexOfCrossRoad(const std::string& start) const
{
	int s = 0;
	for (int i = 0; i < _crossRoads.size(); i++)
	{
		if (_crossRoads[i].getName() == start)
		{
			return i;
		}
	}

	return -1;
}

//must be changed to verify the data
void Graph::readTheFile(const std::string& nameOfFile)
{
	std::ifstream myfile(nameOfFile + ".txt", std::ios::in);
	std::string word;
	std::vector<std::string> line;
	if (!myfile.is_open())
	{
		std::cout << "Error" << std::endl;
		return;
	}
	else
	{
		//putting all of the information from the file into one string vector
		while (myfile >> word)
		{
			line.push_back(word);
		}

		if (!line.empty())
		{

			int i = 0;
			while (line.size() > i + 1)
			{
				//taking the name of a crossroad
				CrossRoad road;
				if (!isNumber(line[i]) && !isNumber(line[i + 1]))
				{
					road.setName(line[i]);
				}

				i++;
				if (line.size() - 1 == i)
				{
					_crossRoads.push_back(road);
					road.setName(line[i]);
					_crossRoads.push_back(road);
					break;
				}

				//taking all of the conected crossroads with specific crossroad
				while ((!isNumber(line[i]) && isNumber(line[i + 1])) && line.size() > i)
				{
					Link link(line[i], std::stoi(line[i + 1]));
					if (road.getNumberOfLinks() == 0)
					{
						road.addLink(link);
					}
					else
					{
						for (int j = 0; j < road.getNumberOfLinks(); j++)
						{
							if (road.getLinks()[j].getName() != link.getName())
							{
								road.addLink(link);
							}
						}
					}
					i += 2;

					if (line.size() == i)
					{
						break;
					}

					if (line.size() - 1 == i)
					{
						_crossRoads.push_back(road);
						CrossRoad road;
						road.setName(line[i]);
						_crossRoads.push_back(road);
						break;
					}

				}

				if (line.size() != i + 1)
				{
					_crossRoads.push_back(road);
				}
			}
		}
	}
	myfile.close();
}

int Graph::getSize() const
{
	return _crossRoads.size();
}
std::string Graph::getNameOfACrossRoad(const int& index) const
{
	return _crossRoads[index].getName();
}
std::vector<Link> Graph::getLinks(const std::string& name) const
{
	return _crossRoads[getIndexOfCrossRoad(name)].getLinks();
}
std::vector<CrossRoad> Graph::getCrossRoads() const
{
	return _crossRoads;
}
std::vector<std::string> Graph::getClosedCrossRoads()
{
	return _closedCrossRoads;
}

bool Graph::checkTheConnection(const std::string& first, const std::string& second) const
{
	if (_crossRoads.size() == 0)
		return false;

	bool* visited = new bool[_crossRoads.size()];
	std::queue<std::string> que;
	que.push(_crossRoads[getIndexOfCrossRoad(first)].getName());

	while (!que.empty())
	{
		std::string temp = que.front();
		int indexOfCrossRoad = getIndexOfCrossRoad(temp);

		//if the element in the queue is the element we search for it returns true 
		if (temp == second)
		{
			delete[] visited;
			return true;
		}

		que.pop();

		for (size_t j = 0; j < _crossRoads[indexOfCrossRoad].getLinks().size(); ++j)
		{
			//pushing all of the links of non visited crossroads into the queue 
			if (visited[indexOfCrossRoad])
			{
				que.push(_crossRoads[indexOfCrossRoad].getLinks()[j].getName());
			}
		}

		//mark the cross road as visited
		visited[indexOfCrossRoad] = false;
	}

	delete[] visited;
	return false;
}

bool Graph::connectedToAll(const std::string& nameOfCrossRoad) const
{
	if (_crossRoads.size() == 0)
		return false;

	int count = 0;

	//if there are number of links equal to the number of the crossroads that means this specific crossroad is connected with all others
	if (_crossRoads[getIndexOfCrossRoad(nameOfCrossRoad)].getLinks().size() == _crossRoads.size() - 1)
	{
		return true;
	}
	
	for (size_t i = 0; i < _crossRoads.size(); ++i)
	{
		//adding one to count every time its connected with another
		if (checkTheConnection(nameOfCrossRoad, _crossRoads[i].getName()))
		{
			count++;
		}
	}

	//if count is equal to the number of crossroads it means its connected with all
	if (count == _crossRoads.size())
	{
		return true;
	}
	
	return false;
}

void Graph::crossRoadsWithoutExit() const
{
	if (_crossRoads.size() == 0)
		return;

	std::vector<std::string> _rossRoadsWithoutExit;

	for (size_t i = 0; i < _crossRoads.size(); ++i)
	{
		//find crossroad without any exit
		if (_crossRoads[i].getLinks().size() == 0)
		{
			//for (size_t j = 0; j < _crossRoads.size(); ++j)
			//{
			//	for (size_t t = 0; t < _crossRoads[j].getLinks().size(); ++t)
			//	{
			//		//find crossroads that are connected with the one without exit
			//		if (_crossRoads[j].getLinks()[t].getName() == _crossRoads[i].getName())
			//		{
			//			std::cout << _crossRoads[j].getName() << "->" << _crossRoads[i].getName() << std::endl;
			//		}
			//	}
			//}

			std::cout << _crossRoads[i].getName() << std::endl;
		}
	}
}
void Graph::addClosedCrossRoads(const std::string& name)
{
	for (int i = 0; i < _closedCrossRoads.size(); ++i)
	{
		if (_closedCrossRoads[i] == name)
		{
			return;
		}
	}
	_closedCrossRoads.push_back(name);
}
void Graph::removeFromClosed(const std::string& name)
{
	for (int i = 0; i < _closedCrossRoads.size(); ++i)
	{
		if (name == _closedCrossRoads[i])
		{
			_closedCrossRoads[i].erase();
			for (int j = i; j < _closedCrossRoads.size() - 1; ++j)
			{
				_closedCrossRoads[j] = _closedCrossRoads[j + 1];
			}
			_closedCrossRoads.resize(_closedCrossRoads.size() - 1);
		}
	}

}

bool Graph::checkForLoop(const std::string& name) const
{
	if (_crossRoads.size() > 0)
	{
		bool* visited = new bool[_crossRoads.size()];
		std::vector<std::string> v;
		bool temp = 0;
		checkForLoopHelper(name, name, visited, v, temp);
		delete[] visited;
		return temp;
	}

}
void Graph::checkForLoopHelper(std::string start, std::string name, bool* visited, std::vector<std::string> v,bool temp) const
{
	if (temp)
	{
		return;
	}

	int indexOfCrossRoad = getIndexOfCrossRoad(name);
	v.push_back(name);

	//after putting atleast three crossroads into the vector it checks if the last one is connected with the first one 
	if (v.size() >= 3 && checkTheConnection(v.back(), start))
	{
		temp = 1;
	}

	for (int j = 0; j < _crossRoads[indexOfCrossRoad].getLinks().size(); ++j)
	{
		//if some crossroad is not marked as visited is calling the function again with it and pushing it into the vector
		if (visited[getIndexOfCrossRoad(_crossRoads[indexOfCrossRoad].getLinks()[j].getName())])
		{
			visited[indexOfCrossRoad] = false;
			checkForLoopHelper(start, _crossRoads[indexOfCrossRoad].getLinks()[j].getName(), visited, v, temp);
		}
	}

	visited[indexOfCrossRoad] = true;
}

int Graph::numberOfRoads() const
{
	int count = 0;
	for (int i = 0; i < _crossRoads.size(); i++)
	{
		count += _crossRoads[i].getLinks().size();
	}
	return count;
}
void Graph::tourHelper(std::string name, bool* visited[], std::vector<std::string> v) const
{
	int indexOfCrossRoad = getIndexOfCrossRoad(name);
	v.push_back(name);

	//if the size of the vector is equal to the number of roads it prints the vector
	if (v.size() == numberOfRoads() + 1)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			std::cout << v[i] << "->";
		}
		std::cout << std::endl;
	}
	else
	{
		for (int i = 0; i < _crossRoads[indexOfCrossRoad].getLinks().size(); ++i)
		{
			//calling the function with the new crossroad that is not visited
			if (visited[indexOfCrossRoad][i])
			{
				visited[indexOfCrossRoad][i] = false;
				tourHelper(_crossRoads[indexOfCrossRoad].getLinks()[i].getName(), visited, v);
			}
		}
	}

	visited[indexOfCrossRoad][getIndexOfCrossRoad(v.back())] = true;
}
void Graph::tour(const std::string& name) const
{
	if (_crossRoads.size() == 0)
		return;

	bool** visited = new bool* [_crossRoads.size()];
	for (int i = 0; i < _crossRoads.size(); i++)
	{
		visited[i] = new bool[size_t(_crossRoads.size())];
	}

	std::vector<std::string> v;
	tourHelper(name, visited, v);

	for (int i = 0; i < _crossRoads.size(); i++)
	{
		delete visited[i];
	}

	delete[] visited;
}

void Graph::dijkstra(const std::string& start, const std::string& end) const
{
	int n = _crossRoads.size();
	std::vector<int> dist(n, INT_MAX);
	std::vector<int> prev(n, -1);
	std::vector<bool> visited(n, false);
	int startIndex = getIndexOfCrossRoad(start);
	int endIndex = getIndexOfCrossRoad(end);

	if (startIndex == -1 || endIndex == -1)
	{
		std::cout << "Start or end crossroad not found." << std::endl;
		return;
	}

	dist[startIndex] = 0;
	auto cmp = [&dist](int left, int right) { return dist[left] > dist[right]; };
	std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
	pq.push(startIndex);

	while (!pq.empty())
	{
		int u = pq.top();
		pq.pop();

		if (visited[u])
			continue;

		visited[u] = true;
		const std::vector<Link>& links = _crossRoads[u].getLinks();
		for (size_t i = 0; i < links.size(); ++i)
		{
			const Link& link = links[i];
			int v = getIndexOfCrossRoad(link.getName());
			int weight = link.getWeight();

			if (!visited[v] && dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;
				prev[v] = u;
				pq.push(v);
			}
		}
	}

	if (dist[endIndex] == INT_MAX)
	{
		std::cout << "No path found from " << start << " to " << end << std::endl;
		return;
	}

	std::vector<std::string> path;
	for (int at = endIndex; at != -1; at = prev[at])
	{
		path.push_back(_crossRoads[at].getName());
	}

	std::reverse(path.begin(), path.end());
	std::cout << "Shortest path from " << start << " to " << end << ": ";

	for (size_t i = 0; i < path.size(); ++i)
	{
		std::cout << path[i] << " ";
	}

	std::cout << "\nDistance: " << dist[endIndex] << std::endl;
}

void Graph::shortestPath(const std::string& first, const std::string& second) const
{
	dijkstra(first, second);

}
bool Graph::shortestPathWithoutClosed(const std::string& first, const std::string& second) const
{
	int size = _crossRoads.size();
	if (size < 1)
		return false;

	std::vector<bool> visited(size, false);
	for (int i = 0; i < _closedCrossRoads.size(); ++i)
	{
		visited[getIndexOfCrossRoad(_closedCrossRoads[i])] = true;
	}
	std::vector<int> dist(size, INT_MAX);
	std::vector<int> prev(size, -1);
	int startIndex = getIndexOfCrossRoad(first);
	int endIndex = getIndexOfCrossRoad(second);


	dist[startIndex] = 0;
	auto cmp = [&dist](int left, int right) { return dist[left] > dist[right]; };
	std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
	pq.push(startIndex);

	while (!pq.empty())
	{
		int u = pq.top();
		pq.pop();

		if (visited[u]) 
			continue;

		visited[u] = true;
		const std::vector<Link>& links = _crossRoads[u].getLinks();
		for (size_t i = 0; i < links.size(); ++i)
		{
			const Link& link = links[i];
			int v = getIndexOfCrossRoad(link.getName());
			int weight = link.getWeight();

			if (!visited[v] && dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;
				prev[v] = u;
				pq.push(v);
			}
		}
	}

	if (dist[endIndex] == INT_MAX)
	{
		std::cout << "No path found from " << first << " to " << second << std::endl;
		return false;
	}

	std::vector<std::string> path;
	for (int at = endIndex; at != -1; at = prev[at])
	{
		path.push_back(_crossRoads[at].getName());
	}

	std::reverse(path.begin(), path.end());
	std::cout << "Shortest path from " << first << " to " << second << ": ";

	for (size_t i = 0; i < path.size(); ++i)
	{
		std::cout << path[i] << " ";
	}

	std::cout << "\nDistance: " << dist[endIndex] << std::endl;

	return true;
}