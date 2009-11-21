#include "fermat_squares.h"

/**
 * Factorizes the specified multiple precision integer into its prime
 * factors and places in the given std vector, when returning true.
 * Alternatively, the algorithm decides it is not able to perform the
 * factorization and then returns false instead.
 */
bool fermat_squares::prime_factorize(mpz_class n, std::vector<mpz_class> & factors) {

    return false;
}

/**
 * Factorizes the specified multiple precision integer into a pair of
 * factors, when returning true. If returning false, then the
 * algorithm decided it was not able to perform the factorization.
 */
bool fermat_squares::factorize(mpz_class n, std::pair<mpz_class,mpz_class> & factors) {

    bool factors_found = false;
    mpz_class x, q_x, x_sqr, q_x_sqr;

    x = sqrt(n);

    return true; // TODO
}


/**
 * Calculates the function Q(x) = x^2 - n and sets q_x to this value.
 */
// TODO: should all these arguments be specified as references?
void fermat_squares::q(mpz_class & q_x, mpz_class x, mpz_class n) {
    q_x = sqrt(x) - n;
}

