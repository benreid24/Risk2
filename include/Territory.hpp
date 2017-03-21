#ifndef TERRITORY_HPP
#define TERRITORY_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * Basic enumeration to easily identify factions
 */
enum Faction {
	Red = 0,
	Green = 1,
	Blue = 2,
	Yellow = 3,
	White = 4,
	Orange = 5,
	Neutral = 6
};

extern sf::Color colorMap[7];

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

	Territory() {
		GameData.id = GameData.x = GameData.y = GameData.continentId = OwnerData.armies = OwnerData.turnsSinceLastRevolt = ConstData.baseCropProduction = ConstData.baseIndustrialProduction = 0;
		OwnerData.owner = Faction::Neutral;
		OwnerData.labor = LaborType::Paid;
	}
};

/**
 * Structure that contains all data related to a single continent
 */
struct Continent {
	std::string name;
	int id;
	int troopBonus;
	int moralBoost, moralDamage;
	std::vector<int> territories;
};

#endif // TERRITORY_HPP
