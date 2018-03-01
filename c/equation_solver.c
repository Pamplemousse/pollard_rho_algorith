#include "equation_solver.h"

#include <stdio.h>
#include <stdlib.h>


int discrete_log_from_exponents(mpz_t *result,
                                mpz_t *ai, mpz_t *bi,
                                mpz_t *Ai, mpz_t *Bi,
                                mpz_t *order) {

  // (Ai - ai) * (bi - Bi)^-1 mod order

  if (!result || !ai || !bi || !Ai || !Bi || !order ) { return -1; }

  mpz_t Ai_minus_ai, bi_minus_Bi;
  mpz_init(Ai_minus_ai);
  mpz_init(bi_minus_Bi);

  mpz_sub(Ai_minus_ai, *Ai, *ai);
  mpz_sub(bi_minus_Bi, *bi, *Bi);

  /* Bezout's identity:
   *   order * u + (bi - Bi) * bi_minus_Bi_invert = gcd
   * (we do not care about `u`) */
  mpz_t gcd, bi_minus_Bi_invert;
  mpz_init(gcd);
  mpz_init(bi_minus_Bi_invert);
  mpz_gcdext(gcd, NULL, bi_minus_Bi_invert, *order, bi_minus_Bi);

  mpz_mul(*result, Ai_minus_ai, bi_minus_Bi_invert);
  mpz_mod(*result, *result, *order);

  mpz_clear(gcd);
  mpz_clear(Ai_minus_ai);
  mpz_clear(bi_minus_Bi);
  mpz_clear(bi_minus_Bi_invert);

  return 0;
}
