#include "TerritoryTree.hpp"
using namespace std;

TerritoryTree::TerritoryTree(map<int, Territory>* ters) {
	territories = ters;
}

bool TerritoryTree::isNeighbor(int t1, int t2) {
	map<int,Territory>::iterator i = territories->find(t1);
	if (i!=territories->end()) {
		for (unsigned int j = 0; j<i->second.GameData.neighbors.size(); ++j) {
			if (i->second.GameData.neighbors[j]==t2)
				return true;
		}
	}
	return false;
}

bool TerritoryTree::pathExists(int start, int dest) {
	map<int,bool> visited;
	Faction f = territories->at(start).OwnerData.owner;

	vector<int> searchIds;
	searchIds.push_back(start);

	for (unsigned int sPos = 0; sPos<searchIds.size(); ++sPos) {
		map<int,Territory>::iterator i = territories->find(searchIds[sPos]);
		for (unsigned int j = 0; j<i->second.GameData.neighbors.size(); ++j) {
			if (visited.find(i->second.GameData.neighbors[j])==visited.end()) { //not visited
				if (territories->at(i->second.GameData.neighbors[j]).OwnerData.owner==f) { //same faction
					if (i->second.GameData.neighbors[j]==dest) //reached end
						return true;
					searchIds.push_back(i->second.GameData.neighbors[j]); //add to list of nodes to check neighbors on
				}
			}
		}
		visited.insert(make_pair(i->second.GameData.id,true)); //mark as visited to avoid infinite loop
	}

	return false; //checked all territories but no path found
}
