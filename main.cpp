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

	return 0;
}
