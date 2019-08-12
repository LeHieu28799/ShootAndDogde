#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <list>
#include <string>

using namespace std;

void fly (float& xShip , float& yShip,
          float& window_width, float& window_height,
          float& width_ship, float& height_ship,
          float& dx, float& dy,
          sf::Sprite& ship,
          sf::RenderWindow& window) {
            // left key is pressed: move our character
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if ( xShip > 0 ) {
                    xShip = xShip - dx;
                    if (xShip <= 0) { xShip = 0;}
                }
                ship.setPosition(sf::Vector2f(xShip,yShip));
                window.draw(ship);
            }

            // Right key is pressed: move our character
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if ( xShip < (window_width - width_ship)) {
                    xShip = xShip + dx;
                    if (xShip >= ((window_width - width_ship))) { xShip = (window_width - width_ship);}
                }
                ship.setPosition(sf::Vector2f(xShip,yShip));
                window.draw(ship);
            }

            // Down key is pressed: move our character
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if ( yShip < (window_height - height_ship)) {
                    yShip = yShip + dy;
                    if ( yShip >= (window_height - height_ship)) { yShip = window_height - height_ship;}
                }
                ship.setPosition(sf::Vector2f(xShip,yShip));
                window.draw(ship);
            }

            // Up is pressed: move our character
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if ( yShip > 0 ) {
                    yShip = yShip - dy;
                    if (yShip <= 0) { yShip = 0;}
                }
                ship.setPosition(sf::Vector2f(xShip,yShip));
                window.draw(ship);
            }
}

void Fire(float& xShip, float& yShip,
          float& xBullet, float& yBullet,
          sf::Sprite& bullet,
          sf::RenderWindow& window) {
            //Fire
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                bullet.setPosition(sf::Vector2f(xShip + 27 ,yShip - 40));
                xBullet = xShip + 27;
                yBullet = yShip - 40;
                window.draw(bullet);

            }
}
void flying_bullet( float& xBullet, float& yBullet,
                    sf::Sprite& bullet,
                    sf::RenderWindow& window) {
            yBullet-= 0.4;
            bullet.setPosition(sf::Vector2f(xBullet,yBullet));
            window.draw(bullet);
}

void bullet_collide_creep( float& xBullet , float& yBullet,
                           float& xCreep, float& yCreep,
                           float& xCreep1, float& yCreep1,
                           sf::Sprite& bullet,
                           sf::Sprite& creep,
                           sf::Sprite& creep1,
                           sf::RenderWindow& window,
                           int& score) {
    if (xBullet <= xCreep +30 && yBullet <= yCreep+40 && xBullet >= xCreep-42 && yBullet >= yCreep-44) {
        xCreep = rand()%800;
        if (xCreep <=20) xCreep+=10;
        if (xCreep >=765) xCreep = 755;
        yCreep = 0;
        creep.setPosition(sf::Vector2f(xCreep,yCreep));
        window.draw(creep);
        score += 10;
        cout<<"score: "<<score<<endl;
    }
    if (xBullet <= xCreep1+30 && yBullet <= yCreep1+40 && xBullet >= xCreep1-42 && yBullet >= yCreep1-44)  {
        xCreep1 = rand()%800;
        if (xCreep1 <=20) xCreep1+=10;
        if (xCreep1 >=765) xCreep1 = 755;
        yCreep1 = 0;
        creep1.setPosition(sf::Vector2f(xCreep1,yCreep1));
        window.draw(creep1);
        score += 10;
        cout<<"score: "<<score<<endl;
    }
}

