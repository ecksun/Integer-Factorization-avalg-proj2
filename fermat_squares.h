#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <utility>

class fermat_squares {

    static void q(mpz_class & q_x, mpz_class x, mpz_class n);

    public:
        static bool prime_factorize(mpz_class, std::vector<mpz_class> &);
        static bool factorize(mpz_class, std::pair<mpz_class,mpz_class> &);

};
