#include "fermat_squares.h"
#include <iostream>
#define prime_test_reps 5

/**
 * Factorizes the specified multiple precision integer into its prime
 * factors and places in the given std vector, when returning true.
 * Alternatively, the algorithm decides it is not able to perform the
 * factorization and then returns false instead.
 *
bool fermat_squares::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    std::pair<mpz_class,mpz_class> factors_pair;
    factorize(n, factors_pair);
    // TODO: problem med överskrivning av factors_pair?
    
    mpz_t first;
    mpz_init_set(first, factors_pair.first.get_mpz_t());

    // store/recurse first factor
    if (mpz_probab_prime_p(first, prime_test_reps)) {
        factors.push_back(factors_pair.first);
    } else {
        prime_factorize(first, factors);
    }

    mpz_t second;
    mpz_init_set(second, factors_pair.second.get_mpz_t());

    // store/recurse second factor
    if (mpz_probab_prime_p(second, prime_test_reps)) {
        if (mpz_cmp(first, second)) {
            factors.push_back(factors_pair.second);
        }
    } else {
        prime_factorize(second, factors);
    }

    return true;
}
*/

/**
 * Factorizes the specified multiple precision integer into a pair of
 * factors. Then recurses and adds the prime factors to the given
 * vector in the end.
 */
bool fermat_squares::factorize(mpz_t n, std::vector<mpz_class> & factors) {

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

            // store in first and second factors
            mpz_class fst_cls, snd_cls;
            fst_cls = mpz_class(x) - q_x_sqrt_cls; // x - sqrt(Q(x))
            snd_cls = mpz_class(x) + q_x_sqrt_cls; // x + sqrt(Q(x))

            factors_found = true;

            // BEGIN [STORE AND RECURSE PART]
             
            // first factor
            if (mpz_probab_prime_p(fst_cls.get_mpz_t(), prime_test_reps)) {
                factors.push_back(fst_cls);
            } else {
                factorize(fst_cls.get_mpz_t(), factors);
            }

            // second factor
            if (mpz_probab_prime_p(snd_cls.get_mpz_t(), prime_test_reps)) {
                factors.push_back(snd_cls);
            } else {
                factorize(snd_cls.get_mpz_t(), factors);
            }

            // END [STORE AND RECURSE PART]

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
    mpz_mul(x_sq_cls.get_mpz_t(), x, x);

    // Q(x)
    mpz_class q_x_cls; // init
    q_x_cls = x_sq_cls - mpz_class(n); // calc

    // set for return
    mpz_set(q_x, q_x_cls.get_mpz_t());
}

