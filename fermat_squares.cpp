#include "fermat_squares.h"

/**
 * Factorizes the specified multiple precision integer into its prime
 * factors and places in the given std vector, when returning true.
 * Alternatively, the algorithm decides it is not able to perform the
 * factorization and then returns false instead.
 */
bool fermat_squares::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    return false;
}

/**
 * Factorizes the specified multiple precision integer into a pair of
 * factors, when returning true. If returning false, then the
 * algorithm decided it was not able to perform the factorization.
 */
bool fermat_squares::factorize(mpz_t n, std::pair<mpz_class,mpz_class> & factors) {

    bool factors_found = false;
    mpz_t x, q_x, x_sqr, q_x_sqr;

    mpz_init(x);
    mpz_init(q_x); 
    mpz_init(x_sqr);
    mpz_init(q_x_sqr);

    mpz_sqrt(x, n); // x <-- int(sqrt(n))


    return true; // TODO
}


/**
 * Calculates the function Q(x) = x^2 - n and sets q_x to this value.
 */
void fermat_squares::q(mpz_t q_x, mpz_t x_sqr, mpz_t n) {

}
