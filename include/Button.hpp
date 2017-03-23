#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * Simple button class to render buttons and tell if they're clicked
 */
class Button {
	sf::RenderWindow& target;
	sf::Texture txtr;
	sf::Sprite spr;
	sf::Image clickMap;
	bool hidden;

public:
	/**
	 * Loads the image file and positions the button
	 *
	 * \param window The window that the button should be in
	 * \param imgFile The image to use for the button
	 * \param pos The position of the button
	 */
	Button(sf::RenderWindow& window, std::string imgFile, sf::Vector2f pos);

	/**
	 * Sets whether or not the button is hidden
	 *
	 * \param hide Pass true to hide the button, false otherwise
	 */
	void setHidden(bool hide);

	/**
	 * Returns the position of the button
	 *
	 * \return A Vector2f containing the position
	 */
	sf::Vector2f getPosition();

    /**
     * Tells whether or not the button is clicked
     * \return True if the button is current clicked, false otherwise
     */
	bool isClicked();

	/**
	 * Draws the button to the window
	 */
	void draw();
};

#endif // BUTTON_HPP
