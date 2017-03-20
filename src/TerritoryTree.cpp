#include "TerritoryTree.hpp"
#include <iostream>
using namespace std;

TerritoryTree::TerritoryTree(map<int, Territory*>* ters, map<int,Continent>* conts) {
	territories = ters;
	continents = conts;
}

void TerritoryTree::assignContinents() {
	for (map<int,Territory*>::iterator i = territories->begin(); i!=territories->end(); ++i) {
        continents->at(i->second->GameData.continentId).territories.push_back(i->first);
	}
}

bool TerritoryTree::isNeighbor(int t1, int t2) {
	map<int,Territory*>::iterator i = territories->find(t1);
	if (i!=territories->end()) {
		for (unsigned int j = 0; j<i->second->GameData.neighbors.size(); ++j) {
			if (i->second->GameData.neighbors[j]==t2)
				return true;
		}
	}
	return false;
}

bool TerritoryTree::pathExists(int start, int dest) {
	map<int,bool> visited;
	Faction f = territories->at(start)->OwnerData.owner;

	vector<int> searchIds;
	searchIds.push_back(start);

	for (unsigned int sPos = 0; sPos<searchIds.size(); ++sPos) {
		map<int,Territory*>::iterator i = territories->find(searchIds[sPos]);
		for (unsigned int j = 0; j<i->second->GameData.neighbors.size(); ++j) {
			if (visited.find(i->second->GameData.neighbors[j])==visited.end()) { //not visited
				if (territories->at(i->second->GameData.neighbors[j])->OwnerData.owner==f) { //same faction
					if (i->second->GameData.neighbors[j]==dest) //reached end
						return true;
					searchIds.push_back(i->second->GameData.neighbors[j]); //add to list of nodes to check neighbors on
				}
			}
		}
		visited.insert(make_pair(i->second->GameData.id,true)); //mark as visited to avoid infinite loop
	}

	return false; //checked all territories but no path found
}

vector<int> TerritoryTree::getControlledContinents(Faction f) {
	vector<int> ret;

	for (map<int,Continent>::iterator i = continents->begin(); i!=continents->end(); ++i) {
		bool add = true;
		for (unsigned int j = 0; j<i->second.territories.size(); ++j) {
			if (territories->at(i->second.territories[j])->OwnerData.owner!=f) {
				add = false;
				break;
			}
		}
		if (add)
			ret.push_back(i->first);
	}

	return ret;
}
