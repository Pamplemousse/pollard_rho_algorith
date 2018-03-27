#include "iteration.h"

#include <stdio.h>
#include <stdlib.h>


#define ASSERT(x) do {                                        \
  if (!(x)) {                                                 \
    fprintf (stderr, "\nAssertion: " #x " failed at %s:%d\n", \
        __FILE__, __LINE__);                                  \
    exit (EXIT_FAILURE);                                      \
  }                                                           \
} while (0)

#define ASSERT_FAIL(x) do {                                   \
  if (x) {                                                    \
    fprintf (stderr, "\nAssertion: " #x " passed at %s:%d\n", \
    __FILE__, __LINE__);                                      \
    exit (EXIT_FAILURE);                                      \
  }                                                           \
} while (0)

#define DO_TEST(t) do {         \
  printf ("Running " #t "..."); \
  fflush (stdout);              \
  t();                          \
  printf ("OK\n");              \
} while (0)


void test_returns_an_error_code_if_given_xi_is_null(void) {
  mpz_t ai, bi, g, h, modulus, order;
  Mmn_t *Mmn;
  int code = f(NULL, &ai, &bi, &g, &h, &modulus, &order, Mmn);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_ai_is_null(void) {
  mpz_t xi, bi, g, h, modulus, order;
  Mmn_t *Mmn;
  int code = f(&xi, NULL, &bi, &g, &h, &modulus, &order, Mmn);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_bi_is_null(void) {
  mpz_t xi, ai, g, h, modulus, order;
  Mmn_t *Mmn;
  int code = f(&xi, &ai, NULL, &g, &h, &modulus, &order, Mmn);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_g_is_null(void) {
  mpz_t xi, ai, bi, h, modulus, order;
  Mmn_t *Mmn;
  int code = f(&xi, &ai, &bi, NULL, &h, &modulus, &order, Mmn);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_h_is_null(void) {
  mpz_t xi, ai, bi, g, modulus, order;
  Mmn_t *Mmn;
  int code = f(&xi, &ai, &bi, &g, NULL, &modulus, &order, Mmn);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_modulus_is_null(void) {
  mpz_t xi, ai, bi, g, h, order;
  Mmn_t *Mmn;
  int code = f(&xi, &ai, &bi, &g, &h, NULL, &order, Mmn);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_order_is_null(void) {
  mpz_t xi, ai, bi, g, h, modulus;
  Mmn_t *Mmn;
  int code = f(&xi, &ai, &bi, &g, &h, &modulus, NULL, Mmn);
  ASSERT (code == -1);
}

void test_returns_an_error_code_if_given_Mmn_is_null(void) {
  mpz_t xi, ai, bi, g, h, modulus, order;
  int code = f(NULL, &ai, &bi, &g, &h, &modulus, &order, NULL);
  ASSERT (code == -1);
}

int main (void) {
  DO_TEST (test_returns_an_error_code_if_given_xi_is_null);
  DO_TEST (test_returns_an_error_code_if_given_ai_is_null);
  DO_TEST (test_returns_an_error_code_if_given_bi_is_null);
  DO_TEST (test_returns_an_error_code_if_given_g_is_null);
  DO_TEST (test_returns_an_error_code_if_given_h_is_null);
  DO_TEST (test_returns_an_error_code_if_given_modulus_is_null);
  DO_TEST (test_returns_an_error_code_if_given_order_is_null);
  DO_TEST (test_returns_an_error_code_if_given_Mmn_is_null);

  return EXIT_SUCCESS;
}
