#include <gmp.h>
#include <iostream>

int main() {
    mpz_t a;
    mpz_init(a);

    char string [32];
    while (scanf("%s", &string) != EOF) {
        mpz_set_str(a, string, 10);
        
        // Do the factorisation here
        
        std::cout << a << std::endl;
    }
}
