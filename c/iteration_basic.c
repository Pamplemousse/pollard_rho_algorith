#include "iteration.h"


Mmn_t *gen_Mmn(mpz_t *g, mpz_t *h,
               mpz_t *modulus, mpz_t *order) { return NULL; }

void Mmn_clear(Mmn_t *Mmn) {}

void Mmn_free(Mmn_t *Mmn) {}

int f(mpz_t *xi, mpz_t *ai, mpz_t *bi,
      mpz_t *g, mpz_t *h,
      mpz_t *modulus, mpz_t *order, Mmn_t *Mmn) {

  if (!xi || !ai || !bi || !g || !h || !modulus || !order) { return -1; }

  mpz_t remainder;
  mpz_init(remainder);
  mpz_mod_ui(remainder, *xi, 3);

  if (mpz_cmp_ui(remainder, 1) == 0) {
    mpz_mul(*xi, *h, *xi);
    mpz_mod(*xi, *xi, *modulus);

    /* ai stays the same */

    mpz_add_ui(*bi, *bi, 1);
    mpz_mod(*bi, *bi, *order);

  } else if (mpz_cmp_si(remainder, 0) == 0) {
    mpz_mul(*xi, *xi, *xi);
    mpz_mod(*xi, *xi, *modulus);

    mpz_mul_ui(*ai, *ai, 2);
    mpz_mod(*ai, *ai, *order);

    mpz_mul_ui(*bi, *bi, 2);
    mpz_mod(*bi, *bi, *order);

  } else {
    mpz_mul(*xi, *g, *xi);
    mpz_mod(*xi, *xi, *modulus);

    mpz_add_ui(*ai, *ai, 1);
    mpz_mod(*ai, *ai, *order);

    /* bi stays the same */
  }

  mpz_clear(remainder);

  return 0;
}
