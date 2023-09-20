#include "Edge.hpp"

#include <map>
#include <vector>
#include <string>

#include <algorithm>
#include <memory>

#define MAX_MARK 0xFFFFFFFF

using TGraph = std::map<std::string, std::vector<MyGraph::Edge>>;

namespace Algorithms {

	namespace Graph {

		std::pair<uint32_t, std::vector<std::string>> dijkstra(const std::shared_ptr<TGraph> g, const std::string& from, const std::string& to) {
			
			struct VertexInfo {
				uint32_t weightMark = MAX_MARK;
				bool isVisited = false;
			};

			// Создаем и инициализируем начальные пути
			std::map<std::string, VertexInfo> map;

			for (auto it = g->begin(); it != g->end(); it++)
			{
				if (it->first == from) {
					map.insert({ from, {0, false } });
				}
				else {
					map.insert({ it->first, {MAX_MARK, false} });
				}
			}

			std::map<std::string, std::string> mapPath; // Для восстановления пути

			std::string current = from;
			while (true) {

				for (auto it = (*g)[current].begin(); it != (*g)[current].end(); it++)
				{
					if (!map[it->to].isVisited && map[current].weightMark + it->weight < map[it->to].weightMark) {

						map[it->to].weightMark = map[current].weightMark + it->weight;
						mapPath[it->to] = current;
					}
				}

				map[current].isVisited = true;

				std::string next = "";
				uint32_t minMark = MAX_MARK;
				for (auto it = map.begin(); it != map.end(); it++) {
					if (!it->second.isVisited && it->second.weightMark < minMark) {
						next = it->first;
						minMark = it->second.weightMark;
					}
				}
				if (next == "") {
					break;
				}
				current = next;
			}

			std::vector<std::string> resPath;
			current = to;

			do {

				resPath.push_back(current);
				current = mapPath[current];

			} while (current != from);
			resPath.push_back(from);

			return { map[to].weightMark, { resPath.rbegin(), resPath.rend()} };
		} // dijkstra

	} // namespace Graph
	
} // namespace Algorithms