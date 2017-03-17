#include "Game.hpp"
#include "Util.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Game::Game(std::string gameFile) : tTree(&territories,&continents) {
	map<string,string> cfg = loadXML(gameFile);
	vector<Continent> conts;

	loadTerritoryCSV(territoriesVec,cfg["Risk2.Map.TerritoryFile"]);
	loadContinentCSV(conts,cfg["Risk2.Map.ContinentFile"]);
	TerritoryCard tCard;
	tCard.type = TerritoryCard::A;
	for (unsigned int i = 0; i<territoriesVec.size(); ++i) {
		territories[territoriesVec[i].GameData.id] = territoriesVec[i];
		tCard.id = territoriesVec[i].GameData.id;
		territoryCardDeck.push_back(tCard);
		tCard.type = TerritoryCard::Type(int(tCard.type)+1);
		if (tCard.type>TerritoryCard::C)
			tCard.type = TerritoryCard::A;
	}
	for (unsigned int i = 0; i<conts.size(); ++i) {
		continents[conts[i].id] = conts[i];
	}
	tTree.assignContinents();

	font.loadFromFile(cfg["Risk2.Media.Font"]);
	rMap = new Map(cfg["Risk2.Map.Image"],font);

	//TODO  - wild cards and players

	window.create(VideoMode(1600,1200,32), "Risk 2", Style::Close|Style::Titlebar|Style::Resize);
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

	while (window.isOpen()) {
		Event evt;
		while (window.pollEvent(evt)) {
			if (evt.type==Event::Closed)
				window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			int id = rMap->getClosetTerritory(territoriesVec,pos.x/1600,pos.y/1200);
			cout << territories[id].GameData.name << endl;
		}

		window.clear();
		rMap->render(window,territoriesVec,IntRect(0,0,1600,1200));
		window.display();
		sleep(milliseconds(30));
	}

	return false;
}

BattleResult Game::attackTerritory(int attacker, int defender) {
	//TODO - battle
	return BattleResult::InvalidAttack;
}

bool Game::moveArmies(int start, int dest, int amount) {
	if (tTree.pathExists(start,dest)) { //this also ensures that both territories are the same faction
		if (territories[start].OwnerData.armies-amount>=1) {
			territories[start].OwnerData.armies -= amount;
			territories[dest].OwnerData.armies += amount;
			return true;
		}
	}
	return false;
}

TerritoryCard Game::drawTerritoryCard() {
	int i = getRandom(0,territoryCardDeck.size());
	TerritoryCard ret = territoryCardDeck[i];
	territoryCardDeck.erase(territoryCardDeck.begin()+i);
	return ret;
}

WildCard Game::drawWildCard() {
	int i = getRandom(0,wildCardDeck.size());
	WildCard ret = wildCardDeck[i];
	wildCardDeck.erase(wildCardDeck.begin()+i);
	return ret;
}

void Game::returnCard(TerritoryCard t) {
	territoryCardDeck.push_back(t);
}

void Game::placeArmies(int territory, int amount) {
	territories[territory].OwnerData.armies += amount;
}
