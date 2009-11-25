#include <gmp.h>
#include <gmpxx.h>
#include <vector>

class trial_division {
    static int array[10000]; 
    public: 
    void factor(mpz_t, std::vector<mpz_class> &);
    trial_division();
    
};
