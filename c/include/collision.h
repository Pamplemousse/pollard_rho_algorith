#ifndef COLLISION_H
#define COLLISION_H

#include <gmp.h>

void collision (mpz_t *result,
                mpz_t *g, mpz_t *h,
                mpz_t *modulus, mpz_t *order);

#endif /* COLLISION_H */
