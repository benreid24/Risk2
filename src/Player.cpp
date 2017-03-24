#include "Player.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Util.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

Texture Player::promptTxtr;
Sprite Player::prompt;
Text Player::armyText;
Button *Player::upArrow, *Player::downArrow, *Player::done;

Player::Player(Game* g, std::string nm, Faction color) {
	game = g;
	name = nm;
	faction = color;
}

int Player::armiesToMove(int mn, int mx) {
	int am = mn;
	armyText.setString(intToString(am));

	while (game->handleWindowEvents()) {
        if (upArrow->isClicked() && am<mx) {
			am++;
			armyText.setString(intToString(am));
			sleep(milliseconds(120));
        }
        else if (downArrow->isClicked() && am>mn) {
			am--;
			armyText.setString(intToString(am));
			sleep(milliseconds(120));
        }
        else if (done->isClicked())
			return am;

		game->render();
		game->draw(prompt);
		upArrow->draw();
		downArrow->draw();
		done->draw();
		game->draw(armyText);
		game->display();
		sleep(milliseconds(30));
	}

	return -1;
}

bool Player::assignArmies(int amount) {
	while (game->handleWindowEvents()) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			int id = game->getClosestTerritory();
			if (id!=-1) {
				if (game->placeArmies(faction,id,1)) {
					amount--;
					if (amount<=0)
						return false;
				}
			}
		}

		game->render();
		game->display();
		sleep(milliseconds(30));
	}

	return true;
}

bool Player::takeTurn(Map* rMap, map<string,Button*>& buttons, TerritoryTree& tTree) {
	int selectedTerritory = -1;
	int targetTerritory = -1;

	int fWait = 0;
	buttons["DoneAttack"]->setHidden(false);
	while (game->handleWindowEvents()) {
		if (buttons["LaborSlave"]->isClicked() && selectedTerritory!=-1) {
			if (tTree.getTerritory(selectedTerritory)->OwnerData.owner==faction) {
				tTree.getTerritory(selectedTerritory)->OwnerData.labor = LaborType::Slave;
				game->selectTerritory(selectedTerritory);
			}
		}
		else if (buttons["LaborFree"]->isClicked() && selectedTerritory!=-1) {
			if (tTree.getTerritory(selectedTerritory)->OwnerData.owner==faction) {
				tTree.getTerritory(selectedTerritory)->OwnerData.labor = LaborType::Paid;
				game->selectTerritory(selectedTerritory);
			}
		}
		else if (buttons["Attack"]->isClicked() && selectedTerritory!=-1 && targetTerritory!=-1) {
			cout << "Attacking " << tTree.getTerritory(targetTerritory)->GameData.name << " from " << tTree.getTerritory(selectedTerritory)->GameData.name << endl;
			BattleResult r = game->attackTerritory(selectedTerritory,targetTerritory);
			if (r==BattleResult::GameClosed)
				return true;
			else if (r==BattleResult::DefenderCaptured) {
				game->selectTerritory(targetTerritory);
				game->selectTerritory(-1,true);
				rMap->deselectTerritory(targetTerritory);
				rMap->deselectTerritory(selectedTerritory);
				selectedTerritory = targetTerritory;
				targetTerritory = -1;
				Color m = colorMap[tTree.getTerritory(selectedTerritory)->OwnerData.owner];
				m = Color(255-m.r,255-m.g,255-m.b);
				rMap->selectTerritory(selectedTerritory,m);
				buttons["Attack"]->setHidden(true);
			}
			sleep(milliseconds(250));
		}
		else if (buttons["DoneAttack"]->isClicked()) {
			if (selectedTerritory!=-1) {
				game->selectTerritory(-1);
				rMap->deselectTerritory(selectedTerritory);
			}
			if (targetTerritory!=-1) {
				rMap->deselectTerritory(targetTerritory);
				game->selectTerritory(-1,true);
			}
			buttons["DoneAttack"]->setHidden(true);
			return false;
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && fWait==0) {
			int id = game->getClosestTerritory();
			if (id!=-1) {
				fWait = 10;
				Color m = colorMap[tTree.getTerritory(id)->OwnerData.owner];
				Color s(abs(128-m.r),abs(128-m.g),abs(128-m.b));
				m = Color(255-m.r,255-m.g,255-m.b);
				if (selectedTerritory==-1 || !tTree.isNeighbor(selectedTerritory,id) || id==targetTerritory || (targetTerritory!=-1 && !tTree.isNeighbor(selectedTerritory,id)) || tTree.getTerritory(id)->OwnerData.owner==faction) {
					if (selectedTerritory!=-1)
						rMap->deselectTerritory(selectedTerritory);
					selectedTerritory = id;
					if (targetTerritory!=-1) {
						rMap->deselectTerritory(targetTerritory);
						game->selectTerritory(-1,true);
					}
					targetTerritory = -1;
					game->selectTerritory(id);
					rMap->selectTerritory(id,m);
				}
				else if (tTree.isNeighbor(selectedTerritory,id) && tTree.getTerritory(selectedTerritory)->OwnerData.owner==faction && tTree.getTerritory(id)->OwnerData.owner!=faction) {
                    if (targetTerritory!=-1) {
						rMap->deselectTerritory(targetTerritory);
						game->selectTerritory(-1,true);
					}
                    targetTerritory = id;
                    game->selectTerritory(id,true);
                    rMap->selectTerritory(id,s);
				}
			}
            else {
                if (selectedTerritory!=-1)
					rMap->deselectTerritory(selectedTerritory);
				if (targetTerritory!=-1)
					rMap->deselectTerritory(targetTerritory);
				game->selectTerritory(-1);
				game->selectTerritory(-1,true);
				selectedTerritory = targetTerritory = -1;
            }
		}

		if (fWait>0)
			fWait--;
		if (selectedTerritory!=-1 && targetTerritory!=-1)
			buttons["Attack"]->setHidden(false);
		else
			buttons["Attack"]->setHidden(true);

		game->render();
		game->display();
		sleep(milliseconds(30));
	}

	return true;
}