void bullet_collide_boss(  float& xShip, float& yShip,
                           float& xBullet , float& yBullet,
                           float& xBoss, float& yBoss,
                           float& xBoss1, float& yBoss1,
                           sf::Sprite& bullet,
                           sf::Sprite& boss,
                           sf::Sprite& boss1,
                           sf::RenderWindow& window,
                           int& score) {
    if (xBullet <= xBoss+60 && yBullet <= yBoss+85 && xBullet >= xBoss-45 && yBullet >= yBoss-45) {
        xBoss = rand() % 800;
        if (xBoss <=45) xBoss+=20;
        if (xBoss >=755) xBoss = 755;
        yBoss = 0;
        boss.setPosition(xBoss,yBoss);
        window.draw(boss);
        bullet.setPosition(xShip,yShip);
        window.draw(bullet);
        score-=3;
        cout<<"score: "<<score<<endl;
    }
    if ((xBullet <= xBoss1+60 && yBullet <= yBoss1+85 && xBullet >= xBoss1-45 && yBullet >= yBoss1-45)) {
        xBoss1 = rand() % 800;
        if (xBoss1 <=45) xBoss1+=20;
        if (xBoss1 >=755) xBoss1 = 755;
        yBoss1 = 0;
        boss.setPosition(xBoss1,yBoss1);
        window.draw(boss1);
        bullet.setPosition(xShip,yShip);
        window.draw(bullet);
        score-=3;
        cout<<"score: "<<score<<endl;
    }
}
// check if ship collide creep or boss
bool Collide(float& xShip , float& yShip,
             float& xCreep, float& yCreep,
             float& xBoss , float& yBoss,
             float& xCreep1, float& yCreep1,
             float& xBoss1, float& yBoss1) {
    if ( (xShip <= xCreep+30 && yShip <= yCreep+40 && xShip >= xCreep-42 && yShip >= yCreep-44)||
         (xShip <= xBoss+60 && yShip <= yBoss+85 && xShip >= xBoss-45 && yShip >= yBoss-45) ||
         (xShip <= xCreep1+30 && yShip <= yCreep1+40 && xShip >= xCreep1-42 && yShip >= yCreep1-44) ||
         (xShip <= xBoss1+60 && yShip <= yBoss1+85 && xShip >= xBoss1-45 && yShip >= yBoss1-45) ) {
        return true;
    }
    return false;
}
//crashing ship ưhen collide
void Crash( float& xShip, float& yShip,
            sf::RenderWindow& window) {
        //Explosion
        sf::Texture texture_explosion12;
        if (!texture_explosion12.loadFromFile("explosion12.png")) cout<<"Wrong.... Can't Find The Image...."<<endl;
        sf::Sprite explosion12;
        explosion12.setTexture(texture_explosion12);
        explosion12.setPosition(sf::Vector2f(xShip,yShip));
        window.draw(explosion12);
}
// Text: Mission failed
void Failed (sf::RenderWindow& window) {
        //Mission Failed (TEXT)
        sf::Text text;
        sf::Font font;
        text.setFont(font);
        if (!font.loadFromFile("Azonix.otf")) cout<<"Wrong.... Can't Find It...."<<endl;
        text.setString("Mission Failed");
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Yellow);
        text.setStyle(sf::Text::Bold | sf::Text::Italic);
        window.draw(text);
}

void Score (int& score,
            sf::Text& text1,
            sf::RenderWindow& window) {
    text1.setString("Score: " + std::to_string(score));
    window.draw(text1);
}

void falling (float& xCreep, float& yCreep,
              float& xBoss, float& yBoss,
              float& xCreep1, float& yCreep1,
              float& xBoss1, float& yBoss1,
              float dy_Creep, float dy_Boss,
              float dy_Creep1, float dy_Boss1,
              sf::Sprite& creep,
              sf::Sprite& boss,
              sf::Sprite& creep1,
              sf::Sprite& boss1,
              sf::RenderWindow& window) {

            yCreep+= dy_Creep;
            creep.setPosition(sf::Vector2f(xCreep,yCreep));
            window.draw(creep);

            yBoss+=dy_Boss;
            boss.setPosition(sf::Vector2f(xBoss,yBoss));
            window.draw(boss);

            yCreep1+= dy_Creep1;
            creep.setPosition(sf::Vector2f(xCreep1,yCreep1));
            window.draw(creep1);

            yBoss1+=dy_Boss1;
            boss1.setPosition(sf::Vector2f(xBoss1,yBoss1));
            window.draw(boss1);

}

