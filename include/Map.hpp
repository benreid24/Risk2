#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "Territory.hpp"

/**
 * View class for rendering the map and all of the armies on it
 */
class Map {
	sf::RenderTexture target;
	sf::Sprite rendSpr;
	sf::Texture mapTxtr;
	sf::Sprite mapImg;
	sf::CircleShape armyCircle;
	sf::Text armyText;
	sf::Color colorMap[6];

public:
	/**
	 * Primary constructor. Initializes internal data and loads map image
	 *
	 * \param img The file of the map image to load
	 * \param font A reference to a Font object to use
	 */
    Map(std::string img, sf::Font& font);

    /**
     * Renders the map and territory data to the given window
     *
     * \param window The window to render to
     * \param territories The territory data to use while rendering
     * \param area The region of the window to render to. Everything will be scaled to fit
     */
    void render(sf::RenderWindow& window, std::vector<Territory>& territories, sf::IntRect area);
};

#endif // MAP_HPP