bool Player::reinforce(Map* rMap, map<string,Button*>& buttons, TerritoryTree& tTree) {
	int selectedTerritory = -1;
	int targetTerritory = -1;

	int fWait = 0;
	buttons["DoneTransfer"]->setHidden(false);
	while (game->handleWindowEvents()) {
		if (buttons["Transfer"]->isClicked() && selectedTerritory!=-1 && targetTerritory!=-1) {
			//transfer
			cout << "Transfer\n";
			int t = armiesToMove(1,tTree.getTerritory(selectedTerritory)->OwnerData.armies-1);
			if (game->moveArmies(selectedTerritory,targetTerritory,t)) {
				if (selectedTerritory!=-1) {
					game->selectTerritory(-1);
					rMap->deselectTerritory(selectedTerritory);
				}
				if (targetTerritory!=-1) {
					rMap->deselectTerritory(targetTerritory);
					game->selectTerritory(-1,true);
				}
				buttons["DoneTransfer"]->setHidden(true);
				buttons["Transfer"]->setHidden(true);
				return false;
			}
		}
		else if (buttons["DoneTransfer"]->isClicked()) {
			if (selectedTerritory!=-1) {
				game->selectTerritory(-1);
				rMap->deselectTerritory(selectedTerritory);
			}
			if (targetTerritory!=-1) {
				rMap->deselectTerritory(targetTerritory);
				game->selectTerritory(-1,true);
			}
			buttons["DoneTransfer"]->setHidden(true);
			buttons["Transfer"]->setHidden(true);
			return false;
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && fWait==0) {
			int id = game->getClosestTerritory();
			if (id!=-1) {
				fWait = 10;
				Color m = colorMap[tTree.getTerritory(id)->OwnerData.owner];
				Color s(abs(128-m.r),abs(128-m.g),abs(128-m.b));
				m = Color(255-m.r,255-m.g,255-m.b);
				if ((selectedTerritory==-1 || !tTree.pathExists(selectedTerritory,id)) && tTree.getTerritory(id)->OwnerData.owner==faction && tTree.getTerritory(id)->OwnerData.armies>1) {
					if (selectedTerritory!=-1)
						rMap->deselectTerritory(selectedTerritory);
					selectedTerritory = id;
					if (targetTerritory!=-1) {
						rMap->deselectTerritory(targetTerritory);
						game->selectTerritory(-1,true);
					}
					targetTerritory = -1;
					game->selectTerritory(id);
					rMap->selectTerritory(id,m);
				}
				else if (tTree.pathExists(selectedTerritory,id) && tTree.getTerritory(selectedTerritory)->OwnerData.owner==faction) {
                    if (targetTerritory!=-1) {
						rMap->deselectTerritory(targetTerritory);
						game->selectTerritory(-1,true);
					}
                    targetTerritory = id;
                    game->selectTerritory(id,true);
                    rMap->selectTerritory(id,s);
				}
			}
            else {
                if (selectedTerritory!=-1)
					rMap->deselectTerritory(selectedTerritory);
				if (targetTerritory!=-1)
					rMap->deselectTerritory(targetTerritory);
				game->selectTerritory(-1);
				game->selectTerritory(-1,true);
				selectedTerritory = targetTerritory = -1;
            }
		}

		if (fWait>0)
			fWait--;
		if (selectedTerritory!=-1 && targetTerritory!=-1)
			buttons["Transfer"]->setHidden(false);
		else
			buttons["Transfer"]->setHidden(true);

		game->render();
		game->display();
		sleep(milliseconds(30));
	}

	return true;
}
