#include "quad_sieve.h"
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

const int FACTOR_BASE_SIZE = 150;
const int ADDITIONAL_B_SMOOTH_NUMBERS = 1;

const int MT_ROWS = FACTOR_BASE_SIZE;
const int MT_COLS = FACTOR_BASE_SIZE + ADDITIONAL_B_SMOOTH_NUMBERS;

/**
 * Constructs a new Quadratic Siever.
 */
quad_sieve::quad_sieve() {
}

/**
 * Destructs this Quadratic Siever.
 */
quad_sieve::~quad_sieve() {
}

/**
 * Performs the prime factorization.
 *
 * @param n The integral number to factorize
 * @param factors A placeholder for the factors found, if any
 */
bool quad_sieve::prime_factorize(mpz_t n, std::vector<mpz_class> & factors) {

    std::vector<mpz_class> B;
    generate_factor_base(B, n);


    mpz_t x;
    mpz_init(x);
    sieve_interval_start(x, n, 0);


    std::vector<mpz_class> xs(MT_COLS), ys(MT_COLS);
    std::vector< std::vector<int> > exps;
    std::vector< std::vector<bool> > m2_exps;
    find_b_smooth_numbers(x, exps, m2_exps, xs, ys, B, n);


    gauss_eliminate(m2_exps);




    
    // try the different lnr_comb:s found above
    

    return true;
}

/**
 * Computes Q(x) = x^2 - n and stores the result in y.
 *
 * @param y Placeholder for the result
 * @param x The x to calculate Q(x) from
 * @param n The integral number that are being factorized
 */
void quad_sieve::q(mpz_t & y, mpz_t x, mpz_t n) {

    // http://en.wikipedia.org/wiki/Quadratic_sieve
    // ta mod_n istället för sub n?

    mpz_t x_sq;
    mpz_init(x_sq);
    mpz_mul(x_sq, x, x);
    mpz_sub(y, x_sq, n);

}

/**
 * Generates the factor base for the specified integer to factorize.
 *
 * @param n The integer that will be factorized
 */
void quad_sieve::generate_factor_base(std::vector<mpz_class> & B, mpz_t n) {
    mpz_t p;
    mpz_init_set_ui(p, 2);
    B.push_back(mpz_class(p));

    int i = 1;
    while (i < FACTOR_BASE_SIZE) {
        mpz_nextprime(p, p);

        if (mpz_legendre(n, p) == 1) {
            B.push_back(mpz_class(p));
            i++;
        }

    }

    mpz_clear(p);
}

/**
 * Finds the specified number of B-smooth numbers, that is, numbers
 * that can be fully factorized by the prime factors in B.
 */
void quad_sieve::find_b_smooth_numbers(
        mpz_t x, std::vector< std::vector<int> > & exps, std::vector< std::vector<bool> > & m2_exps, 
        std::vector<mpz_class> & xs, std::vector<mpz_class> & ys, 
        const std::vector<mpz_class> B, mpz_t n) {

    int found_numbers = 0;

    mpz_t y;
    mpz_init(y);

    while (found_numbers < MT_COLS) {

        q(y, x, n);

        std::vector<int> exp_vec(MT_COLS);
        std::vector<bool> m2_exp_vec(MT_COLS);

        // TODO: fix so that negative numbers are allowed
        if (mpz_sgn(y) == 1 && b_smooth(exp_vec, m2_exp_vec, y, B)) {

            xs.push_back(mpz_class(x));
            ys.push_back(mpz_class(y));

            exps.push_back(exp_vec);
            m2_exps.push_back(m2_exp_vec);

            found_numbers++;

        }

        mpz_add_ui(x, x, 1);
        
    }

    mpz_clear(y);

}

/**
 * Checks whether the specified number y is B-smooth or not. If so, 
 * return true and set all corresponding result placeholders.
 * Otherwise, return false.
 */
bool quad_sieve::b_smooth(std::vector<int> & expv, std::vector<bool> & m2_expv, 
        mpz_t y_, const std::vector<mpz_class> B) {

    mpz_t y;
    mpz_init_set(y, y_);

    for (int i = 0; i < B.size(); i++) {
        expv[i] = 0;
        m2_expv[i] = 0;

        mpz_class p = B[i];

        while (mpz_divisible_p(y, p.get_mpz_t())) {

            mpz_divexact(y, y, p.get_mpz_t());
            expv[i] = expv[i] + 1;
            m2_expv[i] = m2_expv[i] ^ 1;

        }
    }

    return mpz_cmp_ui(y, 1) == 0;  // mpz_cmp_ui(1, 1) == 0
}

/**
 * Performs gauss elimination on the transpose of the specified 
 * matrix.
 */
void quad_sieve::gauss_eliminate(std::vector< std::vector<bool> > & M) {

    // the matrix M is not physically transposed into M^T due to the associated cost
    // therefore it has to be virtually transposed, meaning all accesses are a bit confusing
    // M^T[i][j] == M[j][i]

    // for each column in M^T
    for (int piv_col = 0; piv_col < MT_COLS; piv_col++) {

        // find pivot row (and thereby pivot element)
        int piv_row = -1;

        for (int row = 0; row < MT_ROWS; row++) {

            // use first row with '1' in pivot column that occurs
            // AND that has '0' on all positions to the left
            if (M[piv_col][row]) {

                bool leading_one = true;

                for (int i = 0; i < piv_col; i++) {
                    if (M[i][row]) {
                        leading_one = false; 
                        break; // no need to look for more one's
                    }
                }

                if (leading_one) {
                    piv_row = row;
                    break; // found pivot row
                }

            }

        }

        // if no pivot row found, continue with next pivot column
        if (piv_row == -1) {
            continue;
        }

        // make sure all other rows get a '0' in the current pivot column
        // obviously, all rows before piv_row did already have a '0' in piv_col
        for (int row = 0; row < MT_ROWS; row++) {

            // needs xor (on whole row)
            if (M[piv_col][row] && row != piv_row) {
                // todo: optimize by performing bitwise xor on ints
                for (int col = 0; col < MT_COLS; col++) {
                    M[col][row] = M[col][row] ^ M[col][piv_row];
                }
            }

        }

    }

}

/**
 * Finds the first number in the sieve interval to try out.
 *
 * @param x Result placeholder
 * @param n The integral number to factorize
 * @param M Parameter deciding the sieving interval
 * @return The first number of the sieve interval
 */
void quad_sieve::sieve_interval_start(mpz_t x, mpz_t n, int M) {
    mpz_sqrt(x, n);
    mpz_sub_ui(x, x, M);
}
