#include "distinguished_points.h"

#include <stdlib.h>
#include <math.h>


size_t distinguished_points_index = 0;


size_t number_of_zeroes(mpz_t *order) {
  mpz_t sqrt_order;
  mpz_init(sqrt_order);
  mpz_sqrt(sqrt_order, *order);

  double sqrt_order_d;
  sqrt_order_d = mpz_get_d(sqrt_order);

  size_t number_of_zeroes;
  int tmp = ceil(log2(sqrt_order_d / NB_OF_POINTS));

  if (tmp <= 1) {
    /* Set a default: 1 over 2^2 = 4 numbers would be a distinguished point. */
    number_of_zeroes = 2;
  } else {
    number_of_zeroes = tmp;
  }

  mpz_clear(sqrt_order);
  return number_of_zeroes;
}


/* A number is a distinguished point if it ends with n zeroes */
bool is_distinguished_point (mpz_t *number, unsigned long int number_of_zeroes) {
  return mpz_scan1(*number, 0) == number_of_zeroes;
}


void init_distinguished_points(void) {
  for (size_t i = 0; i < NB_OF_POINTS; i++) {
    mpz_init(distinguished_points[i][0]);
    mpz_init(distinguished_points[i][1]);
    mpz_init(distinguished_points[i][2]);
  }
}


void clear_distinguished_points(void) {
  for (size_t i = 0; i < NB_OF_POINTS; i++) {
    mpz_clear(distinguished_points[i][0]);
    mpz_clear(distinguished_points[i][1]);
    mpz_clear(distinguished_points[i][2]);
  }
}


int is_in_list_of_distinguished_points(mpz_t *number, mpz_t *bi) {
  for (size_t i = 0; i < NB_OF_POINTS; i++) {
    if (mpz_cmp(*number, distinguished_points[i][0]) == 0
     && mpz_cmp(*bi, distinguished_points[i][2]) != 0) {
      return i;
    }
  }
  return -1;
}
