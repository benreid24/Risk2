#ifndef GAME_HPP
#define GAME_HPP

#include "Territory.hpp"
#include "Cards.hpp"
#include "Player.hpp"

class Game {
	std::vector<TerritoryCard> territoryCardDeck;
	std::vector<WildCard> wildCardDeck;
	std::vector<Player> players;

	//map data?

public:
	/**
	 * Primary constructor. Takes an XML file that specifies game properties (such as map image, data file, etc)
	 *
	 * \param gameFile XML file containing game parameters
	 */
	Game(std::string gameFile);

	/**
	 * Function for the menu of adding players
	 */
	void lobby();

	/**
	 * Function for initial territory assignment
};

#endif // GAME_HPP
