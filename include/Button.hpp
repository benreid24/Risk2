#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * Simple button class to render buttons and tell if they're clicked
 */
class Button {
	sf::Texture txtr;
	sf::Sprite spr;
	sf::Image clickMap;

public:
	/**
	 * Loads the image file and positions the button
	 *
	 * \param imgFile The image to use for the button
	 * \param pos The position of the button
	 */
	Button(std::string imgFile, sf::Vector2f pos);

    /**
     * Tells whether or not the button is clicked
     *
     * \param window A reference to the window that the button is in
     * \return True if the button is current clicked, false otherwise
     */
	bool isClicked(sf::RenderWindow& window);

	/**
	 * Draws the button to the given window
	 *
	 * \param window A reference to the window to render to
	 */
	void draw(sf::RenderWindow& window);
};

#endif // BUTTON_HPP
