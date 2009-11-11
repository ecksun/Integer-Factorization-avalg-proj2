#include "trial_division.h"
#include <iostream>


trial_division::trial_division() {
    // divisor[0] = 3;
    // divisor[1] = 5;
    // divisor[2] = 7;
    // divisor[3] = 11;
    // divisor[4] = 13;
    // divisor[5] = 17;
    // divisor[6] = 19;
    // divisor[7] = 23;
    // divisor[8] = 29;
    // divisor[9] = 31;
    // divisor[10] = 37;
    // divisor[11] = 41;
    // divisor[12] = 43;
    // divisor[13] = 47;
    // divisor[14] = 53;
    // divisor[15] = 59;
    // divisor[16] = 61;
    // divisor[17] = 67;
    // divisor[18] = 71;
    // divisor[19] = 73;
    // divisor[20] = 79;
    // divisor[21] = 83;
    // divisor[22] = 89;
    // divisor[23] = 97;
    // divisor[24] = 101;
    // divisor[25] = 103;
    // divisor[26] = 107;
    // divisor[27] = 109;
    // divisor[28] = 113;
    // divisor[29] = 127;
    // divisor[30] = 131;
    // divisor[31] = 137;

}

void trial_division::factor(mpz_t n, std::vector<mpz_class> & factors) {
    // std::cerr << "factor(" << n << ")" << std::endl;

    mpz_t prime;
    mpz_init_set_ui(prime, 2);
    /*
     * In case we have found the factor "1", just return
     */
    if (mpz_cmp_si(n, 1) == 0)
        return;
    /* 
     * If we have an even number, we have a special case, pollards
     * didnt seem to handle the factor 2 verry well
     */
    if (mpz_even_p(n)) {
        mpz_class two(2);

        factors.push_back(two);

        mpz_divexact_ui(n, n, 2);

    }
    else {
        for (int i = 0; i < divisors; i++) {
            mpz_nextprime(prime, prime);
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
