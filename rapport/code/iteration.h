#ifndef ITERATION_H
#define ITERATION_H

#include <gmp.h>

struct Mmn_t {
  mpz_t *M;
  mpz_t *m;
  mpz_t *n;
};

typedef struct Mmn_t Mmn_t;

Mmn_t *gen_Mmn(mpz_t *g, mpz_t *h, mpz_t *modulus, mpz_t *order);

void Mmn_clear(Mmn_t *Mmn);

void Mmn_free(Mmn_t *Mmn);

// Compute next values of x, a, b and update them directly
// Responsability to the caller to allocate and deallocate the memory.
// Returns 0 if the computation was a success, -1 otherwise.
int f(mpz_t *xi, mpz_t *ai, mpz_t *bi,
      mpz_t *g, mpz_t *h,
      mpz_t *modulus, mpz_t *order, Mmn_t *Mmn);

#endif /* ITERATION_H */
