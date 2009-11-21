#include "fermat_squares.h"
#include <iostream>

/**
 * Factorizes the specified multiple precision integer into its prime
 * factors and places in the given std vector, when returning true.
 * Alternatively, the algorithm decides it is not able to perform the
 * factorization and then returns false instead.
 */
bool fermat_squares::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    std::pair<mpz_class,mpz_class> factors_pair;

    fermat_squares::factorize(n, factors_pair);

    factors.push_back(factors_pair.first);
    factors.push_back(factors_pair.second);

    return false;
}

/**
 * Factorizes the specified multiple precision integer into a pair of
 * factors, when returning true. If returning false, then the
 * algorithm decided it was not able to perform the factorization.
 */
bool fermat_squares::factorize(mpz_t n, std::pair<mpz_class,mpz_class> & factors) {

    bool factors_found = false;
    mpz_t x;
    mpz_init(x);
    mpz_sqrt(x, n); // sqrt(n)

    // setup storage for Q(x)
    mpz_t q_x; mpz_init(q_x); 

    // setup storage for sqrt(Q(x))
    mpz_t q_x_sqrt; mpz_init(q_x_sqrt); 

    while (!factors_found) {
        q(q_x, x, n);  // Q(x)

        std::cout << "x: " << x << ", Q(x): " << q_x << std::endl;

        if (mpz_perfect_square_p(q_x)) { // Q(x) is perfect square
            // calculate sqrt(Q(x)) and remainder
            mpz_sqrt(q_x_sqrt, q_x);

            // wrap sqrt(Q(x)) in a class
            mpz_class q_x_sqrt_cls(q_x_sqrt);

            // store in factors pair
            factors.first = mpz_class(x) - q_x_sqrt_cls; // x - sqrt(Q(x))
            factors.second = mpz_class(x) + q_x_sqrt_cls; // x + sqrt(Q(x))

            factors_found = true;
        } else {
            mpz_add_ui(x, x, 1); // increment x
        }
    }

    return factors_found; 
}


/**
 * Calculates the function Q(x) = x^2 - n.
 */
void fermat_squares::q(mpz_t & q_x, mpz_t x, mpz_t n) {
    mpz_class x_sq_cls;
    mpz_pow_ui(x_sq_cls.get_mpz_t(), x, 2);

    // Q(x)
    mpz_class q_x_cls; // init
    q_x_cls = x_sq_cls - mpz_class(n); // calc

    // set for return
    mpz_set(q_x, q_x_cls.get_mpz_t());
}

