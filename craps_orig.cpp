/**
 * \file craps_orig.cpp
 * \date 7-Nov-2011
 *
 *
 */

#include <cstdlib>
#include <iostream>

int roll_die() { return rand() % 6 + 1; }

class Roll {
    int die1;
    int die2;
public:
    Roll() : die1(roll_die()), die2(roll_die()) {}
    int sum() { return die1 + die2; }
};

int main() {

    std::pair<int, int> decision(0, 0);

    for ( int ix=0; ix<10'000; ++ix ) {

        Roll r1;
        if ( r1.sum() == 7 || r1.sum() == 11 ) {
            std::cout << "Shooter wins on first roll with " << r1.sum() << '\n';
            ++decision.first;
        }
        else if ( r1.sum() == 2 || r1.sum() == 3 || r1.sum() == 12 ) {
            std::cout << "Shooter loses on first roll with " << r1.sum() << '\n';
            ++decision.second;
        }
        else {
            std::cout << "Shooter establishes point with " << r1.sum() << '\n';
            while ( true ) {
                Roll r2;
                if ( r2.sum() == r1.sum() ) {
                    std::cout << "Shooter wins on subsequent roll with " << r2.sum() << '\n';
                    ++decision.first;
                    break;
                }
                else if ( r2.sum() == 7 ) {
                    std::cout << "Shooter loses on subsequent roll with " << r2.sum() << '\n';
                    ++decision.second;
                    break;
                }
                else
                    std::cout << "Shooter rolls a " << r2.sum() << '\n';
            }
        }

    }

    std::cout << "\n\nWon  " << decision.first << " times" << '\n'
              << "Lost " << decision.second << " times" << '\n';

    return 0;

}
