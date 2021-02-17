#include "Player.h"

/**
 * Constructor of player
 * Initialize variables
**/
Player::Player(const std::string name, const bool isHuman) {
    name_ = name;
    is_human_ = isHuman;
    points_ = 0;
    isAlive_ = true;
}

/**
 * Add x amount of points to player's score
 * 
 * @param The amount of points you want to add to players score
**/
void Player::ChangePoints(const int x) {
    points_ += x;
}

void Player::changeAlive(const bool status) {
    isAlive_ = status;
}

/**
 * Set a new position for player
 * 
 * @param The new position the player wants to go
**/
void Player::SetPosition(Position newPos) {
    pos_ = newPos;
}

/**
 * Get either up, down, right, left of relative position
 * 
 * @param The positions the player wants to go to
 * @return The corresponding direction
**/
std::string Player::ToRelativePosition(Position other) {
    std::string direction = "This should not have happened!";
    Position getPlayerPosition = get_position();

    if(other.row - getPlayerPosition.row == -1) {
        direction = "UP";
    }
    else if(other.row - getPlayerPosition.row == 1) {
        direction = "DOWN";
    }
    else if(other.col - getPlayerPosition.col == 1) {
        direction = "RIGHT";
    }
    else if (other.col - getPlayerPosition.col == -1) {
        direction = "LEFT";
    }

    return direction;
}

/**
 * String the players name and points together
 * Will be used to generate report
 * 
 * @return a concatenated string
**/
std::string Player::Stringify() {
    std::string name = get_name();
    std::string points = std::to_string(get_points());
    std::string player = name + " " + points;
    return player;
}