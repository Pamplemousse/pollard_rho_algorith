#include "collision.h"

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



void test_Floyd_with_handbook_values(void) {
  mpz_t order   ; mpz_init_set_d(order, 191);
  mpz_t modulus ; mpz_init_set_d(modulus, 383);
  mpz_t alpha   ; mpz_init_set_d(alpha, 2);
  mpz_t beta    ; mpz_init_set_d(beta, 228);

  mpz_t expected_ai, expected_bi, expected_Ai, expected_Bi;

  mpz_init_set_d(expected_ai, 12);
  mpz_init_set_d(expected_bi, 38);
  mpz_init_set_d(expected_Ai, 10);
  mpz_init_set_d(expected_Bi, 104);

  mpz_t result[4];

  for (unsigned int i = 0; i < 4; i++) {
    mpz_init(result[i]);
  }

  Floyd(&result, &alpha, &beta, &modulus, &order);

  ASSERT (mpz_cmp(&expected_ai, result[0]) == 0);
  ASSERT (mpz_cmp(&expected_bi, result[1]) == 0);
  ASSERT (mpz_cmp(&expected_Ai, result[2]) == 0);
  ASSERT (mpz_cmp(&expected_Bi, result[3]) == 0);

  for (unsigned int i = 0; i < 4; i++) {
    mpz_clear(result[i]);
  }

  mpz_clear(expected_ai);
  mpz_clear(expected_bi);
  mpz_clear(expected_Ai);
  mpz_clear(expected_Bi);

  mpz_clear(order);
  mpz_clear(modulus);
  mpz_clear(alpha);
  mpz_clear(beta);
}



int main (void) {
  DO_TEST (test_Floyd_with_handbook_values);

  return EXIT_SUCCESS;
}
