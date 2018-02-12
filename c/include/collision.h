#ifndef COLLISION_H
#define COLLISION_H

#include <gmp.h>

// Compute values of a_i, a_2i, b_i and b_2i until x_i and x_2i are equal
// Then, set the corresponding values into the *result array given as parameter
// Allocation and deallocation is responsability of the caller
void Floyd (mpz_t *result,
            mpz_t alpha, mpz_t beta,
            mpz_t modulus, mpz_t order);

#endif /* COLLISION_H */
