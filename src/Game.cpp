#include "Game.hpp"
#include "Util.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Color colorMap[7] = {Color::Red,Color::Green,Color::Blue,Color::Yellow,Color::White,Color(255,165,0),Color(180,180,180)};

Game::Game(std::string gameFile) : tTree(&territories,&continents) {
	map<string,string> cfg = loadXML(gameFile);
	vector<Continent> conts;

	loadTerritoryCSV(territoriesVec,cfg["Risk2.Map.TerritoryFile"]);
	loadContinentCSV(conts,cfg["Risk2.Map.ContinentFile"]);
	TerritoryCard tCard;
	tCard.type = TerritoryCard::A;
	for (unsigned int i = 0; i<territoriesVec.size(); ++i) {
		territories[territoriesVec[i]->GameData.id] = territoriesVec[i];
		tCard.id = territoriesVec[i]->GameData.id;
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
    butHighlightTxtr.loadFromFile(cfg["Risk2.Menu.Main.LaborHighlight"]);
    butHighlight.setTexture(butHighlightTxtr);
    lobbyButtons.insert(make_pair("UpButton",new Button(window,cfg["Risk2.Menu.Lobby.UpButton"],Vector2f(stringToInt(cfg["Risk2.Menu.Lobby.UpX"]),stringToInt(cfg["Risk2.Menu.Lobby.UpDownY"])))));
    lobbyButtons.insert(make_pair("DownButton",new Button(window,cfg["Risk2.Menu.Lobby.DownButton"],Vector2f(stringToInt(cfg["Risk2.Menu.Lobby.DownX"]),stringToInt(cfg["Risk2.Menu.Lobby.UpDownY"])))));
    lobbyButtons.insert(make_pair("PlayButton",new Button(window,cfg["Risk2.Menu.Lobby.PlayButton"],Vector2f(stringToInt(cfg["Risk2.Menu.Lobby.PlayX"]),stringToInt(cfg["Risk2.Menu.Lobby.PlayY"])))));
	mainButtons.insert(make_pair("Attack",new Button(window,cfg["Risk2.Menu.Main.Attack"],Vector2f(stringToInt(cfg["Risk2.Menu.Main.AttackX"]),stringToInt(cfg["Risk2.Menu.Main.AttackY"])))));
	mainButtons.insert(make_pair("LaborSlave",new Button(window,cfg["Risk2.Menu.Main.LaborSlave"],Vector2f(stringToInt(cfg["Risk2.Menu.Main.LaborSlaveX"]),stringToInt(cfg["Risk2.Menu.Main.LaborY"])))));
	mainButtons.insert(make_pair("LaborFree",new Button(window,cfg["Risk2.Menu.Main.LaborFree"],Vector2f(stringToInt(cfg["Risk2.Menu.Main.LaborFreeX"]),stringToInt(cfg["Risk2.Menu.Main.LaborY"])))));
	mainButtons.insert(make_pair("DoneAttack",new Button(window,cfg["Risk2.Menu.Main.DoneAttack"],Vector2f(stringToInt(cfg["Risk2.Menu.Main.DoneAttackX"]),stringToInt(cfg["Risk2.Menu.Main.DoneAttackY"])))));
	mainButtons.insert(make_pair("Transfer",new Button(window,cfg["Risk2.Menu.Main.Transfer"],Vector2f(stringToInt(cfg["Risk2.Menu.Main.TransferX"]),stringToInt(cfg["Risk2.Menu.Main.TransferY"])))));
	mainButtons.insert(make_pair("DoneTransfer",new Button(window,cfg["Risk2.Menu.Main.DoneTransfer"],Vector2f(stringToInt(cfg["Risk2.Menu.Main.DoneTransferX"]),stringToInt(cfg["Risk2.Menu.Main.DoneTransferY"])))));

	Player::promptTxtr.loadFromFile(cfg["Risk2.Menu.ArmyPrompt"]);
    Player::prompt.setTexture(Player::promptTxtr);
    Player::prompt.setPosition(800-Player::promptTxtr.getSize().x/2,210);
    Player::armyText.setFont(font);
    Player::armyText.setPosition(800,240);
    Player::armyText.setColor(Color::Black);
    Player::upArrow = new Button(window,cfg["Risk2.Menu.Lobby.UpButton"],Vector2f(732,250));
    Player::downArrow = new Button(window,cfg["Risk2.Menu.Lobby.DownButton"],Vector2f(847,250));
    Player::done = new Button(window,cfg["Risk2.Menu.ConfirmButton"],Vector2f(753,280));

	VideoMode t = VideoMode::getDesktopMode();
	t.height *= 0.75;
	t.width = t.height*4/3;
	window.create(t, "Risk 2", Style::Close|Style::Titlebar|Style::Resize);
	View view(FloatRect(0,0,1600,1200));
	window.setView(view);
}

bool Game::handleWindowEvents() {
	Event evt;
	while (window.pollEvent(evt)) {
		if (evt.type==Event::Closed) {
			window.close();
			return false;
		}
	}
	return true;
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
    sf::Text pCountTxt;
    int pCount = 2;
    int fDelay = 0;

    pCountTxt.setPosition(Vector2f(800,70));
    pCountTxt.setFont(font);
    pCountTxt.setCharacterSize(40);
    pCountTxt.setColor(Color::Black);
    pCountTxt.setString("2");

    while (window.isOpen()) {
		if (!handleWindowEvents())
			break;

		if (fDelay>0)
			fDelay--;

		if (lobbyButtons["UpButton"]->isClicked() && pCount<6 && fDelay==0) {
			pCount++;
			pCountTxt.setString(intToString(pCount));
			fDelay = 10;
		}
		if (lobbyButtons["DownButton"]->isClicked() && pCount>2 && fDelay==0) {
			pCount--;
			pCountTxt.setString(intToString(pCount));
			fDelay = 10;
		}
		if (lobbyButtons["PlayButton"]->isClicked()) {
			assignTerritories(pCount); //TODO - maybe just create players here (allow name setting, get network players, etc)
			return false;
		}

		render();
		window.draw(pCountTxt);
		display();
		sleep(milliseconds(30));
    }

    return true;
}

bool Game::gameStart() {
	state = Start;
	int armies = 20; //TODO - make initial army count dynamic

	for (unsigned int i = 0; i<players.size(); ++i) {
		playerRects[i].setFillColor(colorMap[int(players[i].faction)]);
		playerRects[i].setSize(Vector2f(240,20));
		playerRects[i].setPosition(1330,40+i*25);
	}
	arrowTxtr.loadFromFile("Resources/images/arrow.png");
	arrow.setTexture(arrowTxtr);
    arrow.setPosition(1275,40);
    armyLeftText.setFont(font);
    armyLeftText.setPosition(985,23);
    armyLeftText.setCharacterSize(40);
    armyLeftText.setColor(Color::Black);
    armyLeftText.setString(intToString(armies));

    while (armies>0) {
		for (unsigned int i = 0; i<players.size(); ++i) {
			arrow.setPosition(1280,40+i*25);
			if (players[i].assignArmies(1))
				return true;
		}
		armies--;
		armyLeftText.setString(intToString(armies));
    }

	return false;
}

bool Game::mainGame() {
	state = Main;
	turnPhase.setColor(Color::Yellow);
	turnPhase.setCharacterSize(30);
	turnPhase.setPosition(20,60);
	turnPhase.setFont(font);
	pName.setColor(Color::Black);
	pName.setCharacterSize(22);
	pName.setPosition(503,44);
	pName.setFont(font);
	pCrop.setColor(Color::Black);
	pCrop.setCharacterSize(20);
	pCrop.setPosition(503,88);
	pCrop.setFont(font);
	pMorale.setColor(Color::Black);
	pMorale.setCharacterSize(20);
	pMorale.setPosition(503,65);
	pMorale.setFont(font);
	pIndustry.setColor(Color::Black);
	pIndustry.setCharacterSize(20);
	pIndustry.setPosition(503,110);
	pIndustry.setFont(font);
	pTurnIn.setColor(Color::Black);
	pTurnIn.setCharacterSize(20);
	pTurnIn.setPosition(503,132);
	pTurnIn.setFont(font);
	tName.setFont(font);
	tName.setColor(Color::Black);
	tName.setCharacterSize(22);
	tName.setPosition(881,46);
	t2Name.setFont(font);
	t2Name.setColor(Color::Blue);
	t2Name.setCharacterSize(22);
	t2Name.setPosition(1094,46);
	tCrop.setColor(Color::Black);
	tCrop.setCharacterSize(20);
	tCrop.setPosition(881,73);
	tCrop.setFont(font);
	tIndustry.setColor(Color::Black);
	tIndustry.setCharacterSize(20);
	tIndustry.setPosition(881,97);
	tIndustry.setFont(font);
	pMessage.setColor(Color::Black);
	pMessage.setPosition(32,130);
	pMessage.setCharacterSize(24);
	pMessage.setFont(font);
	mainButtons["DoneAttack"]->setHidden(true);
	mainButtons["DoneTransfer"]->setHidden(true);
	mainButtons["Transfer"]->setHidden(true);
	mainButtons["Attack"]->setHidden(true);

	while (true) {
		for (unsigned int i = 0; i<players.size(); ++i) {
			//setup
			pName.setString(players[i].name);
			int crop = sumCropProduction(players[i].faction);
			int industry = sumIndustrialProduction(players[i].faction);
			int morale = crop+industry; //TODO - calculate morale
			pCrop.setString(intToString(crop));
			pIndustry.setString(intToString(industry));
			pMorale.setString(intToString(morale));
			pTurnIn.setString("Unavailable");
			arrow.setPosition(1280,40+i*25);
			selectTerritory(-1);

			//reinforce
			turnPhase.setString("Reinforce");
			int armies = industry/10;
			for (int j = 0; j<armies; ++j) {
				pMessage.setString("Armies to place: "+intToString(armies-j));
				if (players[i].assignArmies(1))
					return true;
				sleep(milliseconds(150));
			}
			sleep(milliseconds(250));
			pMessage.setString("");

			//attack
			turnPhase.setString("Attack");
			if (players[i].takeTurn(rMap,mainButtons,tTree))
				return true;
			sleep(milliseconds(250));

			//transfer
			turnPhase.setString("Transfer");
			if (players[i].reinforce(rMap,mainButtons,tTree))
				return true;
		}
	}

	return false;
}

void Game::selectTerritory(int id, bool t) {
	if (!t) {
		if (id==-1) {
			tName.setString("");
			tCrop.setString("");
			tIndustry.setString("");
			mainButtons["LaborSlave"]->setHidden(true);
			mainButtons["LaborFree"]->setHidden(true);
			butHighlight.setColor(Color::Transparent);
		}
		else {
			tName.setString(territories[id]->GameData.name);
			tCrop.setString(intToString(territories[id]->ConstData.baseCropProduction));
			tIndustry.setString(intToString(territories[id]->ConstData.baseIndustrialProduction));
			mainButtons["LaborSlave"]->setHidden(false);
			mainButtons["LaborFree"]->setHidden(false);
			butHighlight.setColor(Color::White);
			if (territories[id]->OwnerData.labor==LaborType::Slave)
				butHighlight.setPosition(mainButtons["LaborSlave"]->getPosition()+Vector2f(-2,-2));
			else
				butHighlight.setPosition(mainButtons["LaborFree"]->getPosition()+Vector2f(-2,-2));
		}
	}
	else {
		if (id==-1)
			t2Name.setString("");
		else
			t2Name.setString(territories[id]->GameData.name);
	}
}

void Game::render() {
	vector<Territory*> empt;
	window.clear();
	switch (state) {
	case Lobby:
		window.draw(lobbyBgnd);
		for (map<string,Button*>::iterator i = lobbyButtons.begin(); i!=lobbyButtons.end(); ++i)
			i->second->draw();
		rMap->render(window,empt,IntRect(0,200,1600,1000));
		break;
	case Start:
		window.draw(startBgnd);
		for (map<string,Button*>::iterator i = startButtons.begin(); i!=startButtons.end(); ++i)
			i->second->draw();
		rMap->render(window,territoriesVec,IntRect(0,200,1600,1000));
		for (unsigned int i = 0; i<players.size(); ++i) {
			window.draw(playerRects[i]);
		}
		window.draw(armyLeftText);
		window.draw(arrow);
		break;
	case Main:
		window.draw(mainBgnd);
		window.draw(butHighlight);
		for (map<string,Button*>::iterator i = mainButtons.begin(); i!=mainButtons.end(); ++i)
			i->second->draw();
		for (unsigned int i = 0; i<players.size(); ++i) {
			window.draw(playerRects[i]);
		}
		window.draw(arrow);
		rMap->render(window,territoriesVec,IntRect(0,200,1600,1000));
		window.draw(turnPhase);
		window.draw(pMessage);
		window.draw(pName);
		window.draw(pMorale);
		window.draw(pCrop);
        window.draw(pIndustry);
        window.draw(pTurnIn);
        window.draw(tName);
        window.draw(t2Name);
        window.draw(tCrop);
        window.draw(tIndustry);
		break;
	default:
		cout << "Error! Game.state is invalid!\n";
		break;
	}
}

void Game::draw(Drawable& d) {
	window.draw(d);
}

void Game::display() {
	window.display();
}

int Game::sumCropProduction(Faction f) {
	int r = 0;
	int m[2] = {3,1};
	for (unsigned int i = 0; i<territoriesVec.size(); ++i) {
		if (territoriesVec[i]->OwnerData.owner==f)
			r += territoriesVec[i]->ConstData.baseCropProduction*m[territoriesVec[i]->OwnerData.labor];
	}
	return r;
}

int Game::sumIndustrialProduction(Faction f) {
	int r = 0;
	int m[2] = {3,1};
	for (unsigned int i = 0; i<territoriesVec.size(); ++i) {
		if (territoriesVec[i]->OwnerData.owner==f)
			r += territoriesVec[i]->ConstData.baseIndustrialProduction*m[territoriesVec[i]->OwnerData.labor];
	}
	return r;
}

int Game::getClosestTerritory() {
	Vector2f pos = Vector2f(Mouse::getPosition(window));
    pos = window.mapPixelToCoords(Vector2i(pos));
	return rMap->getClosetTerritory(territoriesVec,pos.x/1600,(pos.y-200)/1000);
}

void Game::assignTerritories(int numP) {
	for (int i = 0; i<numP; ++i) {
        players.push_back(Player(this,"Player",Faction(i)));
	}

	vector<int> terV;
	for (int i = 1; i<=42; ++i)
		terV.push_back(i);

	int t = 42/numP;
	for (int i = 0; i<numP; ++i) {
		for (int j = 0; j<t; ++j) {
            int k = getRandom(0,terV.size());
            int id = terV[k];
            territories[id]->OwnerData.armies = 1;
            territories[id]->OwnerData.owner = players[i].faction;
            terV.erase(terV.begin()+k);
		}
	}
	for (unsigned int i = 0; i<terV.size(); ++i) {
		territories[terV[i]]->OwnerData.owner = Faction::Neutral;
		territories[terV[i]]->OwnerData.armies = 3;
	}
}

BattleResult Game::attackTerritory(int attacker, int defender) {
	if (tTree.isNeighbor(attacker,defender) && territories[attacker]->OwnerData.owner!=territories[defender]->OwnerData.owner) {
		int atkAmount = (territories[attacker]->OwnerData.armies>4)?(3):(territories[attacker]->OwnerData.armies-1);
		int defAmount = (territories[defender]->OwnerData.armies>2)?(2):(territories[defender]->OwnerData.armies);
		int atkDice[atkAmount], defDice[defAmount];
		for (int i = 0; i<atkAmount; ++i)
			atkDice[i] = getRandom(1,7); //[1,6]
		for (int i = 0; i<defAmount; ++i)
			defDice[i] = getRandom(1,7); //[1,6]
        sort(atkDice,atkDice+atkAmount);
        sort(defDice,defDice+defAmount);
        int c = min(atkAmount,defAmount);
        int aLoss = 0, dLoss = 0;
        for (int i = 0; i<c; ++i) {
			if (atkDice[i]>defDice[i])
				aLoss++;
			else
				dLoss++;
        }
        territories[attacker]->OwnerData.armies -= aLoss;
        territories[defender]->OwnerData.armies -= dLoss;
        if (territories[defender]->OwnerData.armies==0) {
			int a = 0;
			for (unsigned int i = 0; i<players.size(); ++i) {
				if (players[i].faction==territories[attacker]->OwnerData.owner) {
					a = players[i].armiesToMove(1,territories[attacker]->OwnerData.armies-1);
					if (a==-1)
						return BattleResult::GameClosed;
					break;
				}
			}
            territories[attacker]->OwnerData.armies -= a;
            territories[defender]->OwnerData.armies = a;
            territories[defender]->OwnerData.owner = territories[attacker]->OwnerData.owner;
            return BattleResult::DefenderCaptured;
        }
		return BattleResult::Stalemate;
	}
	return BattleResult::InvalidAttack;
}

bool Game::moveArmies(int start, int dest, int amount) {
	if (tTree.pathExists(start,dest)) { //this also ensures that both territories are the same faction
		if (territories[start]->OwnerData.armies-amount>=1) {
			territories[start]->OwnerData.armies -= amount;
			territories[dest]->OwnerData.armies += amount;
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

bool Game::placeArmies(Faction f, int territory, int amount) {
	if (territories[territory]->OwnerData.owner==f) {
		territories[territory]->OwnerData.armies += amount;
		return true;
	}
	return false;
}
