#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!",Style::Default);
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
    bool beeActive = false;
    float beeSpeed = 0.0f;
    Texture textureCloud;
    textureCloud.loadFromFile("../Resources/graphics/cloud.png");
    Sprite spriteClouds[3];
    spriteClouds[0].setTexture(textureCloud);
    spriteClouds[1].setTexture(textureCloud);
    spriteClouds[2].setTexture(textureCloud);
    spriteClouds[0].setPosition(0, 0);
    spriteClouds[1].setPosition(0, 250);
    spriteClouds[2].setPosition(0, 500);
    bool cloudActive[3];
    cloudActive[0] = false; cloudActive[1] = false; cloudActive[2] = false;
    float cloudSpeed[3];
    cloudSpeed[0] = 0.0f;cloudSpeed[1] = 0.0f;cloudSpeed[2] = 0.0f;
    Clock clock;
    while (window.isOpen())
       {
           Time dt = clock.restart();
           if(!beeActive){
               srand((int)time(0));
               beeSpeed = (rand()%200)+200;
               
               srand((int) time(0)*10);
               float height = (rand()%500)+500;
               spriteBee.setPosition(2000, height);
               beeActive = true;
           }else{
               spriteBee.setPosition(
                                     spriteBee.getPosition().x-(beeSpeed*dt.asSeconds()),
                                     spriteBee.getPosition().y);
               
               if(spriteBee.getPosition().x<-100){
                   beeActive = false;
               }
           }
           for(int i = 0; i<3;i++){
               if(!cloudActive[i]){
                   srand((int)time(0)*10);
                   cloudSpeed[i] = (rand()%200+5+(i*50));
                   
                   srand((int) time(0)*10);
                   float height = (rand()%150+(i*180));
                   spriteClouds[i].setPosition(-(i*400), height);
                   cloudActive[i] = true;
               }else{
                   spriteClouds[i].setPosition(
                                               spriteClouds[i].getPosition().x+(cloudSpeed[i]*dt.asSeconds()),
                                               spriteClouds[i].getPosition().y);
                   
                   if(spriteClouds[i].getPosition().x>window.getSize().x){
                       cloudActive[i] = false;
                   }
               }
           }
           /*
            ****************************************
            Handle the players input
            ****************************************
            */
           
          //Fixes SFML Not opening error.
           Event event;
           while (window.pollEvent(event)) {
               if (event.type == Event::Closed) {
                       window.close();
               }
           }
           
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
               window.close();

         

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
           window.draw(spriteClouds[0]);
           window.draw(spriteClouds[1]);
           window.draw(spriteClouds[2]);
           window.draw(spriteTree);
           window.draw(spriteBee);

           // Show everything we just drew
           window.display();
       }
       return 0;
}
