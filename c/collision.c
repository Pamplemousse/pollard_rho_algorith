#include "collision.h"
#include "iteration.h"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>


void Floyd (mpz_t *result, mpz_t alpha, mpz_t beta, mpz_t modulus, mpz_t order) {
  mpz_t xi, ai, bi, Xi, Ai, Bi;

  mpz_init_set_d(xi, 1);
  mpz_init_set_d(ai, 0);
  mpz_init_set_d(bi, 0);
  mpz_init_set_d(Xi, 1);
  mpz_init_set_d(Ai, 0);
  mpz_init_set_d(Bi, 0);

  while (1) {
    f(&xi, &ai, &bi, alpha, beta, modulus, order);

    f(&Xi, &Ai, &Bi, alpha, beta, modulus, order);
    f(&Xi, &Ai, &Bi, alpha, beta, modulus, order);
 
    if (mpz_cmp(xi, Xi) == 0)
      break;
  }

  mpz_set(result[0], ai);
  mpz_set(result[1], bi);
  mpz_set(result[2], Ai);
  mpz_set(result[3], Bi);

  mpz_clear(xi);
  mpz_clear(ai);
  mpz_clear(bi);
  mpz_clear(Xi);
  mpz_clear(Ai);
  mpz_clear(Bi);

}
