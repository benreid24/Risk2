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

	return 0;
}
