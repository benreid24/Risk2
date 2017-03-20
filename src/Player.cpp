#include "Player.hpp"
using namespace std;

Player::Player(Game* g, std::string nm, Faction color) {
	game = g;
	name = nm;
	faction = color;
}
