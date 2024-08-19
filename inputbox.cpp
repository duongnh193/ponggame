#include "inputbox.h"

InputBox::InputBox(float width, float height) {
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::Magenta);
    box.setPosition(150,200);

    if (!font.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/font/november.ttf")) {
        // Handle error
    }

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(box.getPosition().x + 10, box.getPosition().y + 10);


    // isSelected = false;
}

void InputBox::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            char typedChar = static_cast<char>(event.text.unicode);
            if (typedChar == '\b') { // Backspace
                if (!input.empty()) {
                    input.pop_back();
                }
            } else {
                input += typedChar;
            }
            text.setString(input);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Delete) {
            input.clear();
            text.setString(input);
        }
    }
}

void InputBox::render(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}

void InputBox::clearInput()
{
    input.clear();
    text.setString(input);
}

std::string InputBox::getInput() const {
    return input;
}
