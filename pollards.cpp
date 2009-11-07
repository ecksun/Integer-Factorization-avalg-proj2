#include "pollards.h"
#include <iostream>
pollards::pollards(mpz_t * a) : n(a) {

}

bool pollards::run(mpz_t rop) {
    mpz_t x, y, tmp;
    mpz_init_set_ui(x, 2);
    mpz_init_set_ui(y, 2);
    mpz_init(tmp);
    mpz_set_ui(rop, 1);


    while (mpz_cmp_ui(rop, 1) == 0) {
        std::cerr << "while" << std::endl;
        f(x);
        f(y);
        f(y);
        std::cout << "x:" << x << std::endl;
        std::cout << "y:" << y << std::endl;
        std::cout << "rop:" << rop << std::endl;
        mpz_sub(tmp, x, y);
        mpz_abs(tmp, tmp);
        mpz_gcd(rop, tmp, *n);
        sleep(1);
    }
    if (rop == *n)
        return false;
    else
        return true;
}

void pollards::f(mpz_t x) {
    mpz_mul(x, x, x);
    mpz_add_ui(x, x, 4711);
    mpz_mod(x, x, *n);
}
