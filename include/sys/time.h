/*
 * Public domain
 * sys/time.h compatibility shim
 */

#include_next <sys/time.h>

#include <stdint.h>

int adjfreq(const int64_t *freq, int64_t *oldfreq);
