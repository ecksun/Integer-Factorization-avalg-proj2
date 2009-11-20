#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class pollards {
    static void f(mpz_t, mpz_t);

    public: 
    static bool factor(mpz_t, std::vector<mpz_class> &);
    static bool factor(mpz_t, std::vector<mpz_class> &, int);
    
};
