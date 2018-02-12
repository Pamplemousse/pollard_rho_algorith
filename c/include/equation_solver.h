#ifndef EQUATION_SOLVER_H
#define EQUATION_SOLVER_H

#include <gmp.h>

// Compute the discrete log corresponding to the following relation
// (Ai - ai) * (bi - Bi)^-1 mod order
// and set it to the *result given as parameter
// Responsability to the caller to allocate and deallocate the memory
int discrete_log_from_exponents(mpz_t *result,
                                mpz_t *ai, mpz_t *bi,
                                mpz_t *Ai, mpz_t *Bi,
                                mpz_t *order);

#endif /* EQUATION_SOLVER_H */
