/* Rock Paper Scissors Simlator */

#include <iostream>
#include <string>
#include <cstdlib>

/* Enum type that defines the different possible moves */
typedef enum {
    ROCK = 0,
    PAPER,
    SCISSORS
} Move;
// const string array with the values of the Move enum corresponding to the fitting index for a move as string
const std::string moveStrings[3] = {"Rock", "Paper", "Scissors"};

/* Enum type that defines the different possible evaluation outcomes */
typedef enum
{
    WIN = 0,
    LOSE,
    TIE
} Outcome;
// const string array with the values of the Outcome enum corresponding to the fitting index for an outcome as string
const std::string outcomeStrings[3] = {"won", "lose", "tied"};

/* Scram function that kills the program after printing an error message to stderr */
void scram()
{
    std::cerr << std::endl << "Encountered an unexpected error." << std::endl;
    exit(-1);
}

/* Interface Player Class */
class Player
{
    public:
        int points;
        std::string name;
        virtual Move make_move() const = 0;
};

/* Human Player Class which extends player */
class HumanPlayer: public Player
{
    public:
        /* Implementation of initially virtual make_move function */
        Move make_move() const
        {
            std::cout << "You can choose between \"Rock\", \"Paper\" and \"Scissors\"" << std::endl;
            std::cout << "  What is your move, " << name << "? ";
            while(true)
            {
                std::string input;

                // Prompt

                // Get input        
                std::cin >> input;

                // Evaluate input
                for(int i = 0; i < 3; i++)
                    if(input.compare(moveStrings[i]) == 0)
                        return (Move)i;

                // When invalid, print notice and restart loop
                std::cout << "  !! Invalid input. Try again: ";
            }

            // This should never happen. Returns a negative value for type Move, which denotes an error in my program.
            return (Move)-1;
        }

        /* Constructor */
        HumanPlayer(std::string name)
        {
            this->points = 0;
            this->name = name;
        }
};

/* Computer Player class that extends player */
class ComputerPlayer : public Player
{

    public:
        /* Implementation of initially virtual make_move function */
        Move make_move() const
        {
            // Returns a random value (as Move) between 0 and 3
            return (Move)(std::rand() / ((RAND_MAX + 1u) / 3));
        }
    
        /* Constructor */
        ComputerPlayer()
        {
            this->points = 0;
            this->name = "Computer";
        }
};

class Referee
{
    private:
        /* Evaluates a move as loss, win or tie */
        /* Note to self: find out more sophisticated method to calculate different cases. Current nested switch is crude. */
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

            // This should never happen. Returns a negative value for type Outcome, which denotes an error in my program.
            return (Outcome)-1;
        }

    public:
        /* This makes the Referee play a round */
        void play_round(Player* p1, Player* p2)
        {
            // Get Moves from each player
            Move p1Move = p1->make_move();
            Move p2Move = p2->make_move();

            // Evaluate if an error occurred. If so, scram
            if(p1Move < -1 || p2Move < -1)
                scram();

            // Evaluate outcome for player 1, set initial outcome of player 2 to TIE.
            Outcome p1o = evaluate_moves(p1Move, p2Move);
            Outcome p2o = TIE;

            // Evaluate if an error occurred. If so, scram
            if(p1o < 0)
                scram();

            // Evaluate outcome for player 2
            if(p1o == WIN)
                p2o = LOSE;
            else if(p1o == LOSE)
                p2o = WIN;

            // Evaluate points
            if(p1o == WIN)
                p1->points++;
            else if(p1o == TIE)
                ;   // compact syntax to say "do nothing"
            else if(p1o == LOSE)
                p2->points++;
            
            // Print results
            std::cout << p1->name << " played " << moveStrings[p1Move] << " whilst " << p2->name << " retaliated with " << moveStrings[p2Move] << "." << std::endl;
            std::cout << p1->name << ", you " << outcomeStrings[p1o] << " and " << p2->name << ", you " << outcomeStrings[p2o] << "!" << std::endl;
            std::cout << p1->name << " has " << p1->points << " point(s) and " << p2->name << " point(s) has " << p2->points << "." << std::endl << std::endl;
        }
};

int main()
{
    // Declaration and initalisation of players
    HumanPlayer mika = HumanPlayer("Mikail");
    HumanPlayer simon = HumanPlayer("Simon");
    ComputerPlayer computer1 = ComputerPlayer();

    // Declaration and initialisation of the referee
    Referee r = Referee();

    // forever loop that makes the referee play infinite rounds of rock paper scissors
    while(1)
        // These need to be passed as pointers, since they are implementations of a commmon interface
        r.play_round(&mika, &simon);
}