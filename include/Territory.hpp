#ifndef TERRITORY_HPP
#define TERRITORY_HPP

#include <vector>
#include <string>

/**
 * Basic enumeration to easily identify factions
 */
enum Faction {
	Red,
	Green,
	Blue,
	Yellow,
	White,
	Orange
};

/**
 * Basic enumeration to easily identify labor type in territories
 */
enum LaborType {
	Slave,
	Paid
};

/**
 * Structure that contains all data related to a single territory
 */
struct Territory {
	struct {
		int id;
		int x,y;
		std::string name;
		std::vector<int> neighbors;
	}GameData;

	struct {
		Faction owner;
		int armies;
		LaborType labor;
		int turnsSinceLastRevolt;
	}OwnerData;

	struct {
		int baseCropProduction;
		int baseIndustrialProduction;
	}ConstData;
};

#endif // TERRITORY_HPP
