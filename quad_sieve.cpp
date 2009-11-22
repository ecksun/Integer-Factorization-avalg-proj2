#include "quad_sieve.h"
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

const int factor_base_size = 5;

/**
 * Constructs a new Quadratic Siever.
 */
quad_sieve::quad_sieve() {
    factor_base = new mpz_t [factor_base_size];
}

/**
 * Destructs this Quadratic Siever.
 */
quad_sieve::~quad_sieve() {
    delete[] factor_base;
}

/**
 * Performs the prime factorization.
 *
 * @param n The integer number to factorize
 * @param factors A placeholder for the factors found, if any
 */
bool quad_sieve::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    generate_factor_base(n);

    mpz_t x;
    mpz_init(x);
    sieve_interval_start(x, n);

    find_b_smooth_numbers(x, factor_base_size+1);

    std::vector<int> selected_indices;
    select_b_smooth_numbers(selected_indices);


    // almost done when here ...
   
    

    return true;
}

/**
 * Computes Q(x) = x^2 - n and stores the result in y.
 *
 * @param y Placeholder for the result
 * @param x The x to calculate Q(x) from
 * @param n The integer number that are being factorized
 */
void quad_sieve::q(mpz_t & y, mpz_t x, mpz_t n) {

}

/**
 * Generates the factor base for the specified integer to factorize.
 *
 * @param n The integer that will be factorized
 */
void quad_sieve::generate_factor_base(mpz_t n) {
    mpz_t p;
    mpz_init_set_ui(p, 2);

    for (int i = 0; i < factor_base_size; i++) {

    }

    mpz_clear(p);
}

/**
 * Find the specified number of B-smooth numbers, that is, numbers
 * that can be fully factorized by the prime factors in B.
 *
 * @param start The first number to try
 * @param num_results The number of B-smooth numbers wanted
 */
void quad_sieve::find_b_smooth_numbers(mpz_t start, int num_results) {

}

/**
 * Finds a subset of the earlier discovered B-smooth numbers, that
 * will result in a perfect square later on. 
 *
 * @param subset A placeholder for the indices selected 
 */
void quad_sieve::select_b_smooth_numbers(std::vector<int> subset) {

}

/**
 * Returns the first number in the sieve interval to try out.
 *
 * @param n The integral number to factorize
 * @return The first number of the sieve interval
 */
void quad_sieve::sieve_interval_start(mpz_t x, mpz_t n) {
    // TODO: sqrt(n)-M
}
