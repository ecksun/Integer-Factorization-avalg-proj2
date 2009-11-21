#include "fermat_squares.h"
#include <iostream>
#define prime_test_reps 5

/**
 * Factorizes the specified multiple precision integer into a pair of
 * factors. Then recurses and adds the prime factors to the given
 * vector in the end.
 */
bool fermat_squares::factorize(mpz_t n, std::vector<mpz_class> & factors) {

    // first we factorize all 2's in order to get the required odd composite
    while (mpz_even_p(n)) {
        factors.push_back(mpz_class(2));
        mpz_divexact_ui(n, n, 2); // TODO: optimize by performing a right shift
    }

    bool factors_found = false;

    if (is_prime(n)) {
        factors.push_back(mpz_class(n));
        return true;
    }

    mpz_t x; mpz_init(x);
    mpz_sqrt(x, n); // x <-- sqrt(n)

    // setup storage for Q(x) and sqrt(Q(x))
    mpz_t q_x; mpz_init(q_x); 
    mpz_t q_x_sqrt; mpz_init(q_x_sqrt); 

    while (!factors_found) {
        q(q_x, x, n);  // Q(x)

//        std::cout << "x: " << x << ", Q(x): " << q_x << std::endl;

        if (mpz_perfect_square_p(q_x)) { // Q(x) is perfect square

            mpz_sqrt(q_x_sqrt, q_x); // sqrt(Q(x))
            mpz_class q_x_sqrt_cls(q_x_sqrt); // wrap sqrt(Q(x))

            // store factors in first and second, wrapped in mpz_class
            mpz_class fst_cls, snd_cls;
            fst_cls = mpz_class(x) - q_x_sqrt_cls; // x - sqrt(Q(x))
            snd_cls = mpz_class(x) + q_x_sqrt_cls; // x + sqrt(Q(x))

            factors_found = true;

            // BEGIN [STORE AND RECURSE PART]
             
            // first factor
            if (is_prime(fst_cls)) {
                factors.push_back(fst_cls);
            } else {
                factorize(fst_cls.get_mpz_t(), factors);
            }

            // second factor
            if (is_prime(snd_cls)) {
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

bool fermat_squares::is_prime(mpz_t number) {
    return mpz_probab_prime_p(number, prime_test_reps);
}

bool fermat_squares::is_prime(mpz_class number) {
    return mpz_probab_prime_p(number.get_mpz_t(), prime_test_reps);
}
