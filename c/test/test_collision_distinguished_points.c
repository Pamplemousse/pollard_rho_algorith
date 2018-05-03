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



void test_(void) {
  mpz_t order   ; mpz_init_set_d(order, 191);
  mpz_t modulus ; mpz_init_set_d(modulus, 383);
  mpz_t g       ; mpz_init_set_d(g, 2);
  mpz_t h       ; mpz_init_set_d(h, 228);

  mpz_t result[4];

  for (unsigned int i = 0; i < 4; i++) {
    mpz_init(result[i]);
  }

  collision(&result, &g, &h, &modulus, &order);

  /* TODO: write some meaningful assertions */
  /* ASSERT(true); */

  for (unsigned int i = 0; i < 4; i++) {
    mpz_clear(result[i]);
  }

  mpz_clear(order);
  mpz_clear(modulus);
  mpz_clear(g);
  mpz_clear(h);
}



int main (void) {
  DO_TEST (test_);

  return EXIT_SUCCESS;
}
