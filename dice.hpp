#pragma once
#include <random>
#include <iostream>

/**
 * @brief A class to simulate a dice roll with random results.
 */
class Dice {
private:
    std::mt19937 generator; /**< Random number generator */
    std::uniform_int_distribution<int> distribution; /**< Distribution for dice rolls */

public:
    /**
     * @brief Constructor to initialize the dice with random seed.
     */
    Dice() : distribution(1, 6) {
        std::random_device rd;  // Seed generator
        generator.seed(rd());   // Seeding the generator with random device
    }

    /**
     * @brief Rolls the dice and returns the result.
     * @return The result of the dice roll (between 1 and 6).
     */
    int roll() {
        return distribution(generator);
    }
};

// ? example usage with main
// int main() {
//     Dice diceObj;
    
//     // Example of rolling the dice
//     for (int i = 0; i < 10; ++i) {
//         std::cout << "Roll " << i + 1 << ": " << diceObj.roll() << std::endl;
//     }

//     return 0;
// }
