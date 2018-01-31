#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv) {
  if (argc < 2) {
    perror("You should provide a file as argument\n");
    exit(EXIT_FAILURE);
  }

  FILE *fd;
  fd = fopen(argv[1], "r");

  if( fd == NULL ) {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  char *buffer = NULL;
  size_t buffer_size;
  getline(&buffer, &buffer_size, fd);

  /* Lire le nombre depuis une chaine vers un mpz_t en base 10 */
  mpz_t number;
  mpz_init_set_str(number, buffer, 10);

  mpz_t one;
  mpz_init_set_d(one, 1);

  mpz_t result;
  mpz_init(result);
  mpz_add(result, number, one);

  /* Écrire le nombre depuis un mpz_t en base 10 */
  char *output = malloc(sizeof(char) * mpz_sizeinbase(number, 10)+2);
  mpz_get_str(output, 10, result);

  printf("%s\n", output);

  mpz_clear(number);
  mpz_clear(one);
  mpz_clear(result);

  free(output);
  free(buffer);
  fclose(fd);

  return EXIT_SUCCESS;
}
