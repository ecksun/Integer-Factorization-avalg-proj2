#include "pollards.h"
#include <iostream>
#define max_bit_size 88
#define iterations_before_gcd 13

bool pollards::factor(mpz_t n, std::vector<mpz_class> & factors) {
    pollards::factor(n, factors, 2);
}

bool pollards::factor(mpz_t n, std::vector<mpz_class> & factors, int initValue) {
    // std::cerr << "factor(" << n << ")" << std::endl;

    /*
     * In case we have found the factor "1", just return
     */
    if (mpz_cmp_si(n, 1) == 0)
        return true;
    // Hantera bara "små" tal 
    if (mpz_sizeinbase(n, 2) >= max_bit_size) {
        return false;
    }

    int prime = mpz_probab_prime_p(n, 5);
    // We found a prime! hopefully
    if (prime != 0) {
        // std::cerr << "We found a prime" << std::endl;
        mpz_class tmp (n);
        factors.push_back(tmp);
        return true;
    }
    else {
        // std::cerr << " Running pollards" << std::endl;
        // Init some temporary variables
        mpz_t x, y, tmp, factor;
        // H ändrade x och y till 3 och fick förbättring
        mpz_init_set_ui(x, initValue);
        mpz_init_set_ui(y, initValue);
        mpz_init(tmp);
        mpz_init_set_ui(factor, 1);


        int power = 1;
        int lam = 1;

        // The actual pollards algoritm
        while (mpz_cmp_si(factor, 1) == 0) {

            for (int i = 0; i < iterations_before_gcd; i++) {
                if (power == lam) {
                    mpz_set(x, y);
                    power *= 2;
                    lam = 0;
                }

                pollards::f(y, n);
                lam++;

                mpz_sub(tmp, y, x);
                mpz_abs(tmp, tmp);
                mpz_mul(factor, factor, tmp);
            }

            mpz_gcd(factor, factor, n);

            // for (int i = 0; i < iterations_before_gcd; i++) {
                // pollards::f(x, n);
                // pollards::f(y, n);
                // pollards::f(y, n);
                // mpz_sub(tmp, y, x);
                // mpz_abs(tmp, tmp);
                // mpz_mul(factor, factor, tmp);
            // }
            // mpz_gcd(factor, factor, n);
            // std::cerr << "x:" << x << std::endl;
            // std::cerr << "y:" << y << std::endl;
            // std::cerr << "factor:" << factor << std::endl;
            // sleep(1);
        }
        if (mpz_cmp(factor, n) == 0) {
            // We coudlnt find anything usefull


            // Trying another init value. Without the "return false"
            // in this if statement we dont have the ability to fail.
            // This might cause TLE if we increase the input values
            // It runs OK with < 88 bits.
            return pollards::factor(n, factors, initValue+1);
            // return false;
        }
        else {
            // We found a factor! lets se if it contains any more factors
            mpz_divexact(n, n, factor);
            // std::cerr << "Starting new recursion" << std::endl;
            if (pollards::factor(n, factors) && 
                    pollards::factor(factor, factors))
                return true;
            else
                return false;
        }
    }
}

/*
 * a pseudo-random function modulo n
 */
void pollards::f(mpz_t x, mpz_t n) {
    mpz_mul(x, x, x);       // Mycket snabbare än mpz_pow_ui(x, x, 2)
    mpz_add_ui(x, x, 1);
    mpz_mod(x, x, n);
}
