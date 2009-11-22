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
}

/**
 * Destructs this Quadratic Siever.
 */
quad_sieve::~quad_sieve() {
}

/**
 * Performs the prime factorization.
 *
 * @param n The integral number to factorize
 * @param factors A placeholder for the factors found, if any
 */
bool quad_sieve::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    std::vector<mpz_class> factor_base;
    generate_factor_base(factor_base, n);

    mpz_t x;
    mpz_init(x);
    sieve_interval_start(x, n, 0);


    std::cerr << "find_b_smooth_numbers" << std::endl;

    std::vector<mpz_class> xs, ys;
    std::vector< std::vector<int> > exps, m2_exps;
    find_b_smooth_numbers(x, exps, m2_exps, xs, ys, factor_base, n);


    return false;

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
 * @param n The integral number that are being factorized
 */
void quad_sieve::q(mpz_t & y, mpz_t x, mpz_t n) {

    mpz_t x_sq;
    mpz_init(x_sq);
    mpz_mul(x_sq, x, x);
    mpz_sub(y, x_sq, n);

}

/**
 * Generates the factor base for the specified integer to factorize.
 *
 * @param n The integer that will be factorized
 */
void quad_sieve::generate_factor_base(std::vector<mpz_class> & B, mpz_t n) {
    mpz_t p;
    mpz_init_set_ui(p, 2);
    B.push_back(mpz_class(p));

    int i = 1;
    while (i < factor_base_size) {
        mpz_nextprime(p, p);

        if (mpz_legendre(n, p) == 1) {
            B.push_back(mpz_class(p));
            i++;
        }

    }

    mpz_clear(p);
}

/**
 * Finds the specified number of B-smooth numbers, that is, numbers
 * that can be fully factorized by the prime factors in B.
 */
void quad_sieve::find_b_smooth_numbers(
        mpz_t x, std::vector< std::vector<int> > & exps, std::vector< std::vector<int> > & m2_exps, 
        std::vector<mpz_class> & xs, std::vector<mpz_class> & ys, 
        const std::vector<mpz_class> B, mpz_t n) {

    int found_numbers = 0;

    mpz_t y;
    mpz_init(y);

    std::vector<int> exp_vec, m2_exp_vec;

    while (found_numbers < B.size()+1) {
        
        q(y, x, n);

        if (b_smooth(exp_vec, m2_exp_vec, y, B)) {

            xs.push_back(mpz_class(x));
            ys.push_back(mpz_class(y));

            exps.push_back(exp_vec);
            m2_exps.push_back(m2_exp_vec);

            found_numbers++;

            exp_vec.clear();
            m2_exp_vec.clear();

        }

        std::cerr << "x: " << x << "\ty: " << y << std::endl;

        mpz_add_ui(x, x, 1);
        
    }

    mpz_clear(y);

}

/**
 * Checks whether the specified number y is B-smooth or not. If so, 
 * return true and set all corresponding result placeholders.
 * Otherwise, return false.
 */
bool quad_sieve::b_smooth(std::vector<int> & expv, std::vector<int> & m2_expv, 
        mpz_t y, const std::vector<mpz_class> B) {



    return false;
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
 * Finds the first number in the sieve interval to try out.
 *
 * @param x Result placeholder
 * @param n The integral number to factorize
 * @param M Parameter deciding the sieving interval
 * @return The first number of the sieve interval
 */
void quad_sieve::sieve_interval_start(mpz_t x, mpz_t n, int M) {
    mpz_sqrt(x, n);
    mpz_sub_ui(x, x, M);
}
