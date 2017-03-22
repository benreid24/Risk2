#include "Player.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Player::Player(Game* g, std::string nm, Faction color) {
	game = g;
	name = nm;
	faction = color;
}

bool Player::assignArmies(int amount) {
	while (game->handleWindowEvents()) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			int id = game->getClosestTerritory();
			if (id!=-1) {
				if (game->placeArmies(faction,id,1)) {
					amount--;
					if (amount<=0)
						return false;
				}
			}
		}

		game->render();
		game->display();
		sleep(milliseconds(30));
	}

	return true;
}

bool Player::takeTurn(Map* rMap, map<string,Button*>& buttons, TerritoryTree& tTree) {
	int selectedTerritory = -1;
	int targetTerritory = -1;

	int fWait = 0;
	while (game->handleWindowEvents()) {
		if (Mouse::isButtonPressed(Mouse::Left) && fWait==0) {
			int id = game->getClosestTerritory();
			if (id!=-1) {
				fWait = 10;
				Color m = colorMap[tTree.getTerritory(id)->OwnerData.owner];
				Color s(abs(128-m.r),abs(128-m.g),abs(128-m.b));
				m.r = 255-m.r;
				m.g = 255-m.g;
				m.b = 255-m.b;
				if (selectedTerritory==-1 || !tTree.isNeighbor(selectedTerritory,id) || id==targetTerritory || targetTerritory!=-1) {
					if (selectedTerritory!=-1)
						rMap->deselectTerritory(selectedTerritory);
					selectedTerritory = id;
					if (targetTerritory!=-1) {
						rMap->deselectTerritory(targetTerritory);
						game->selectTerritory(-1,true);
					}
					targetTerritory = -1;
					game->selectTerritory(id);
					rMap->selectTerritory(id,m);
				}
				else if (targetTerritory==-1 && tTree.isNeighbor(selectedTerritory,id)) {
                    targetTerritory = id;
                    game->selectTerritory(id,true);
                    rMap->selectTerritory(id,s);
				}
			}
            else {
                if (selectedTerritory!=-1)
					rMap->deselectTerritory(selectedTerritory);
				if (targetTerritory!=-1)
					rMap->deselectTerritory(targetTerritory);
				game->selectTerritory(-1);
				game->selectTerritory(-1,true);
				selectedTerritory = targetTerritory = -1;
            }
		}

		if (fWait>0)
			fWait--;

		game->render();
		game->display();
		sleep(milliseconds(30));
	}

	return true;
}
