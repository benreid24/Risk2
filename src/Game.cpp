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

	//TODO - wild cards

	font.loadFromFile(cfg["Risk2.Media.Font"]);
	rMap = new Map(cfg["Risk2.Map.Image"],font);
    lobbyTxtr.loadFromFile(cfg["Risk2.Menu.Lobby.Background"]);
    startTxtr.loadFromFile(cfg["Risk2.Menu.Start.Background"]);
    mainTxtr.loadFromFile(cfg["Risk2.Menu.Main.Background"]);
    lobbyBgnd.setTexture(lobbyTxtr);
    startBgnd.setTexture(startTxtr);
    mainBgnd.setTexture(mainTxtr);

	VideoMode t = VideoMode::getDesktopMode();
	t.height *= 0.75;
	t.width = t.height*4/3;
	window.create(t, "Risk 2", Style::Close|Style::Titlebar|Style::Resize);
	View view(FloatRect(0,0,1600,1200));
	window.setView(view);
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
	state = Lobby;
    //TODO - lobby menu
    return false;
}

bool Game::gameStart() {
	state = Start;
	//TODO - assign territories randomly and go around letting players place troops
	return false;
}

bool Game::mainGame() {
	state = Main;
	//TODO - go around and do player turns

	while (window.isOpen()) {
		Event evt;
		while (window.pollEvent(evt)) {
			if (evt.type==Event::Closed)
				window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2f pos = Vector2f(Mouse::getPosition(window));
			pos = window.mapPixelToCoords(Vector2i(pos));
			int id = rMap->getClosetTerritory(territoriesVec,pos.x/1600,pos.y/1200);
			cout << territories[id].GameData.name << endl;
		}

		render();
		sleep(milliseconds(30));
	}

	return false;
}

void Game::render() {
	window.clear();
	switch (state) {
	case Lobby:
		window.draw(lobbyBgnd);
		for (map<string,Button>::iterator i = lobbyButtons.begin(); i!=lobbyButtons.end(); ++i)
			i->second.draw(window);
		break;
	case Start:
		window.draw(startBgnd);
		for (map<string,Button>::iterator i = startButtons.begin(); i!=startButtons.end(); ++i)
			i->second.draw(window);
		break;
	case Main:
		window.draw(mainBgnd);
		for (map<string,Button>::iterator i = mainButtons.begin(); i!=mainButtons.end(); ++i)
			i->second.draw(window);
		break;
	default:
		cout << "Error! Game.state is invalid!\n";
		break;
	}
	rMap->render(window,territoriesVec,IntRect(0,200,1600,1000));
	window.display();
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
