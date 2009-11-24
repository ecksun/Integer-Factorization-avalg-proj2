#ifndef QUAD_SIEVE_H
#define QUAD_SIEVE_H

#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class quad_sieve {

    void q(mpz_t &, mpz_t, mpz_t);
    void generate_factor_base(std::vector<mpz_class> &, mpz_t);
    void find_b_smooth_numbers(mpz_t, std::vector< std::vector<int> > &, std::vector< std::vector<bool> > &,
            std::vector<mpz_class> &, std::vector<mpz_class> &, 
            const std::vector<mpz_class>, mpz_t);
    void select_b_smooth_numbers(std::vector<int> &, std::vector< std::vector<bool> > &);
    void sieve_interval_start(mpz_t, mpz_t, int);
    bool b_smooth(std::vector<int> &, std::vector<bool> &, mpz_t, const std::vector<mpz_class>);

        

    public:
    quad_sieve();
    ~quad_sieve();
    bool prime_factorize(mpz_t, std::vector<mpz_class> &);

};

#endif /* QUAD_SIEVE_H */
