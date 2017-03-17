#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Util.hpp"
#include "Game.hpp"
using namespace sf;
using namespace std;

int main() {
	srand(time(0));
	Game game("Resources/data/game.xml");
	game.start();

	return 0;
}
