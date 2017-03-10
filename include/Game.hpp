#ifndef GAME_HPP
#define GAME_HPP

#include "Territory.hpp"
#include "Cards.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game {
	std::vector<TerritoryCard> territoryCardDeck;
	std::vector<WildCard> wildCardDeck;
	std::vector<Player> players;

	Map rMap;

public:
	/**
	 * Primary constructor. Takes an XML file that specifies game properties (such as map image, data file, etc)
	 *
	 * \param gameFile XML file containing game parameters
	 */
	Game(std::string gameFile);

	/**
	 * Overall game loop that allows multiple games to played. Exit the program when it returns
	 */
	void start();

	/**
	 * Function for the menu of adding players
	 *
	 * \return True if the program should exit, false otherwise
	 */
	bool lobby();

	/**
	 * Function for initial territory assignment
	 *
	 * \return True if the program should exit, false otherwise
	 */
	bool gameStart();

	/**
	 * Function for main game play
	 *
	 * \return True if the program should exit, false otherwise
	 */
	bool mainGame();
};

#endif // GAME_HPP
