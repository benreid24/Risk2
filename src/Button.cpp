#include "Button.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Button::Button(string imgFile, Vector2f pos) {
	clickMap.loadFromFile(imgFile);
	txtr.loadFromFile(imgFile);
	spr.setTexture(txtr);
	spr.setPosition(pos);
	hidden = false;
}

bool Button::isClicked(RenderWindow& window) {
	Vector2f pos = Vector2f(Mouse::getPosition(window));
	pos = window.mapPixelToCoords(Vector2i(pos));
	pos -= spr.getPosition();
	if (pos.x<0 || pos.y<0 || pos.x>=clickMap.getSize().x || pos.y>=clickMap.getSize().y)
		return false;
	return (clickMap.getPixel(pos.x,pos.y)!=Color::Transparent && Mouse::isButtonPressed(Mouse::Left));
}

void Button::draw(RenderWindow& window) {
	if (!hidden)
		window.draw(spr);
}

void Button::setHidden(bool hide) {
	hidden = hide;
}

Vector2f Button::getPosition() {
	return spr.getPosition();
}
