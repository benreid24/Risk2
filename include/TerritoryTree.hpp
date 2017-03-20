#ifndef TERRITORYTREE_HPP
#define TERRITORYTREE_HPP

#include "Territory.hpp"
#include <map>

/**
 * Helper class to encapsulate territory traversal and continent ownership
 */
class TerritoryTree {
	std::map<int,Territory*>* territories;
	std::map<int,Continent>* continents;

public:
	/**
	 * Builds the internal tree structure from the territories in the map
	 *
	 * \param ters A map containing all of the territories
	 * \param conts A map containing all of the continents
	 */
	TerritoryTree(std::map<int,Territory*>* ters, std::map<int,Continent>* conts);

	/**
	 * Assigns territories to the continents that they belong to
	 */
	void assignContinents();

	/**
	 * Tells whether or not two territories are adjacent
	 *
	 * \param t1 The first territory to check
	 * \param t2 The second territory to check
	 * \return True if they are neighbors, false otherwise
	 */
	bool isNeighbor(int t1, int t2);

	/**
	 * Tells whether or not the 2 given territories are connected by territories of the same faction
	 *
	 * \param start The territory to start at
	 * \param dest The territory to get to
	 * \return True if a path exists, false otherwise
	 */
	bool pathExists(int start, int dest);

	/**
	 * Returns a list of continents owned by the given Faction
	 *
	 * \param f The Faction to check for
	 * \return A vector of continent ids they own
	 */
	std::vector<int> getControlledContinents(Faction f);
};

#endif // TERRITORYTREE_HPP
