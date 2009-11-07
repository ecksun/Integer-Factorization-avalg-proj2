#include "pollards.h"
#include <iostream>

bool pollards::factor(mpz_t n) {
    std::cerr << "factor(" << n << ")" << std::endl;
    std::cerr << "size:" << mpz_sizeinbase(n, 2) << std::endl;
    if (mpz_cmp_si(n, 1) == 0)
        return true;
    if (mpz_even_p(n)) {
        // Jämnt tal
        // std::cerr << "Found even number" << std::endl;
        mpz_t two;
        mpz_init_set_si(two, 2);
        // std::cout << 2 << std::endl;
        pollards::factors.push_back(2);

        mpz_divexact_ui(n, n, 2);
        pollards::factor(n);
        return true;
    }
    // Hantera bara 64 bitars tal så faktorerna får plats i en lista med unsigned long ints
    if (mpz_sizeinbase(n, 2) >= 64) {
        std::cout << "fail" << std::endl;
        return false;
    }

    int prime = mpz_probab_prime_p(n, 5);
    // We found a prime!
    if (prime == 2) {
        // std::cerr << "We found a prime" << std::endl;
        std::cout << n << std::endl;
        return true;
    }
    else {
        // std::cerr << " Running pollards" << std::endl;
        mpz_t x, y, tmp, factor;
        mpz_init_set_ui(x, 2);
        mpz_init_set_ui(y, 2);
        mpz_init(tmp);
        mpz_init_set_ui(factor, 1);


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
            std::cout << "fail" << std::endl;
            return false;
        }
        else {
            mpz_divexact(n, n, factor);
            // std::cerr << "Starting new recursion" << std::endl;
            if (pollards::factor(n) && 
            pollards::factor(factor))
                return true;
            else
                return false;
        }
    }
}

void pollards::f(mpz_t x, mpz_t n) {
    mpz_mul(x, x, x);
    mpz_add_ui(x, x, 4710);
    mpz_mod(x, x, n);
}
