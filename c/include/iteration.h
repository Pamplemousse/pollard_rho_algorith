#ifndef ITERATION_H
#define ITERATION_H

#include <gmp.h>

// Compute next values of x, a, b and update them directly
// Responsability to the caller to allocate and deallocate the memory.
// Returns 0 if the computation was a success, -1 otherwise.
int f(mpz_t *xi, mpz_t *ai, mpz_t *bi,
      mpz_t *g, mpz_t *h,
      mpz_t *modulus, mpz_t *order);

#endif /* ITERATION_H */
