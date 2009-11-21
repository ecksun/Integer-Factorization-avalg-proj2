#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <utility>

class fermat_squares {

    static void q(mpz_t & q_x, mpz_t x, mpz_t n);

    public:
        static bool prime_factorize(mpz_t, std::vector<mpz_class> &);
        static bool factorize(mpz_t, std::pair<mpz_class,mpz_class> &);

};
