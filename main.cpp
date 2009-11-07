#include <gmp.h>
#include <iostream>
#include "pollards.h"

int main() {
    mpz_t a;
    mpz_init(a);

    char string [32];
    while (scanf("%s", &string) != EOF) {
        mpz_set_str(a, string, 10);
        std::cerr << "working on: " << a << std::endl;

        pollards::factor(a);

        std::cout << std::endl;
    }
}

