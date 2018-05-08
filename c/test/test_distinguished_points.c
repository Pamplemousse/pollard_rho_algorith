#include "distinguished_points.h"

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
  t();                          \
  printf ("OK\n");              \
} while (0)


void test_is_distinguished_point_if_it_ends_with_the_right_number_of_zeroes(void) {
  mpz_t number1, number2, number3;
  mpz_init_set_d(number1, 0b1000);
  mpz_init_set_d(number2, 0b10000);
  mpz_init_set_d(number3, 0b100000);

  ASSERT(is_distinguished_point(&number1, 3));
  ASSERT(is_distinguished_point(&number2, 4));
  ASSERT(is_distinguished_point(&number3, 5));

  mpz_clear(number1);
  mpz_clear(number2);
  mpz_clear(number3);
}


void test_is_not_distinguished_point_if_it_ends_with_the_wrong_number_of_zeroes(void) {
  mpz_t number1, number2, number3;
  mpz_init_set_d(number1, 0b1100);
  mpz_init_set_d(number2, 0b11000);
  mpz_init_set_d(number3, 0b110000);

  ASSERT(!is_distinguished_point(&number1, 3));
  ASSERT(!is_distinguished_point(&number2, 4));
  ASSERT(!is_distinguished_point(&number3, 5));

  mpz_clear(number1);
  mpz_clear(number2);
  mpz_clear(number3);
}


/* Beware:
 * Number of zeroes is dynamically calculated in function of the order
 * BUT it relies on a constant defined in distinguished_point.c as well */
void test_number_of_zeroes(void) {
  unsigned long int inputs[] = {
    0b11011001111011110001,
    0b11101110000000101111111,
    0b1101100110101001101011000001110001010001
  };
  size_t results[] = { 2, 2, 4 };
  mpz_t order;

  for (size_t i = 0; i < 3; i++) {
    mpz_init_set_d(order, inputs[i]);
    ASSERT(number_of_zeroes(order) == results[i]);
    mpz_clear(order);
  }
}


void test_initialize_array_of_found_distinguished_points_with_zeroes(void) {
  init_distinguished_points();

  for (size_t i = 0; i < NB_OF_POINTS; i++) {
    mpz_t *point = distinguished_points[i];

    ASSERT (mpz_cmp_d(point[0], 0) == 0);
    ASSERT (mpz_cmp_d(point[1], 0) == 0);
    ASSERT (mpz_cmp_d(point[2], 0) == 0);

    mpz_clear(point[0]);
    mpz_clear(point[1]);
    mpz_clear(point[2]);
  }
}


void test_is_in_list_returns_index_if_number_is_in_list_of_DP(void) {
  init_distinguished_points();
  mpz_t number1, number2, number3, bi;
  mpz_init_set_d(number1, 1);
  mpz_init_set_d(number2, 42);
  mpz_init_set_d(number3, 100);
  mpz_init_set_d(bi, 1);

  mpz_set(distinguished_points[0][0], number1);
  mpz_set(distinguished_points[4][0], number2);
  mpz_set(distinguished_points[8][0], number3);

  ASSERT (is_in_list_of_distinguished_points(&number1, &bi) == 0);
  ASSERT (is_in_list_of_distinguished_points(&number2, &bi) == 4);
  ASSERT (is_in_list_of_distinguished_points(&number3, &bi) == 8);

  mpz_clear(number1);
  mpz_clear(number2);
  mpz_clear(number3);
  clear_distinguished_points();
}


void test_is_in_list_returns_minus_1_if_number_is_in_list_of_DP_but_exponents_are_the_same(void) {
  init_distinguished_points();
  mpz_t x, a, b;
  mpz_init_set_d(x, 1);
  mpz_init_set_d(a, 42);
  mpz_init_set_d(b, 100);

  mpz_set(distinguished_points[0][0], x);
  mpz_set(distinguished_points[0][1], a);
  mpz_set(distinguished_points[0][2], b);

  ASSERT (is_in_list_of_distinguished_points(&x, &b) == -1);

  mpz_clear(x);
  mpz_clear(a);
  mpz_clear(b);
  clear_distinguished_points();
}


void test_is_in_list_returns_minus_1_if_number_is_NOT_in_list_of_DP(void) {
  init_distinguished_points();
  mpz_t number1, number2, number3, bi;
  mpz_init_set_d(number1, 1);
  mpz_init_set_d(number2, 42);
  mpz_init_set_d(number3, 100);
  mpz_init_set_d(bi, 1);

  ASSERT (is_in_list_of_distinguished_points(&number1, &bi) == -1);
  ASSERT (is_in_list_of_distinguished_points(&number2, &bi) == -1);
  ASSERT (is_in_list_of_distinguished_points(&number3, &bi) == -1);

  mpz_clear(number1);
  mpz_clear(number2);
  mpz_clear(number3);
  clear_distinguished_points();
}


int main (void) {
  DO_TEST (test_is_distinguished_point_if_it_ends_with_the_right_number_of_zeroes);
  DO_TEST (test_is_not_distinguished_point_if_it_ends_with_the_wrong_number_of_zeroes);
  DO_TEST (test_number_of_zeroes);
  DO_TEST (test_initialize_array_of_found_distinguished_points_with_zeroes);
  DO_TEST (test_is_in_list_returns_index_if_number_is_in_list_of_DP);
  DO_TEST (test_is_in_list_returns_minus_1_if_number_is_in_list_of_DP_but_exponents_are_the_same);
  DO_TEST (test_is_in_list_returns_minus_1_if_number_is_NOT_in_list_of_DP);

  return EXIT_SUCCESS;
}
