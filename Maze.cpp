#include "Maze.h"
#include <iostream>
#include <ctime>

/**
 * Return the corresponding emojies of specific square type
 * @param The type of square to turn into a string
 * @return The correlating emoji string
**/
std::string SquareTypeStringify(SquareType sq) {
    if(sq == SquareType::Wall) {
        return "❌";
    }
    else if(sq == SquareType::Exit) {
        return "✅";
    }
    else if(sq == SquareType::Enemy) {
        return "💀";
    }
    else if(sq == SquareType::Human) {
        return "👨";
    }
    else if(sq == SquareType::Treasure) {
        return "💰";
    }
    else if(sq == SquareType:: Empty) {
        return "⚪";
    }
    return "There was a problem loading the Squares";
}

/**
 * Construct the Board with random tiles
**/
Board::Board() {
    int numRows = get_rows();
    int numCols = get_cols();
    int randNum;
    std::srand(std::time(nullptr));

    //Used for step 2: Improving the game
    Position upperRight;
    Position bottomRight;
    Position upperLeft;
    Position bottomLeft;

    SquareType upperRightType;
    SquareType bottomRightType;
    SquareType upperLeftType;
    SquareType bottomLeftType;
    
    //Go through all squares on Board
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            randNum = std::rand()%100+1;

            if(randNum <= 30 && randNum > 10) {
                upperRight = {i-1, j+1};
                bottomRight = {i+1, j+1};
                upperLeft = {i-1, j-1};
                bottomLeft = {i+1, j-1};

                //Check if diagonals of random position has a square
                upperRightType = get_square_value(upperRight);
                bottomRightType = get_square_value(bottomRight);
                upperLeftType = get_square_value(upperLeft);
                bottomLeftType = get_square_value(bottomLeft);

                //SREESHA- I HAVE NO IDEA HOW MY CODE IS SPAWNING WALLS
                if(upperRightType != SquareType::Wall && bottomRightType != SquareType::Wall && upperLeftType != SquareType::Wall && bottomLeftType != SquareType::Wall) {
                    std::cout<<i<<j<<" "<<SquareTypeStringify(upperRightType)<<" "<<SquareTypeStringify( bottomRightType)<<" "<<SquareTypeStringify(upperLeftType)<<" "<<SquareTypeStringify(bottomLeftType)<<std::endl;
                    arr_[i][j] = SquareType::Wall;
                }
            }
            //Randomly place treasure
            else if(randNum <= 10) {
                arr_[i][j] = SquareType::Treasure;
            } 
            //place Empty Squares
            else {
                arr_[i][j] = SquareType::Empty;
            }

        }
    }
    arr_[0][0] = SquareType::Human;
    arr_[numRows-1][numCols-1] = SquareType::Exit;
    //arr_[0][3] = SquareType::Enemy;
}

/**
 * Get the square value at a certain position
 * 
 * @param Position of square you want value
 * @return the value of the Square
 **/
SquareType Board::get_square_value(Position pos) const {
    return arr_[pos.row][pos.col];
}

/**
 * Set the square value at a certain position
 *  
 * @param pos: The position of the square you want to change value for, type: The type of square you want to change it to
**/
void Board::SetSquareValue(Position pos, SquareType type) {
    arr_[pos.row][pos.col] = type;
}

/**
 * Get the allowed moves a player can make on a turn
 * Not Allowed Moves:Into Wall or off Board
 * 
 * @param Get Player that is wanting to move
 * @return a vector of positions that player can move
 **/
std::vector<Position> Board::GetMoves(Player *p) {
    std::vector<Position> allowedMoves;
    Position playerPosition = p->get_position();
    Position potentialUp;
    Position potentialRight;
    Position potentialDown;
    Position potentialLeft;

    //Get pos of square above player
    potentialUp.row = playerPosition.row - 1;
    potentialUp.col = playerPosition.col;
    
    //Get pos of square to the right of player
    potentialRight.row = playerPosition.row;
    potentialRight.col = playerPosition.col + 1;

    //Get pos of square below player
    potentialDown.row = playerPosition.row + 1;
    potentialDown.col = playerPosition.col;

    //Get pos of square to the left of player
    potentialLeft.row = playerPosition.row;
    potentialLeft.col = playerPosition.col - 1;

    //Make sure allowed move is not into wall or off board
    if(get_square_value(potentialUp) != SquareType::Wall && potentialUp.row > -1) {
        allowedMoves.push_back(potentialUp);
    }

    if(get_square_value(potentialRight) != SquareType::Wall && potentialRight.col < get_cols()) {
        allowedMoves.push_back(potentialRight);
    }

    if(get_square_value(potentialDown) != SquareType::Wall && potentialDown.row < get_rows()) {
        allowedMoves.push_back(potentialDown);
    }

    if(get_square_value(potentialLeft) != SquareType::Wall && potentialLeft.col > -1) {
        allowedMoves.push_back(potentialLeft);
    }
    
    return allowedMoves;
}

/**
 * Move a player to an allowed position for their turn
 * 
 * @param p: The player that wants to move, pos: The position the player wants to move to
 **/
