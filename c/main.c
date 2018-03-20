#define _POSIX_C_SOURCE 200809L

#include "main.h"

#include "collision.h"
#include "equation_solver.h"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>


char *big_number_as_string(mpz_t number) {
  char *output = malloc(sizeof(char) * mpz_sizeinbase(number, 10)+2);
  mpz_get_str(output, 10, number);
  return output;
}


void get_parameters(mpz_t **parameters, int argc, char **argv) {
  if (argc < 2) {
    perror("You should provide a file as argument\n");
    exit(EXIT_FAILURE);
  }

  FILE *fd;
  fd = fopen(argv[1], "r");

  if(fd == NULL) {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  char *buffer = NULL;
  size_t buffer_size;

  for (size_t i = 0; i < 4; i++) {
    getline(&buffer, &buffer_size, fd);
    mpz_init_set_str(*parameters[i], buffer, 10);
  }

  free(buffer);
  fclose(fd);
}


void print_result_nicely(mpz_t result, mpz_t g, mpz_t h) {
  char *g_as_str = big_number_as_string(g);
  char *h_as_str = big_number_as_string(h);
  char *result_str = big_number_as_string(result);

  printf("Log of %s in base %s = %s\n",
         h_as_str, g_as_str, result_str);

  free(g_as_str);
  free(h_as_str);
  free(result_str);
}


int main (int argc, char **argv) {
  mpz_t modulus, order, g, h;
  mpz_t *parameters[] = { &modulus, &order, &g, &h };
  get_parameters(parameters, argc, argv);

  mpz_t exponents[4];
  for (size_t i = 0; i < 4; i++) {
    mpz_init(exponents[i]);
  }
  Floyd(exponents, &g, &h, &modulus, &order);

  mpz_t discrete_log_of_h;
  mpz_init(discrete_log_of_h);
  discrete_log_from_exponents(&discrete_log_of_h,
                              &exponents[0], &exponents[1],
                              &exponents[2], &exponents[3],
                              &order);

  print_result_nicely(discrete_log_of_h, g, h);

  for (size_t i = 0; i < 4; i++) {
    mpz_clear(*parameters[i]);
    mpz_clear(exponents[i]);
  }

  mpz_clear(discrete_log_of_h);

  return EXIT_SUCCESS;
}
