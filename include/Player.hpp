#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Territory.hpp"
#include "Cards.hpp"

class Game;

/**
 * Base class for Player objects. Both local and remote players will derive from this
 */
class Player {
	Game* game;
	std::string name; //?
	std::vector<TerritoryCard> cards;
	Faction faction;

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
	bool assignArmies(int amount); //TODO - figure out GUI stuff

	/**
	 * This is a GUI function that allows the player to turn in, reinforce, attack and relocate armies
	 *
	 * \param armies The amount of armies available to the player to place (not counting if they decide to turn in)
	 * \return True if the game should close, false otherwise
	 */
	bool takeTurn(); //TODO - figure out how to indicate player resignation
};

#endif // PLAYER_HPP
