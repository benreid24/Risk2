#include "Map.hpp"
#include "Util.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Map::Map(string img, Font& f) : armyCircle(13) {
	mapTxtr.loadFromFile(img);
	mapImg.setTexture(mapTxtr);
	armyText.setColor(Color::Black);
	armyText.setFont(f);
	armyText.setCharacterSize(15);
	target.create(mapTxtr.getSize().x,mapTxtr.getSize().y);
	rendSpr.setTexture(target.getTexture());
}

void Map::render(RenderWindow& window, vector<Territory*>& territories, IntRect area) {
	Vector2f pos;
	target.draw(mapImg);
	for (unsigned int i = 0; i<territories.size(); ++i) {
		pos = Vector2f(territories[i]->GameData.x,territories[i]->GameData.y);
		armyCircle.setPosition(pos);
		armyCircle.setFillColor(colorMap[territories[i]->OwnerData.owner]);
		target.draw(armyCircle);
		armyText.setString(intToString(territories[i]->OwnerData.armies));
		armyText.setPosition(pos.x+13,pos.y+12);
		armyText.setOrigin(armyText.getGlobalBounds().width/2,armyText.getGlobalBounds().height);
		target.draw(armyText);
	}
	rendSpr.setScale(area.width/float(target.getSize().x),-area.height/float(target.getSize().y));
	rendSpr.setPosition(area.left,area.top+area.height);
	window.draw(rendSpr);
}

int Map::getClosetTerritory(vector<Territory*>& territories, float x, float y) {
	int cId = -1, cDist = 10000000;
	int xLoc = x*mapTxtr.getSize().x;
	int yLoc = y*mapTxtr.getSize().y;

	for (unsigned int i = 0; i<territories.size(); ++i) {
		int tx = territories[i]->GameData.x;
		int ty = territories[i]->GameData.y;
		int t = (xLoc-tx)*(xLoc-tx)+(yLoc-ty)*(yLoc-ty);
		if (t<cDist) {
			cDist = t;
			cId = territories[i]->GameData.id;
		}
	}

	return (cDist<1600)?(cId):(-1);
}
