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
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(NULL, &ai, &bi, &alpha, &beta, &modulus, &order);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_ai_is_null(void) {
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(&xi, NULL, &bi, &alpha, &beta, &modulus, &order);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_bi_is_null(void) {
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(&xi, &ai, NULL, &alpha, &beta, &modulus, &order);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_alpha_is_null(void) {
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(&xi, &ai, &bi, NULL, &beta, &modulus, &order);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_beta_is_null(void) {
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(&xi, &ai, &bi, &alpha, NULL, &modulus, &order);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_modulus_is_null(void) {
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(&xi, &ai, &bi, &alpha, &beta, NULL, &order);
  ASSERT (code == -1);
}


void test_returns_an_error_code_if_given_order_is_null(void) {
  mpz_t xi, ai, bi, alpha, beta, modulus, order;
  int code = f(&xi, &ai, &bi, &alpha, &beta, &modulus, NULL);
  ASSERT (code == -1);
}


void test_handbook_values(void) {
  mpz_t order   ; mpz_init_set_d(order, 191);
  mpz_t modulus ; mpz_init_set_d(modulus, 383);
  mpz_t alpha   ; mpz_init_set_d(alpha, 2);
  mpz_t beta    ; mpz_init_set_d(beta, 228);

  int expected_x[] = { 228, 279, 92, 184, 205, 14, 28, 256, 152, 304, 372, 121,
                       12, 144 };
  int expected_a[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 6, 6, 12 };
  int expected_b[] = { 1, 2, 4, 4, 5, 6, 6, 7, 8, 8, 9, 18, 19, 38 };

  /* Will hold all the expected values for x, a and b */
  mpz_t *expected_values = malloc(14 * 3 * sizeof(mpz_t));

  for (size_t i = 0; i < 14; i++) {
    size_t j = 3*i;
    mpz_init_set_d(expected_values[j], expected_x[i]);
    mpz_init_set_d(expected_values[j + 1], expected_a[i]);
    mpz_init_set_d(expected_values[j + 2], expected_b[i]);

    if (i > 0) {
      mpz_t xi, ai, bi;
      mpz_init(xi);
      mpz_init(ai);
      mpz_init(bi);

      /* x_i, a_i and b_i are set to the previously expected values  */
      mpz_set(xi, expected_values[j - 3]);
      mpz_set(ai, expected_values[j - 2]);
      mpz_set(bi, expected_values[j - 1]);

      f(&xi, &ai, &bi, &alpha, &beta, &modulus, &order);

      ASSERT (mpz_cmp(&xi, expected_values[j]) == 0);
      ASSERT (mpz_cmp(&ai, expected_values[j + 1]) == 0);
      ASSERT (mpz_cmp(&bi, expected_values[j + 2]) == 0);

      mpz_clear(xi);
      mpz_clear(ai);
      mpz_clear(bi);

    }
  }

  for (size_t i = 0; i < 14*3; i++) {
    mpz_clear(expected_values[i]);
  }
  free(expected_values);

  mpz_clear(order);
  mpz_clear(modulus);
  mpz_clear(alpha);
  mpz_clear(beta);
}



int main (void) {
  DO_TEST (test_returns_an_error_code_if_given_xi_is_null);
  DO_TEST (test_returns_an_error_code_if_given_ai_is_null);
  DO_TEST (test_returns_an_error_code_if_given_bi_is_null);
  DO_TEST (test_returns_an_error_code_if_given_alpha_is_null);
  DO_TEST (test_returns_an_error_code_if_given_beta_is_null);
  DO_TEST (test_returns_an_error_code_if_given_modulus_is_null);
  DO_TEST (test_returns_an_error_code_if_given_order_is_null);
  DO_TEST (test_handbook_values);

  return EXIT_SUCCESS;
}
