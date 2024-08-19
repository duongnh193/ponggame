#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SFML/Graphics.hpp>
#include <sstream>

    class InputBox {
public:
    InputBox(float width, float height);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void clearInput();
    std::string getInput() const;
    sf::RectangleShape box;

private:

    sf::Text text;
    sf::Font font;
    std::string input;
    bool isSelected;
};

#endif
