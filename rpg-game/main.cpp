#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

struct point {
    int x, y;
};


int main()
{
    srand(time(0));

    sf::VideoMode VM(400, 533);
    sf::RenderWindow window(VM, "Doodle Jump");

    window.setFramerateLimit(60);

    sf::Texture t1, t2, t3; //Creating textures
    t1.loadFromFile("images/background.png"); //Loads the texture
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");

    sf::Sprite sBackground(t1), sPlat(t2), sPlayer(t3); //creates the sprite using our textures

    point plat[20]; //struct for the platform position

    for (int i = 0; i < 10; i++) {
        plat[i].x = rand() % 400; //setting the platforms initial positions
        plat[i].y = rand() % 533;
    }

    int x = 100, y = 100, h = 100;
    float dx = 0, dy = 0;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        //Horizontal Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            x+=3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x -= 3;
        }

        //Makes player bounce
        dy += 0.2;
        y += dy;
        if (y > 500) {
            dy = -10;
        }
        sPlayer.setPosition(x, y);

        //Making player bounces in the platforms
        for (int i = 0; i < 10; i++) {
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y+14) && (dy > 0)){
                dy = -10;

            }
        }

        if (y < h) {
            for (int i = 0; i < 10; i++) {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y = 0; 
                    plat[i].x = rand() % 400; //setting the new platforms positions
                }
            }
        }

        window.draw(sBackground);
        window.draw(sPlayer);

        for (int i = 0; i < 10; i++) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            window.draw(sPlat);
        }

        window.display(); //Actually shows what we drew in the window
    }
}