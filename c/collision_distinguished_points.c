#include "collision.h"
#include "distinguished_points.h"
#include "iteration.h"

#include <stdio.h>
#include <stdlib.h>


static void generate_starting_point(gmp_randstate_t *state,
                                    mpz_t *xi, mpz_t *ai, mpz_t *bi,
                                    mpz_t *g, mpz_t *h,
                                    mpz_t *modulus, mpz_t *order) {
  mpz_urandomm(*ai, *state, *order);
  mpz_urandomm(*bi, *state, *order);

  mpz_t inter_1, inter_2;
  mpz_init(inter_1);
  mpz_init(inter_2);

  mpz_powm(inter_1, *g, *ai, *modulus);
  mpz_powm(inter_2, *h, *bi, *modulus);

  mpz_mul(*xi, inter_1, inter_2);
  mpz_mod(*xi, *xi, *modulus);

  mpz_clear(inter_1);
  mpz_clear(inter_2);
}


void collision (mpz_t *result,
                mpz_t *g, mpz_t *h,
                mpz_t *modulus, mpz_t *order) {

  gmp_randstate_t state;
  gmp_randinit_mt(state);

  unsigned int nb_of_0 = number_of_zeroes(order);
  init_distinguished_points();

  Mmn_t *Mmn = gen_Mmn(g, h, modulus, order);
  mpz_t xi, ai, bi, i;
  mpz_init(xi);
  mpz_init(ai);
  mpz_init(bi);

  mpz_init_set_d(i, 0);

  size_t index = -1;
  while (index == -1) {
    generate_starting_point(&state, &xi, &ai, &bi, g, h, modulus, order);

    while (!is_distinguished_point(&xi, nb_of_0)) {
      f(&xi, &ai, &bi, g, h, modulus, order, Mmn);

      mpz_add_ui(i, i, 1);

      if (mpz_cmp(i, *order) == 0) {
        generate_starting_point(&state, &xi, &ai, &bi, g, h, modulus, order);
        mpz_set_d(i, 0);
      }
    }

    index = is_in_list_of_distinguished_points(&xi, &bi);
    if (index == -1) {
      mpz_t *next_dp = distinguished_points[distinguished_points_index];
      mpz_set(next_dp[0], xi);
      mpz_set(next_dp[1], ai);
      mpz_set(next_dp[2], bi);

      distinguished_points_index++;

      if (distinguished_points_index < NB_OF_POINTS) {
        distinguished_points_index++;
      } else {
        distinguished_points_index = 0;
      }
    }
  }

  mpz_t *found_dp = distinguished_points[index];

  mpz_set(result[0], ai);
  mpz_set(result[1], bi);
  mpz_set(result[2], found_dp[1]);
  mpz_set(result[3], found_dp[2]);

  mpz_clear(ai);
  mpz_clear(bi);
  mpz_clear(xi);
  mpz_clear(i);
  gmp_randclear(state);
  clear_distinguished_points();

  Mmn_clear(Mmn);
  Mmn_free(Mmn);
}
