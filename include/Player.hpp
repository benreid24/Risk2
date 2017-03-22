#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <string>
#include "Territory.hpp"
#include "TerritoryTree.hpp"
#include "Cards.hpp"
#include "Button.hpp"

class Game;
class Map;

/**
 * Base class for Player objects. Both local and remote players will derive from this
 */
class Player {
	Game* game;
	std::string name; //?
	std::vector<TerritoryCard> cards;
	Faction faction;

	friend class Game;

public:
	/**
	 * Primary constructor, initializes basic internal data
	 *
	 * \param g A point to the main Game object
	 * \param nm The name of the player
	 * \param color The Faction of the player
	 */
	Player(Game* g, std::string nm, Faction color);

	/**
	 * This is a GUI function to assign initial armies in the beginning
	 *
	 * \param amount The amount of armies the player can place
	 * \return True if the game should close, false otherwise
	 */
	bool assignArmies(int amount);

	/**
	 * This is a GUI function that allows the player to turn in, reinforce, attack and relocate armies
	 *
	 * \param rMap A pointer to the Map object
	 * \param buttons A reference to the map of buttons available to the player
	 * \param tTree A reference to a TerritoryTree
	 * \return True if the game should close, false otherwise
	 */
	bool takeTurn(Map* rMap, std::map<std::string,Button*>& buttons, TerritoryTree& tTree); //TODO - figure out how to indicate player resignation
};

#endif // PLAYER_HPP
