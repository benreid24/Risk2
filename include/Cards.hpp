#ifndef CARDS_HPP
#define CARDS_HPP

/**
 * Basic structure to store territory card data. Used to determine initial troop placement as well as troop bonuses
 */
struct TerritoryCard {
	int id;
	enum Type {
		A,
		B,
		C
	}type;
};

/**
 * Basic enum to represent wild cards. May want to upgrade to a struct depending on what cards end up doing
 */
enum WildCard {
	Do,
	These
};

#endif // CARDS_HPP
