#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    
    //Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("../Resources/graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    // The player starts on the left
    side playerSide = side::LEFT;
    
    //Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("../Resources/graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);
    
    // Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("../Resources/graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
    // Line the axe up with the tree
    const float AXE_POSITION_LEFT= 700;
    const float AXE_POSITION_RIGHT =1075;
    
    //Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("../Resources/graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    //Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    
    bool acceptInput = false;
    
    //Prepare the sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("../Resources/sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);
    
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("../Resources/sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);
    // Out of time
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("../Resources/sound/out_of_time.wav");
    Sound outofTime;
    outofTime.setBuffer(ootBuffer);
    
    while (window.isOpen())
       {
           //Fixes SFML Not opening error.
           Event event;
           while (window.pollEvent(event)) {
               if(event.type==Event::KeyReleased && !paused){
                   acceptInput = true;
                   spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
               }
               
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
           
               if (Keyboard::isKeyPressed(Keyboard::Return)){
                   paused = false;
                   score = 0;
                   timeRemaining = 6;
                   event.key.code = sf::Keyboard::Unknown;
                   for(int i =0;i<NUM_BRANCHES;++i){
                       branchPositions[i] = side::NONE;
                   }
                   spriteRIP.setPosition(675, 2000);
                   spritePlayer.setPosition(580, 720);
                   spriteAxe.setPosition(700, 830);
                   acceptInput=true;
               }
           if(acceptInput){
               if(Keyboard::isKeyPressed(sf::Keyboard::Right)){
                   playerSide = side::RIGHT;
                   
                   ++score;
                   
                   timeRemaining += (2/score)+.15;
                   
                   spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                   spritePlayer.setPosition(1200, 720);
                   
                   updateBranches(score);
                   spriteLog.setPosition(810, 720);
                   logSpeedX = -5000;
                   logActive = true;
                   acceptInput = false;
                   chop.play();
               }else if(Keyboard::isKeyPressed(sf::Keyboard::Left)){
                   playerSide = side::LEFT;
                   
                   ++score;
                   
                   timeRemaining += (2/score)+.15;
                   
                   spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                   spritePlayer.setPosition(580, 720);
                   
                   updateBranches(score);
                   spriteLog.setPosition(810, 720);
                   logSpeedX = 5000;
                   logActive = true;
                   acceptInput = false;
                   chop.play();
               }
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
                   outofTime.play();
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
               
               if(logActive){
                   spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX*dt.asSeconds()), spriteLog.getPosition().y+(logSpeedY*dt.asSeconds()));
                   
                   if(spriteLog.getPosition().x<-100||spriteLog.getPosition().x>2000){
                       logActive = false;
                       spriteLog.setPosition(810, 720);
                   }
               }
               
               if(branchPositions[5]==playerSide){
                   paused = true;
                   acceptInput = false;
                   spriteRIP.setPosition(525, 760);
                   spritePlayer.setPosition(2000, 660);
                   spriteAxe.setPosition(spriteAxe.getPosition().x, 1500);
                   spriteLog.setPosition(spriteLog.getPosition().x, 1500);
                   messageText.setString("SQUISHED");
                   FloatRect textRect = messageText.getLocalBounds();
                   messageText.setOrigin(textRect.left+ textRect.width/2.0f,
                                         textRect.top+textRect.height/2.0f);
                   
                   messageText.setPosition(window.getSize().x/2, window.getSize().y/2);
                   death.play();
                   
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
           //Draw the player
           window.draw(spritePlayer);
           //Draw the axe
           window.draw(spriteAxe);
           // Draw the flying log
           window.draw(spriteLog);
           //Draw the gravestone
           window.draw(spriteRIP);
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
