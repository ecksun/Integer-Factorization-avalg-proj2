#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class trial_division {
    const static int divisors = 256;

    public: 
    void factor(mpz_t, std::vector<mpz_class> &);
    trial_division();
    
};