bool Board::MovePlayer(Player *p, Position pos) {
    std::vector<Position> allowedMoves = GetMoves(p);
    bool succesMove = false;
    Position lastPos = p->get_position();

    //Only move to allowed positions
    for(Position position : allowedMoves) {
        if(pos == position) {
            p->SetPosition(pos);
            if(p->is_human()) {
                if(arr_[pos.row][pos.col] == SquareType::Exit) {
                    p->ChangePoints(1);
                    std::cout<<"You reached the Exit!"<<std::endl;
                }
                else if(arr_[pos.row][pos.col] == SquareType::Treasure) {
                    p->ChangePoints(100);
                    std::cout<<"You got some treasure!"<<std::endl;
                }
                SetSquareValue(lastPos, SquareType::Empty);
                SetSquareValue(pos, SquareType::Human);
            }
            else {
                if(arr_[lastPos.row][lastPos.col] == arr_[get_rows()-1][get_cols()-1]) {
                    SetSquareValue(lastPos, SquareType::Exit);
                    SetSquareValue(pos, SquareType::Enemy);
                } else {
                    SetSquareValue(pos, SquareType::Enemy);
                    SetSquareValue(lastPos, SquareType::Empty);
                }            }
            succesMove = true;
        }
    }

    return succesMove;
}

/**
 * Used to check if human has reached the exit
 * 
 * @return the type of square that is the exit
 **/
SquareType Board::GetExitOccupant(){
    return arr_[get_rows()-1][get_cols()-1];
}

/**
 * overload << operator to print out Square Types
**/
std::ostream& operator<<(std::ostream& os, const Board &b) {
    for(int i = 0; i < b.get_rows(); i++) {
        for(int j = 0; j < b.get_cols(); j++) {
            os<<SquareTypeStringify(b.arr_[i][j])<<std::endl;
        }
    }
    return os;
}

//Maze Class
Maze::Maze() {
    board_ = new Board();
    turn_count_ = 0;
}

/**
 * Create and initialize a new game
 * 
 * @param human: The human player that will play, numEnemies: The number of enemies in the game
**/
void Maze::NewGame(Player* human, const int numEnemies) {
    Position startHuman = {0, 0};
    human->SetPosition(startHuman);
    players_.push_back(human);

    int randRow;
    int randCol;
    bool isFilled = false;
    int counter = 0;
    Position randPos;
    std::srand(std::time(nullptr));

    //Create number of enemies at random position
        while(!isFilled) {
            /**
             * Make sure an enemy always spawns by continusously getting
             * a random square until an empty one is found
            **/
                if(counter < numEnemies) {
                    randRow = std::rand() % board_->get_rows();
                    randCol = std::rand() % board_->get_cols();
                    randPos = {randRow, randCol};

                    //Make sure the position is not filled 
                    if(board_->get_square_value(randPos) == SquareType::Empty) {
                        Player* newEnemy = new Player("enemy", false);
                        newEnemy->SetPosition(randPos);
                        board_->SetSquareValue(randPos, SquareType::Enemy);
                        players_.push_back(newEnemy);
                        counter++;
                    }     
                } else
                {
                    isFilled = true;
                }
                
   
    }
}

/**
 * Method that lets player decide where to move to
 * 
 * @param The player that is taking the turn and moving
**/
void Maze::TakeTurn(Player *p) {
    std::vector<Position> allowedMoves = board_->GetMoves(p);
    bool validAnswer = false;
    //Continuously ask the player to input a correct move until they do
    do {
        std::cout<<p->get_name()<<": Please enter one of the following to make your move (Case Sensitive)"<<std::endl;

        //Print out the relative positions that the player is allowed to move to
        for(Position position : allowedMoves) {
            std::cout<<p->ToRelativePosition(position)<<", ";
        }
        std::cout<<std::endl;
        std::string answer;
        std::cin>>answer;

        //See if user move is valid
        for(Position checkPosition : allowedMoves) {

            if(answer == p->ToRelativePosition(checkPosition)) {
                //std::cout<<"That is a valid move"<<std::endl;
                if(board_->MovePlayer(p, checkPosition)) {
                    turn_count_++;
                } else {
                    std::cout<<"There was a problem taking that turn!"<<std::endl;
                }
                validAnswer = true;
            }
        }
    }while(!validAnswer);
}

/**
 * Find the player that has the next turn
 * 
 * @return The next player to take their turn
**/
Player* Maze::GetNextPlayer() {
    Player* nextPlayer = players_[turn_count_ % players_.size()]; //Point to the next players turn
    return nextPlayer;
}

/**
 * Check to see if the game is over
 * 
 * @return True if human has reached Exit or if there is no human left(Not implemented)
**/
bool Maze::IsGameOver() {

    if(board_->GetExitOccupant() == SquareType::Human) {
        return true;
    }

    //Seperate players into human and non human    
    std::vector<Player*> humans;
    std::vector<Player* > enemies;
    for(Player* p : players_) {
        if(p->is_human()) {
           humans.push_back(p); 
        } else {
            enemies.push_back(p);
        }
    }

    //loop through all human and enemy players and see if an enemy is on the same location of a human
    //Change alive status of human to false if both are on the same location
    for(Player* human : humans) {
        for(Player* enemy : enemies) {
            if(human->get_position() == enemy->get_position()) {
                human->changeAlive(false);
            }
        }
    }

    //Continue running the game if there is still a human alive
    for(Player* p : players_) {
        if(p->is_human() && p->isAlive()) {
            return false;
        }
    }
    
    return true;
}

/**
 * Print a string that shows each player their name and corresponding score
**/
std::string Maze::GenerateReport() {
    std::string report;
    for(Player* p : players_) {
        report += p->Stringify()+" ";
    }
    return report;
}

std::ostream& operator<<(std::ostream& os, const Maze &m) {
    for(int i = 0; i < m.board_->get_rows(); i++) {
        for(int j = 0; j < m.board_->get_cols(); j++) {
            Position newPlace = {i, j};
            os<<SquareTypeStringify(m.board_->get_square_value(newPlace))<<" ";
        }
        os<<std::endl;
    }
    return os;
}