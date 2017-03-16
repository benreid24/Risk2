#include <iostream>
#include <SFML/Graphics.hpp>
#include "Util.hpp"
#include "Game.hpp"
using namespace sf;
using namespace std;

int main() {
	Game game("Resources/data/game.xml");
	game.start();

	return 0;
}
