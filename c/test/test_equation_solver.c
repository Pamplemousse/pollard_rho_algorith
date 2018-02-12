#include "equation_solver.h"

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



void test_discrete_log_from_exponents_returns_an_error_code_if_given_result_is_null(void) {
  mpz_t ai, bi, Ai, Bi, order;
  int code = discrete_log_from_exponents(NULL, &ai, &bi, &Ai, &Bi, &order);
  ASSERT (code == -1);
}


void test_discrete_log_from_exponents_returns_an_error_code_if_given_ai_is_null(void) {
  mpz_t result, bi, Ai, Bi, order;
  int code = discrete_log_from_exponents(&result, NULL, &bi, &Ai, &Bi, &order);
  ASSERT (code == -1);
}


void test_discrete_log_from_exponents_returns_an_error_code_if_given_bi_is_null(void) {
  mpz_t result, ai, Ai, Bi, order;
  int code = discrete_log_from_exponents(&result, &ai, NULL, &Ai, &Bi, &order);
  ASSERT (code == -1);
}


void test_discrete_log_from_exponents_returns_an_error_code_if_given_Ai_is_null(void) {
  mpz_t result, ai, bi, Bi, order;
  int code = discrete_log_from_exponents(&result, &ai, &bi, NULL, &Bi, &order);
  ASSERT (code == -1);
}


void test_discrete_log_from_exponents_returns_an_error_code_if_given_Bi_is_null(void) {
  mpz_t result, ai, bi, Ai, order;
  int code = discrete_log_from_exponents(&result, &ai, &bi, &Ai, NULL, &order);
  ASSERT (code == -1);
}


void test_discrete_log_from_exponents_returns_an_error_code_if_given_order_is_null(void) {
  mpz_t result, ai, bi, Ai, Bi;
  int code = discrete_log_from_exponents(&result, &ai, &bi, &Ai, &Bi, NULL);
  ASSERT (code == -1);
}


void test_discrete_log_from_exponents_with_handbook_values(void) {
  mpz_t ai    ; mpz_init_set_d(ai, 12);
  mpz_t bi    ; mpz_init_set_d(bi, 38);
  mpz_t Ai    ; mpz_init_set_d(Ai, 10);
  mpz_t Bi    ; mpz_init_set_d(Bi, 104);
  mpz_t order ; mpz_init_set_d(order, 191);

  mpz_t result;
  mpz_init(result);

  discrete_log_from_exponents(&result, &ai, &bi, &Ai, &Bi, &order);

  ASSERT (mpz_cmp_d(result, 110) == 0);

  mpz_clear(ai); mpz_clear(bi);
  mpz_clear(Ai); mpz_clear(Bi);
  mpz_clear(order);
  mpz_clear(result);
}



int main (void) {
  DO_TEST (test_discrete_log_from_exponents_returns_an_error_code_if_given_result_is_null);
  DO_TEST (test_discrete_log_from_exponents_returns_an_error_code_if_given_ai_is_null);
  DO_TEST (test_discrete_log_from_exponents_returns_an_error_code_if_given_bi_is_null);
  DO_TEST (test_discrete_log_from_exponents_returns_an_error_code_if_given_Ai_is_null);
  DO_TEST (test_discrete_log_from_exponents_returns_an_error_code_if_given_Bi_is_null);
  DO_TEST (test_discrete_log_from_exponents_returns_an_error_code_if_given_order_is_null);

  DO_TEST (test_discrete_log_from_exponents_with_handbook_values);

  return EXIT_SUCCESS;
}
