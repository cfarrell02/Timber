#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!",Style::Default);
    Texture textureBackground;
    textureBackground.loadFromFile("../Resources/graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
    Texture textureTree;
    textureTree.loadFromFile("../Resources/graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810,0);
    Texture textureBee;
    textureBee.loadFromFile("../Resources/graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    while (window.isOpen())
       {
           /*
            ****************************************
            Handle the players input
            ****************************************
            */
           
          
           Event event;
           while (window.pollEvent(event)) {
               if (event.type == Event::Closed) {
                       window.close();
               }
           }
           
//           if (Keyboard::isKeyPressed(Keyboard::Escape))
//           {
//               window.close();
//           }

         

           /*
            ****************************************
            Update the scene
            ****************************************
            */
           
           
           /*
            ****************************************
            Draw the scene
            ****************************************
            */
           
           // Clear everything from the last frame
           window.clear();
           
           // Draw our game scene here
           window.draw(spriteBackground);
           window.draw(spriteTree);
           window.draw(spriteBee);
           // Show everything we just drew
           window.display();
       }
       return 0;
}
