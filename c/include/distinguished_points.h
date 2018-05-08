#ifndef DISTINGUISHED_POINT_H
#define DISTINGUISHED_POINT_H

#include <gmp.h>
#include <stdbool.h>

/* Represents the number of points that we can store
 * (depend on the amount of memory available). */
#define NB_OF_POINTS 100000

/* Array of { xi, ai, bi }
 * where xi = g^ai * h^bi */
mpz_t distinguished_points[NB_OF_POINTS][3];
size_t distinguished_points_index;
void init_distinguished_points (void);
void clear_distinguished_points (void);

/* Check wether `number` is in the `list` of distinguished_points
 *   returns the index of the first found
 *   returns -1 if the element is not present in the list */
int is_in_list_of_distinguished_points (mpz_t *number, mpz_t *bi);

// Returns 0 if the number is a distinguished point
//         1 otherwise
bool is_distinguished_point (mpz_t *number, unsigned long int number_of_zeroes);

// Determine the number of zeroes to count to have a good proportion of
// distinguished points.
size_t number_of_zeroes (mpz_t *order);

#endif /* DISTINGUISHED_POINT_H */
