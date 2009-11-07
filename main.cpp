#include <gmp.h>
#include <iostream>
#include "pollards.h"

int main() {
    mpz_t a;
    mpz_init(a);

    std::vector<unsigned long int> factors;

    char string [32];
    while (scanf("%s", &string) != EOF) {
        mpz_set_str(a, string, 10);
        std::cerr << "working on: " << a << std::endl;

        if (pollards::factor(a, factors)) {
            for (int i = 0; i < factors.size(); i++) {
                std::cout << factors[i] << std::endl;
            }
        }
        else 
            std::cout << "fail" << std::endl;

        factors.clear();

        std::cout << std::endl;
    }
}

