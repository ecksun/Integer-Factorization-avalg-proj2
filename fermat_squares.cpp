#ifndef FERMAT_SQUARES_H
#define FERMAT_SQUARES_H

#include "fermat_squares.h"
#include <iostream>
#define prime_test_reps 5
#define max_bit_size 88
#define max_iterations 100000


/**
 * First factorizes all 2's before running the algorithm, in order to
 * get the required odd composite.
 */
bool fermat_squares::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    if (mpz_sizeinbase(n, 2) >= max_bit_size) {
        return false;
    }

    while (mpz_even_p(n)) {
        factors.push_back(mpz_class(2));
        mpz_divexact_ui(n, n, 2); // TODO: optimize by performing a right shift
    }

    return factorize(n, factors);
}

/**
 * Factorizes the specified multiple precision integer into a pair of
 * factors. Then recurses and adds the prime factors to the given
 * vector in the end.
 */
bool fermat_squares::factorize(mpz_t n, std::vector<mpz_class> & factors) {

    if (is_prime(n)) {
        mpz_class tmp(n);
        factors.push_back(tmp);
        return true;
    }

    mpz_t x; mpz_init(x);
    mpz_sqrt(x, n); // x <-- sqrt(n)

    // setup storage for Q(x) and sqrt(Q(x))
    mpz_t q_x; mpz_init(q_x); 
    mpz_t q_x_sqrt; mpz_init(q_x_sqrt); 

    bool factors_found = false;
    unsigned int iterations = 0;


    while (!factors_found && iterations++ < max_iterations) {
        q(q_x, x, n);  // Q(x)

//        std::cerr << "x: " << x << ", Q(x): " << q_x << std::endl;

        if (mpz_perfect_square_p(q_x)) { // Q(x) is perfect square

//            std::cerr << "Perfect square: " << q_x << std::endl;

            mpz_sqrt(q_x_sqrt, q_x); // sqrt(Q(x))
            mpz_class q_x_sqrt_cls(q_x_sqrt); // wrap sqrt(Q(x))

            // store factors in first and second, wrapped in mpz_class
            mpz_class fst_cls, snd_cls;
            fst_cls = mpz_class(x) - q_x_sqrt_cls; // x - sqrt(Q(x))
            snd_cls = mpz_class(x) + q_x_sqrt_cls; // x + sqrt(Q(x))

            factors_found = true;

            // BEGIN [STORE AND RECURSE PART]

            bool first = true, second = true;

            // first factor
            if (is_prime(fst_cls)) {
                factors.push_back(fst_cls);
            } else {
                first = factorize(fst_cls.get_mpz_t(), factors);
            }

            // second factor
            if (is_prime(snd_cls)) {
                factors.push_back(snd_cls);
            } else {
                second = factorize(snd_cls.get_mpz_t(), factors);
            }

            return first && second;
            // END [STORE AND RECURSE PART]

        } else {
            mpz_add_ui(x, x, 1); // increment x
        }
    }

    mpz_clear(x);
    mpz_clear(q_x_sqrt);

    return factors_found; 
}

/**
 * Calculates the function Q(x) = x^2 - n.
 */
void fermat_squares::q(mpz_t & q_x, mpz_t x, mpz_t n) {
    // x^2
    mpz_t x_sq; mpz_init(x_sq);
    mpz_mul(x_sq, x, x);

    // Q(x) = x^2 - n
    mpz_sub(q_x, x_sq, n);

    mpz_clear(x_sq);
}

bool fermat_squares::is_prime(mpz_t number) {
    return mpz_probab_prime_p(number, prime_test_reps);
}

bool fermat_squares::is_prime(mpz_class number) {
    return mpz_probab_prime_p(number.get_mpz_t(), prime_test_reps);
}

#endif /* FERMAT_SQUARES_H */
