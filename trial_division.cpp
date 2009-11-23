#include "trial_division.h"
#include <iostream>
#define divisors 256

trial_division::trial_division() {
}

void trial_division::factor(mpz_t n, std::vector<mpz_class> & factors) {
    // std::cerr << "factor(" << n << ")" << std::endl;
    // mpz_sqrt() eller mpz_tdiv_q_2exp
    mpz_t sqrt;
    mpz_init(sqrt);
    mpz_sqrt(sqrt, n);


    mpz_t prime;
    mpz_init_set_ui(prime, 2);
    /*
     * In case we have found the factor "1", just return
     */
    if (mpz_cmp_si(n, 1) == 0)
        return;
    /* 
     * If we have an even number, we have a special case
     */
    if (mpz_even_p(n)) {
        mpz_class two(2);

        factors.push_back(two);

        mpz_divexact_ui(n, n, 2);
        this->factor(n, factors); 
        return;
    }
    else {
        for (int i = 0; i < divisors; i++) {
            mpz_nextprime(prime, prime);
            // For small numbers we dont want to try more then nescesary
            if (mpz_cmp(prime, sqrt) > 0) {
                return;
            }

            if (mpz_divisible_p(n, prime) != 0) {
                mpz_class factor(prime);

                factors.push_back(factor);

                mpz_divexact(n, n, prime);
                this->factor(n, factors);
                return;
            }
        }
    }
}
