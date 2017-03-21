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
    void render(sf::RenderWindow& window, std::vector<Territory*>& territories, sf::IntRect area);

    /**
     * Returns the closet territory to the given position
     *
     * \param territories A reference to a vector containing all of the territories
     * \param x A normalized x coordinate in the range [0,1] of the position on the map to check
     * \param y A normalized y coordinate in the range [0,1] of the position on the map to check
     * \return The id of the closest territory, or -1 if no territory is within 40 units
     */
	int getClosetTerritory(std::vector<Territory*>& territories, float x, float y);
};

#endif // MAP_HPP
