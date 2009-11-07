#include <gmp.h>
#include <iostream>
#include "pollards.h"

int main() {
    mpz_t a;
    mpz_init(a);

    // A vector to store our results in
    std::vector<unsigned long int> factors;

    char string [32];
    while (scanf("%s", &string) != EOF) {
        // Read the next integer
        mpz_set_str(a, string, 10);
        std::cerr << "working on: " << a << std::endl;

        if (pollards::factor(a, factors)) {
            // In case we didnt fail, print the factors
            for (int i = 0; i < factors.size(); i++) {
                std::cout << factors[i] << std::endl;
            }
        }
        else 
            std::cout << "fail" << std::endl;

        // Clear the vector to store the next integers factors
        factors.clear();

        std::cout << std::endl;
    }
}

