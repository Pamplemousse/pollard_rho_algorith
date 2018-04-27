#include "collision.h"
#include "iteration.h"

#include <stdio.h>
#include <stdlib.h>


/* Compute values of a_i, a_2i, b_i and b_2i until x_i and x_2i are equal */
/* Then, set the corresponding values into the *result array given as parameter */
/* Allocation and deallocation is responsability of the caller */
void collision (mpz_t *result,
                mpz_t *g, mpz_t *h,
                mpz_t *modulus, mpz_t *order) {
  mpz_t xi, ai, bi, Xi, Ai, Bi;

  mpz_init_set_d(xi, 1);
  mpz_init_set_d(ai, 0);
  mpz_init_set_d(bi, 0);
  mpz_init_set_d(Xi, 1);
  mpz_init_set_d(Ai, 0);
  mpz_init_set_d(Bi, 0);

  mpz_t i;
  mpz_init_set_d(i, 0);

  Mmn_t *Mmn = gen_Mmn(g, h, modulus, order);

  while (1) {
    f(&xi, &ai, &bi, g, h, modulus, order, Mmn);

    f(&Xi, &Ai, &Bi, g, h, modulus, order, Mmn);
    f(&Xi, &Ai, &Bi, g, h, modulus, order, Mmn);

    mpz_add_ui(i, i, 1);
    if (mpz_cmp(i, *order) == 0) { break; }
    if ((mpz_cmp(xi, Xi) == 0) && (mpz_cmp(bi, Bi) != 0)) { break; }
  }

  mpz_clear(i);
  if (mpz_cmp(xi, Xi) != 0) {
      gmp_randstate_t state;
      gmp_randinit_mt(state);

      mpz_urandomm(ai, state, *order);
      mpz_urandomm(bi, state, *order);

      mpz_t inter_1, inter_2;
      mpz_init_set_d(inter_1, 1);
      mpz_init_set_d(inter_2, 1);

      mpz_powm(inter_1, *g, ai, *modulus);
      mpz_powm(inter_2, *h, bi, *modulus);

      mpz_mul(xi, inter_1, inter_2);

      mpz_set(Xi, xi);
      mpz_set(Ai, ai);
      mpz_set(Bi, bi);

      gmp_randclear(state);
      mpz_clear(inter_1); mpz_clear(inter_2);

      while (1) {
        f(&xi, &ai, &bi, g, h, modulus, order, Mmn);

        f(&Xi, &Ai, &Bi, g, h, modulus, order, Mmn);
        f(&Xi, &Ai, &Bi, g, h, modulus, order, Mmn);

        if (mpz_cmp(i, *order) == 0) { break; }
        if ((mpz_cmp(xi, Xi) == 0) && (mpz_cmp(bi, Bi) != 0)) { break; }
      }
    }

  mpz_set(result[0], ai);
  mpz_set(result[1], bi);
  mpz_set(result[2], Ai);
  mpz_set(result[3], Bi);

  mpz_clear(xi); mpz_clear(ai); mpz_clear(bi);
  mpz_clear(Xi); mpz_clear(Ai); mpz_clear(Bi);

  Mmn_clear(Mmn);
  Mmn_free(Mmn);
}
