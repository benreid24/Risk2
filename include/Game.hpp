#ifndef GAME_HPP
#define GAME_HPP

#include "Territory.hpp"
#include "TerritoryTree.hpp"
#include "Cards.hpp"
#include "Player.hpp"
#include "Map.hpp"

/**
 * Basic enum to encode battle results
 */
enum BattleResult {
	Stalemate,
	DefenderCaptured,
	InvalidAttack
};

/**
 * Overall game class. Mostly serves as the data model/controller but also owns the GUI elements
 */
class Game {
	TerritoryTree tTree;
	std::vector<Territory> territoriesVec;
	std::map<int,Territory> territories;
	std::map<int,Continent> continents;
	std::vector<TerritoryCard> territoryCardDeck;
	std::vector<WildCard> wildCardDeck;
	std::vector<Player> players;

	Map* rMap;
	sf::Font font;

	sf::RenderWindow window;
	//more GUI stuff

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
	 * This function does the action of attacking one territory from another. Updates internal data
	 *
	 * \param attacker The id of the territory attacking
	 * \param defender The id of the territory being attacked
	 * \return A BattleResult the reflects what happened
	 */
	BattleResult attackTerritory(int attacker, int defender);

	/**
	 * Moves armies from one territory to another, provided that at least 1 army remains and that a path exists
	 *
	 * \param start The id of territory to move from
	 * \param dest The id of the territory to move to
	 * \return True if the armies could be moved, false otherwise
	 */
	bool moveArmies(int start, int dest, int amount);

	/**
	 * Draws a TerritoryCard from the deck and returns it
	 *
	 * \return The card drawn
	 */
	TerritoryCard drawTerritoryCard();

	/**
	 * Draws a WildCard from the deck and returns it
	 *
	 * \return The card drawn
	 */
	WildCard drawWildCard();

	/**
	 * Returns the passed card to the deck. Use this for turn ins and when a player is out
	 *
	 * \param c The card to add
	 */
	void returnCard(TerritoryCard t);

	/**
	 * Places armies on the given territory
	 *
	 * \param territory The id of the territory to place on
	 * \param amount The amount of armies to place
	 */
	void placeArmies(int territory, int amount);
};

#endif // GAME_HPP
