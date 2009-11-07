#include "pollards.h"
#include <iostream>

bool pollards::factor(mpz_t n, std::vector<unsigned long int> & factors) {
    // std::cerr << "factor(" << n << ")" << std::endl;
    // std::cerr << "size:" << mpz_sizeinbase(n, 2) << std::endl;

    /*
     * In case we have found the factor "1", just return
     */
    if (mpz_cmp_si(n, 1) == 0)
        return true;
    /* 
     * If we have an even number, we have a special case, pollards
     * didnt seem to handle the factor 2 verry well
     */
    if (mpz_even_p(n)) {
        // Jämnt tal
        // std::cerr << "Found even number" << std::endl;

        mpz_t two;
        mpz_init_set_si(two, 2);

        factors.push_back(2);

        mpz_divexact_ui(n, n, 2);

        if (pollards::factor(n, factors))
            return true;
        else 
            return false;
    }
    // Hantera bara 64 bitars tal så faktorerna får plats i en lista med unsigned long ints
    if (mpz_sizeinbase(n, 2) >= 82) {
        return false;
    }

    int prime = mpz_probab_prime_p(n, 5);
    // We found a prime! hopefully
    if (prime == 2 || prime == 1) {
        // std::cerr << "We found a prime" << std::endl;
        factors.push_back(mpz_get_ui(n));
        return true;
    }
    else {
        // std::cerr << " Running pollards" << std::endl;
        // Init some temporary variables
        mpz_t x, y, tmp, factor;
        mpz_init_set_ui(x, 2);
        mpz_init_set_ui(y, 2);
        mpz_init(tmp);
        mpz_init_set_ui(factor, 1);


        // The actual pollards algoritm
        while (mpz_cmp_si(factor, 1) == 0) {
            pollards::f(x, n);
            pollards::f(y, n);
            pollards::f(y, n);
            mpz_sub(tmp, x, y);
            mpz_abs(tmp, tmp);
            mpz_gcd(factor, tmp, n);
            // std::cerr << "x:" << x << std::endl;
            // std::cerr << "y:" << y << std::endl;
            // std::cerr << "factor:" << factor << std::endl;
            // sleep(1);
        }
        if (mpz_cmp(factor, n) == 0) {
            // We coudlnt find anything usefull
            // std::cout << "fail" << std::endl;
            return false;
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
    mpz_mul(x, x, x);
    mpz_add_ui(x, x, 2);
    mpz_mod(x, x, n);
}
