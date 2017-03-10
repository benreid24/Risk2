#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Territory.hpp"
#include "Cards.hpp"

/**
 * Basic structure to store player data. No functionality is implemented here
 */
struct Player {
	std::string name; //?
	std::vector<TerritoryCard> cards;
	Faction faction;
};

#endif // PLAYER_HPP
