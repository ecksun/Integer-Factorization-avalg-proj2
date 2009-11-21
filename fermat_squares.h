#ifndef FERMAT_SQUARES_H
#define FERMAT_SQUARES_H

#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class fermat_squares {

    inline static bool is_prime(mpz_t);
    inline static bool is_prime(mpz_class);
    static void q(mpz_t & q_x, mpz_t x, mpz_t n);
    static bool factorize(mpz_t, std::vector<mpz_class> &);
    static bool save_and_recurse(mpz_class, mpz_class, std::vector<mpz_class> &);

    public:
        static bool prime_factorize(mpz_t, std::vector<mpz_class> &);

};

#endif /* FERMAT_SQUARES_H */
