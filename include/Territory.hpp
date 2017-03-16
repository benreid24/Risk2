#ifndef TERRITORY_HPP
#define TERRITORY_HPP

#include <vector>
#include <string>

/**
 * Basic enumeration to easily identify factions
 */
enum Faction {
	Red = 0,
	Green = 1,
	Blue = 2,
	Yellow = 3,
	White = 4,
	Orange = 5
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
		int continentId;
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

/**
 * Structure that contains all data related to a single continent
 */
struct Continent {
	std::string name;
	int id;
	int moralBoost, moralDamage;
	std::vector<int> territories;
};

#endif // TERRITORY_HPP
