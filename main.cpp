#include <gmp.h>
#include <iostream>
#include "pollards.h"

int main() {
    mpz_t a, factor;
    mpz_init(a);
    mpz_init(factor);

    char string [32];
    while (scanf("%s", &string) != EOF) {
        mpz_set_str(a, string, 10);
        bool moreFactors = true;
        
        // Do the factorisation here
        while (moreFactors) {
            std::cerr << "pollards" << std::endl;
            pollards p(&a);
            std::cerr << "eftter p(&a)" << std::endl;
            if (p.run(factor)) {
                // we found a factor
                std::cerr << "factor:";
                std::cout << factor << std::endl;
                mpz_divexact(a, a, factor);
            }
            else {
                std::cerr << "else" << std::endl;
                int prime = mpz_probab_prime_p(a, 5);
                if (prime == 2) {
                    // a is definitly a prime
                    std::cout << a << std::endl;
                    moreFactors = false;
                }
                else {
                    std::cout << "fail" << std::endl;
                }
                /*
                if (prime == 1){
                    
                    // a is probably a prime
                }
                if (prime == 0) {
                    // a is definitly NOT a prime (composite) we should continue
                }
                */
            }
        }
        std::cerr << "nextprime" << std::endl;
    }
}

