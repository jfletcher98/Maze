/**
 * John Fletcher
 * 
 * Maze Game
 * Attempt to make a board playable each time
**/

#include "Maze.h"
#include "Player.h"
#include <iostream>

int main() {
    Player* p1 = new Player("john", true);
    Maze game;

    game.NewGame(p1, 2);
    std::cout<<game<<std::endl;
    Player* nextPlayer = p1;

    while(!game.IsGameOver()) {
        game.TakeTurn(nextPlayer);
        std::cout<<game<<std::endl;
        nextPlayer = game.GetNextPlayer();
    }
    std::cout<<"Game Over! Here is this games stats!:"<<std::endl;
    std::cout<<game.GenerateReport()<<std::endl;
}