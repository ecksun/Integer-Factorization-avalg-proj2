#include <gmp.h>

class pollards {
    mpz_t * n;

    void f(mpz_t);

    public: 
    pollards(mpz_t *);
    bool run(mpz_t);

};