int main() {

    srand(time(0));

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shoot And Dogde ---- SAD");
    // original position of the ship, size of the ship and window, distance changes
    static float xShip = 350, yShip = 500, width_ship = 80, height_ship = 59;

    static float window_width = 800, window_height = 600;

    static float dx = 0.3, dy = 0.3,
                 dy_Creep =0.12, dy_Boss = 0.16,
                 dy_Creep1 =0.14, dy_Boss1 = 0.2;

    static float xCreep  = rand()%800, yCreep = 0,
                 xCreep1 = rand()%800+17, yCreep1 = 0,
                 xBoss   = rand()%800, yBoss = 0,
                 xBoss1  = rand()%800+15, yBoss1 = 0,
                 xBullet = 0, yBullet = 0;
    static int score = 0, turn =0, save =0;
    //score
    sf::Text text1;
    sf::Font font1;
    text1.setFont(font1);
    if (!font1.loadFromFile("Azonix.otf")) cout<<"Wrong.... Can't Find It...."<<endl;
    text1.setCharacterSize(30);
    text1.setFillColor(sf::Color::Red);
    text1.setStyle(sf::Text::Regular| sf::Text::Underlined);
    text1.setPosition(sf::Vector2f(550,10));

    // create the ship
    sf::Texture texture_ship;
    if (!texture_ship.loadFromFile("Ship.jpg")) {
      cout<<"Wrong.... Can't Find The Image...."<<endl;
    }
    texture_ship.setSmooth(true);
    sf::Sprite ship;
    ship.setTexture(texture_ship);


    // create creeps
    sf::Texture texture_creep;
    if (!texture_creep.loadFromFile("alien.png")) {
        cout<<"Can't find anything about creep........"<<endl;
    }
    texture_creep.setSmooth(true);
    sf::Sprite creep;
    creep.setTexture(texture_creep);

    sf::Texture texture_creep1;
    if (!texture_creep1.loadFromFile("alien.png")) {
        cout<<"Can't find anything about creep........"<<endl;
    }
    texture_creep1.setSmooth(true);
    sf::Sprite creep1;
    creep1.setTexture(texture_creep1);

    //create boss
    sf::Texture texture_boss;
    if (!texture_boss.loadFromFile("Boss.png")) {
        cout<<"Can't find anything about Boss........"<<endl;
    }
    texture_boss.setSmooth(true);
    sf::Sprite boss;
    boss.setTexture(texture_boss);

     sf::Texture texture_boss1;
    if (!texture_boss1.loadFromFile("Boss.png")) {
        cout<<"Can't find anything about Boss........"<<endl;
    }
    texture_boss1.setSmooth(true);
    sf::Sprite boss1;
    boss1.setTexture(texture_boss);

    //Bullet
    sf::Texture texture_bullet;
    if (!texture_bullet.loadFromFile("bullet.png")) {
        cout<<"No Bullet!!!!!";
    }
    sf::Sprite bullet;
    bullet.setTexture(texture_bullet);
    // run the program as long as the window is open


    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        //ship's position
        ship.setPosition(sf::Vector2f(xShip,yShip));
        window.draw(ship);
        fly(xShip,yShip, window_width,window_height, width_ship, height_ship, dx, dy ,ship,window);
        // when ship ! collide bullet keep going on flying
        if (!Collide(xShip,yShip,xCreep,yCreep,xBoss,yBoss,xCreep1,yCreep1,xBoss1,yBoss1)) {
            Fire(xShip,yShip,xBullet,yBullet,bullet,window);
        }

        //what bullet can do
        if (yBullet<0) {
            bullet.setPosition(xShip,yShip);
            window.draw(bullet);
        }
        flying_bullet(xBullet,yBullet,bullet,window);
        bullet_collide_creep(xBullet, yBullet, xCreep, yCreep, xCreep1, yCreep1, bullet, creep, creep1, window, score);
        bullet_collide_boss(xShip, yShip, xBullet, yBullet, xBoss, yBoss, xBoss1, yBoss1, bullet, boss, boss1, window, score);

        // ship collide others
        if (Collide(xShip,yShip,xCreep,yCreep,xBoss,yBoss,xCreep1,yCreep1,xBoss1,yBoss1)) {
            Crash(xShip, yShip, window);

        }

        //creep and boss return after out the screen

        if (turn% 8 ==0 and turn/8 != save) {
            dy_Boss += 0.023;
            dy_Boss1 += 0.023;
            dy_Creep += 0.053;
            dy_Creep1 += 0.053;
            save = turn/8;
        }
        if ((yCreep < 600 || yBoss <600 ||  yCreep1<600 || yBoss1<600) && !Collide(xShip,yShip,xCreep,yCreep,xBoss,yBoss,xCreep1,yCreep1,xBoss1,yBoss1)) {
            falling(xCreep, yCreep, xBoss, yBoss, xCreep1, yCreep1, xBoss1, yBoss1, dy_Creep, dy_Boss, dy_Creep1, dy_Boss1, creep, boss, creep1, boss1, window);
            if (yCreep >= 600) {
                xCreep = rand()%800;
                if (xCreep <=20) xCreep+=10;
                if (xCreep >=765) xCreep = 755;
                yCreep=0;
                turn ++;
            }
            if (yBoss >= 600) {
                xBoss = rand() % 800;
                if (xBoss <=45) xBoss+=20;
                if (xBoss >=755) xBoss = 755;
                yBoss = 0;
                turn++;
            }
            if (yCreep1 >= 600) {
                xCreep1 = rand()%800;
                if (xCreep1 <=20) xCreep1+=10;
                if (xCreep1 >=765) xCreep1 = 755;
                yCreep1=0;
                turn++;
            }
            if (yBoss1 >= 600) {
                xBoss1 = rand() % 800;
                if (xBoss1 <=45) xBoss1+=20;
                if (xBoss1 >=755) xBoss1 = 755;
                yBoss1 = 0;
                turn++;
            }
        }

        //score
        Score(score,text1,window);

        //Creep
        creep.setPosition(sf::Vector2f(xCreep,yCreep));
        window.draw(creep);
        creep1.setPosition(sf::Vector2f(xCreep1,yCreep1));
        window.draw(creep1);

        //boss
        boss.setPosition(sf::Vector2f(xBoss,yBoss));
        window.draw(boss);
        boss1.setPosition(sf::Vector2f(xBoss1,yBoss1));
        window.draw(boss1);

        //Show text: Mission failed without being covered by others
        if (Collide(xShip,yShip,xCreep,yCreep,xBoss,yBoss,xCreep1,yCreep1,xBoss1,yBoss1)) {
            Failed(window);
            Score(score,text1,window);
        }

        // end the current frame
        window.display();
    }
    return 0;
}
