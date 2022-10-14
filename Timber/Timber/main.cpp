#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
using namespace sf;
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side{LEFT,RIGHT,NONE};
side branchPositions[NUM_BRANCHES];
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
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((window.getSize().x / 2) - timeBarStartWidth / 2, window.getSize().y*.9);
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond=timeBarStartWidth/timeRemaining;
    bool paused = false;
    Font font;
    font.loadFromFile("../Resources/fonts/KOMIKAP_.ttf");
    int score = 0;
    Text messageText, scoreText;
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score=0");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
    textRect.top + textRect.height / 2.0f);
    messageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    scoreText.setPosition(20,20);
    Texture textureBranch;
    textureBranch.loadFromFile("../Resources/graphics/branch.png");
    
    for(int i =0;i<NUM_BRANCHES;++i){
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }
    for(int i = 1;i<=5;++i) updateBranches(i);
    
    while (window.isOpen())
       {
           //Fixes SFML Not opening error.
           Event event;
           while (window.pollEvent(event)) {
               if (event.type == Event::Closed) {
                       window.close();
               }
           }
   
               /*
                ****************************************
                Handle the players input
                ****************************************
                */
               if (event.key.code == sf::Keyboard::Escape)
                   window.close();
           
               if (event.key.code == sf::Keyboard::Return && paused){
                   paused = false;
                   score = 0;
                   timeRemaining = 6;
                   event.key.code = sf::Keyboard::Unknown;
               }
               
               
           if(!paused){
               /*
                ****************************************
                Update the scene
                ****************************************
                */
               Time dt = clock.restart();
               
               timeRemaining -= dt.asSeconds();
               timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining,timeBarHeight));
               
               if (timeRemaining <= 0.0f) {
                   // Pause the game
                   paused = true;
               // Change the message shown to the player
                   messageText.setString("Out of time!!");
               //Reposition the text based on its new size
               FloatRect textRect = messageText.getLocalBounds();
                   messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect. height / 2.0f);
                   messageText.setPosition(1920/2.0f,1080/2.0f);}
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
                       float height = (rand()%100+(i*180));
                       spriteClouds[i].setPosition(-((i+1)*400), height);
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
               std::stringstream ss;
               ss << "Score = " << score;
               scoreText.setString(ss.str());
               
               for(int i = 0;i<NUM_BRANCHES;++i){
                   float height = i*150;
                   if(branchPositions[i]==side::LEFT){
                       branches[i].setPosition(600, height);
                       branches[i].setRotation(180);
                   }else if(branchPositions[i]==side::RIGHT){
                       branches[i].setPosition(1330, height);
                       branches[i].setRotation(0);
                   }else{
                       branches[i].setPosition(3000, height);
                   }
               }
           }
           
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
           for(Sprite branch:branches) window.draw(branch);
           window.draw(spriteTree);
           window.draw(spriteBee);
           window.draw(timeBar);
           window.draw(scoreText);
           if(paused) window.draw(messageText);

           // Show everything we just drew
           window.display();
       }
       return 0;
}

void updateBranches(int seed){
    for(int i = NUM_BRANCHES-1;i>0;i--){
        branchPositions[i] = branchPositions[i-1];
    }
    srand((int)time(0)+seed);
    int r = (rand()%5);
    switch(r){
        case 0:
            branchPositions[0]=side::LEFT;
            break;
        case 1:
            branchPositions[0]=side::RIGHT;
            break;
        default:
            branchPositions[0]=side::NONE;
            break;
    }
}
