#include "Game.hpp"
#include "Util.hpp"
using namespace std;
using namespace sf;

Game::Game(std::string gameFile) : tTree(&territories,&continents) {
	map<string,string> cfg = loadXML(gameFile);
	vector<Territory> ters;
	vector<Continent> conts;

	loadTerritoryCSV(ters,cfg["Risk2.Map.TerritoryFile"]);
	loadContinentCSV(conts,cfg["Risk2.Map.ContinentFile"]);

	TerritoryCard tCard;
	tCard.type = TerritoryCard::A;
	for (unsigned int i = 0; i<ters.size(); ++i) {
		territories[ters[i].GameData.id] = ters[i];
		tCard.id = ters[i].GameData.id;
		territoryCardDeck.push_back(tCard);
		tCard.type = TerritoryCard::Type(int(tCard.type)+1);
		if (tCard.type>TerritoryCard::C)
			tCard.type = TerritoryCard::A;
	}

	for (unsigned int i = 0; i<conts.size(); ++i) {
		continents[conts[i].id] = conts[i];
	}

	font.loadFromFile(cfg["Risk2.Media.Font"]);
	rMap = new Map(cfg["Risk2.Map.Image"],font);

	//TODO  - wild cards and players
}

void Game::start() {
	while (true) {
		if (lobby())
			break;
		if (gameStart())
			break;
		if (mainGame())
			break;
		break;
	}
}

bool Game::lobby() {
    //TODO - lobby menu
    return false;
}

bool Game::gameStart() {
	//TODO - assign territories randomly and go around letting players place troops
	return false;
}

bool Game::mainGame() {
	//TODO - go around and do player turns
	return false;
}
