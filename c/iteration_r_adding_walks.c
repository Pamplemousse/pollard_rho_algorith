#include "iteration.h"

#include <stdlib.h>

#define R 20

/* R partitions, m correspond aux puissances de g,
   n à celles de h, M = g^m * h^n */

static Mmn_t *Mmn_alloc() {
  Mmn_t *Mmn = malloc(sizeof(Mmn_t));
  if (Mmn == NULL)
    return NULL;
  Mmn->M = malloc(R * sizeof(mpz_t));
  if (Mmn->M == NULL)
    return NULL;
  Mmn->m = malloc(R * sizeof(mpz_t));
  if (Mmn->m == NULL)
    return NULL;
  Mmn->n = malloc(R * sizeof(mpz_t));
  if (Mmn->n == NULL)
    return NULL;
  return Mmn;
}

void Mmn_clear(Mmn_t *Mmn) {
  for (int i = 0; i < R; i++) {
    mpz_clear(Mmn->M[i]);
    mpz_clear(Mmn->m[i]);
    mpz_clear(Mmn->n[i]);
  }
}

void Mmn_free(Mmn_t *Mmn) {
  free(Mmn->M);
  free(Mmn->m);
  free(Mmn->n);
  free(Mmn);
}

Mmn_t *gen_Mmn(mpz_t *g, mpz_t *h,
               mpz_t *modulus, mpz_t *order) {
  Mmn_t *Mmn = Mmn_alloc();
  if (Mmn == NULL)
    return NULL;

  mpz_t inter;
  mpz_init(inter);

  gmp_randstate_t state;
  gmp_randinit_mt(state);

  for (int i = 0; i < R; i++) {
    mpz_init(Mmn->M[i]);
    mpz_init(Mmn->m[i]);
    mpz_init(Mmn->n[i]);
    mpz_urandomm(Mmn->m[i], state, *order);
    mpz_urandomm(Mmn->n[i], state, *order);
    mpz_powm(Mmn->M[i], *g, Mmn->m[i], *modulus);
    mpz_powm(inter, *h, Mmn->n[i], *modulus);
    mpz_mul(Mmn->M[i], Mmn->M[i], inter);
  }

  gmp_randclear(state);
  mpz_clear(inter);

  return Mmn;
}

int f(mpz_t *xi, mpz_t *ai, mpz_t *bi, mpz_t *g,
      mpz_t *h, mpz_t *modulus, mpz_t *order, Mmn_t *Mmn) {

  if (!xi || !ai || !bi || !g || !h || !modulus || !order || !Mmn) { return -1; }

  mpz_t rop;
  mpz_init(rop);
  unsigned long int remainder = mpz_mod_ui(rop, *xi, R);

  mpz_mul(*xi, *xi, Mmn->M[remainder]);
  mpz_mod(*xi, *xi, *modulus);

  mpz_add(*ai, *ai, Mmn->m[remainder]);
  mpz_add(*bi, *bi, Mmn->n[remainder]);

  mpz_clear(rop);

  return 0;
}
