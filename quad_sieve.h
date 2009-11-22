#ifndef QUAD_SIEVE_H
#define QUAD_SIEVE_H

#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class quad_sieve {

    mpz_t * factor_base;

    void q(mpz_t &, mpz_t, mpz_t);
    void generate_factor_base(mpz_t);
    void find_b_smooth_numbers(mpz_t, int);
    void select_b_smooth_numbers(std::vector<int>);
    void sieve_interval_start(mpz_t, mpz_t);

    public:
    quad_sieve();
    ~quad_sieve();
    bool prime_factorize(mpz_t, std::vector<mpz_class> &);

};

#endif /* QUAD_SIEVE_H */
