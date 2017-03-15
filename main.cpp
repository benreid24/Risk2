#include <iostream>
#include <SFML/Graphics.hpp>
#include "Util.hpp"
using namespace sf;
using namespace std;

int main() {
	map<string,string> t = loadXML("Resources/data/game.xml");

	for (map<string,string>::iterator i = t.begin(); i!=t.end(); ++i) {
        cout << i->first << " -> " << i->second << endl;
	}

	vector<Territory> ters;
	vector<Continent> cons;
	loadTerritoryCSV(ters,t["Risk2.Map.TerritoryFile"]);
	loadContinentCSV(cons,t["Risk2.Map.ContinentFile"]);

	for (unsigned int i = 0; i<ters.size(); ++i) {
		cout << "Territory: Id(" << ters[i].GameData.id << "), Name(" << ters[i].GameData.name << "), Continent(" << ters[i].GameData.continentId <<"), NumNeighbors(" << ters[i].GameData.neighbors.size() << ")\n";
	}

	return 0;
}
