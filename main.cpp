#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include "pollards.h"
#include "trial_division.h"
#include "fermat_squares.h"

int main() {
    mpz_t a;
    mpz_init(a);

    // A vector to store our results in
    std::vector<mpz_class> factors;

    char string[32];
    while (gmp_scanf("%s", &string) != EOF) {
        // Read the next integer
        mpz_set_str(a, string, 10);
        std::cerr << "working on: " << a << std::endl;
        // Try trial division for small numbers here instead of 
        // in pollards
//        trial_division TD;
//        TD.factor(a, factors);
//        if (pollards::factor(a, factors)) {
//             In case we didnt fail, print the factors
//            for (int i = 0; i < factors.size(); i++) {
//                std::cout << factors[i] << std::endl;
//            }
//        }
//        else 
//            std::cout << "fail" << std::endl;


        if (fermat_squares::prime_factorize(a, factors)) {
            // In case we didnt fail, print the factors
            for (int i = 0; i < factors.size(); i++) {
                std::cout << factors[i] << std::endl;
            }
        }
        else {
            std::cout << "fail" << std::endl;
        }


        // Clear the vector to store the next integers factors
        factors.clear();

        std::cout << std::endl;
    }

    mpz_clear(a);
}

