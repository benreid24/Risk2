#include "Map.hpp"
#include "Util.hpp"
using namespace std;
using namespace sf;

Map::Map(string img, Font& f) : armyCircle(7) {
	mapTxtr.loadFromFile(img);
	mapImg.setTexture(mapTxtr);
	armyText.setColor(Color::Black);
	armyText.setFont(f);
	target.create(mapTxtr.getSize().x,mapTxtr.getSize().y);
	rendSpr.setTexture(target.getTexture());
	colorMap[0] = Color::Red;
	colorMap[1] = Color::Green;
	colorMap[2] = Color::Blue;
	colorMap[3] = Color::Yellow;
	colorMap[4] = Color::White;
	colorMap[5] = Color(255,165,0);
}

void Map::render(RenderWindow& window, vector<Territory>& territories, IntRect area) {
	Vector2f pos;
	target.draw(mapImg);
	for (unsigned int i = 0; i<territories.size(); ++i) {
		pos = Vector2f(territories[i].GameData.x,territories[i].GameData.y);
		armyCircle.setPosition(pos);
		armyCircle.setFillColor(colorMap[territories[i].OwnerData.owner]);
		target.draw(armyCircle);
		armyText.setString(intToString(territories[i].OwnerData.armies));
		armyText.setPosition(pos.x+2,pos.y+2);
		target.draw(armyText);
	}
	rendSpr.setScale(area.width/float(target.getSize().x),area.height/float(target.getSize().y));
	rendSpr.setPosition(area.left,area.top);
	window.draw(rendSpr);
}
