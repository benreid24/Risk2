#include "Player.hpp"
#include "Game.hpp"
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
	}
	return true;
}
