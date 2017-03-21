#ifndef GAME_HPP
#define GAME_HPP

#include "Territory.hpp"
#include "TerritoryTree.hpp"
#include "Cards.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Button.hpp"

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
	std::vector<Territory*> territoriesVec;
	std::map<int,Territory*> territories;
	std::map<int,Continent> continents;
	std::vector<TerritoryCard> territoryCardDeck;
	std::vector<WildCard> wildCardDeck;
	std::vector<Player> players;

	sf::RenderWindow window;
	std::map<std::string,Button*> lobbyButtons, startButtons, mainButtons;
	sf::Texture lobbyTxtr, startTxtr, mainTxtr;
	sf::Sprite lobbyBgnd, startBgnd, mainBgnd;
	Map* rMap;
	sf::Font font;
	sf::Texture arrowTxtr;
	sf::Sprite arrow;
	sf::RectangleShape playerRects[6];

	/**
	 * Internal enum used for determining which menu to render
	 */
	enum State {
		Lobby,
		Start,
		Main
	}state;

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

	/**
	 * Creates player objects and initializes territory owners
	 *
	 * \param numP The number of players
	 */
	void assignTerritories(int numP);

public:
	/**
	 * Primary constructor. Takes an XML file that specifies game properties (such as map image, data file, etc)
	 *
	 * \param gameFile XML file containing game parameters
	 */
	Game(std::string gameFile);

	/**
	 * Renders the map and current menu items to the window
	 */
	void render();

	/**
	 * Updates the window to display rendered content
	 */
	void display();

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
	 * \param f The Faction of the armies to place
	 * \param territory The id of the territory to place on
	 * \param amount The amount of armies to place
	 * \return True if the armies were placed, or false if the factions are not the same
	 */
	bool placeArmies(Faction f, int territory, int amount);

	/**
     * Returns the id of the current closest territory to the mouse
     *
     * \return The id of the closest territory, or -1 if none are nearby
     */
	int getClosestTerritory();

	/**
	 * Handles window events and tells whether or not the game should exit
	 *
	 * \return True if the game should stay open, false otherwise
	 */
	bool handleWindowEvents();
};

#endif // GAME_HPP
