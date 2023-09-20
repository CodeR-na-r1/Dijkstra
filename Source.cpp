#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <memory>

#include "Algorims.hpp"

using TGraph = std::map<std::string, std::vector<MyGraph::Edge>>;
using namespace std;

int main() {

	std::ifstream fileIn("GraphTask1.txt");

	if (!fileIn.is_open()) {
		cout << "File no open" << endl;
		return -1;
	}

	std::string from, to;

	fileIn >> from >> to;

	TGraph graph;
	for (uint32_t from, to, weight; fileIn >> from >> to >> weight;) {
		graph[std::to_string(from)].push_back({ std::to_string(to), weight });
	}
	fileIn.close();

	auto [dist, path] = Algorithms::Graph::dijkstra(std::make_shared<TGraph>(graph), from, to);
	
	cout << "Distance -> " << dist << endl;

	cout << "Path -> { ";
	for (auto vertex : path) {
		cout << vertex << " ";
	}
	cout << "}" << endl;

	return 0;
}