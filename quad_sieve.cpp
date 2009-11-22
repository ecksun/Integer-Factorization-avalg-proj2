#include "quad_sieve.h"
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

/**
 * TODO: kanske ska köra static ändå och kopiera in de önskade primtalen.
 */



quad_sieve::quad_sieve(int fbs) {
    factor_base mpz_t[fbs];
}

bool quad_sieve::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {


    return true;
}

/**
 * Computes Q(x) = [x + floor(sqrt(n))]^2 - n.
 */
void quad_sieve::q(mpz_t & q_x, mpz_t x, mpz_t n) {

}

/**
 * Sets up the factor base for the quad sieving.
 */
void quad_sieve::setup_factor_base() {
    mpz_t prime;
    mpz_init_set(prime, -1);


    for (int i = 0; i < FACTOR_BASE_SIZE; i++) {

    }




}
