#include "headers/stdafx.h"

#include "headers/Game.h"

int main()
{
    srand(static_cast <unsigned> (time(0)));

    Game game;

    sf::Clock frameClock;
    sf::Time timeSinceLstUpd = sf::Time::Zero;
    //for fixed frames per second
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    while (game.winOpen()) {

        //if window is open and game is not lost
        if (!game.gameLost()) {
            timeSinceLstUpd += frameClock.restart();

            while (timeSinceLstUpd > TimePerFrame) {
                timeSinceLstUpd -= TimePerFrame;

                game.update(TimePerFrame);

            }

            game.render();
        }
        //if game is lost ask player to player again and froze all other stuff
        else {
            game.restartGame();
            game.render();
        }

        

    }

    return 0;
}