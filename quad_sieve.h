#ifndef QUAD_SIEVE_H
#define QUAD_SIEVE_H

#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class quad_sieve {

    int factor_base_size;
    int factor_base[];

    void q(mpz_t & q_x, mpz_t x, mpz_t n);
    void setup_factor_base();

    public:
    explicit quad_sieve(const int);

    bool prime_factorize(mpz_t, std::vector<mpz_class> &);

};

#endif /* QUAD_SIEVE_H */
