#include <iostream>
#include <string>
#include <cstdlib>

typedef enum {
    ROCK = 0,
    PAPER,
    SCISSORS
} Move;
const std::string moveStrings[3] = {"Rock", "Paper", "Scissors"};

typedef enum
{
    WIN = 0,
    LOSE,
    TIE
} Outcome;
const std::string outcomeStrings[3] = {"won", "lose", "tied"};

void scram()
{
    std::cout << std::endl << "Encountered an unexpected error." << std::endl;
    exit(-1);
}

class Player
{
    public:
        int points;
        std::string name;
        virtual Move make_move() const = 0;
};

class HumanPlayer: public Player
{
    public:
        Move make_move() const
        {
            while(true)
            {
                std::cout << "You can choose between \"Rock\", \"Paper\" and \"Scissors\"" << std::endl;
                std::cout << "What is your move, " << name << "? ";
                std::string input;
                std::cin >> input;

                for(int i = 0; i < 3; i++)
                    if(input.compare(moveStrings[i]) == 0)
                        return (Move)i;

                std::cout << "Invalid input. Try again!\n" << std::endl;
            }
            return (Move)-1;
        }

        HumanPlayer(std::string name)
        {
            this->points = 0;
            this->name = name;
        }
};

class ComputerPlayer : public Player
{

    public:
        virtual Move make_move() const
        {
            return (Move)(std::rand() / ((RAND_MAX + 1u) / 3));
        }
    
        ComputerPlayer()
        {
            this->points = 0;
            this->name = "Computer";
        }
};

class Referee
{
    private:
        Outcome evaluate_moves(Move p1Move, Move p2Move)
        {
            switch(p1Move)
            {
                case ROCK:
                    switch(p2Move)
                    {
                        case ROCK:
                            return TIE;
                        break;
                        case PAPER:
                            return LOSE;
                        break;
                        case SCISSORS:
                            return WIN;
                        break;
                    }
                break;
                case PAPER:
                    switch(p2Move)
                    {
                        case ROCK:
                            return WIN;
                        break;
                        case PAPER:
                            return TIE;
                        break;
                        case SCISSORS:
                            return LOSE;
                        break;
                    }
                break;
                case SCISSORS:
                    switch(p2Move)
                    {
                        case ROCK:
                            return WIN;
                        break;
                        case PAPER:
                            return LOSE;
                        break;
                        case SCISSORS:
                            return TIE;
                        break;
                    }
                break;
            }

            return (Outcome)-1;
        }

    public:
        void play_round(Player* p1, Player* p2)
        {
            Move p1Move = p1->make_move();
            Move p2Move = p2->make_move();

            if(p1Move < -1 || p2Move < -1)
                scram();

            Outcome p1o = evaluate_moves(p1Move, p2Move);
            Outcome p2o = TIE;

            if(p1o == WIN)
                p2o = LOSE;
            else if(p1o == LOSE)
                p2o = WIN;

            if(p1o < 0)
                scram();

            if(p1o == WIN)
                p1->points++;
            else if(p1o == TIE)
                ;   // compact syntax to say "do nothing"
            else if(p1o == LOSE)
                p2->points++;
            
            std::cout << p1->name << " played " << moveStrings[p1Move] << " whilst " << p2->name << " retaliated with " << moveStrings[p2Move] << "." << std::endl;
            std::cout << p1->name << ", you " << outcomeStrings[p1o] << " and " << p2->name << ", you " << outcomeStrings[p2o] << "!" << std::endl;
            std::cout << p1->name << " has " << p1->points << " point(s) and " << p2->name << " point(s) has " << p2->points << "." << std::endl << std::endl;
        }
};

int main()
{
    HumanPlayer simon = HumanPlayer("Simon");
    HumanPlayer mika = HumanPlayer("Mikail");
    ComputerPlayer computer = ComputerPlayer();

    Referee r = Referee();

    while(1)
        r.play_round(&simon, &mika);
}