/* -*- c-file-style: "linux" -*-
 * Author: Jesper Dangaard Brouer <netoptimizer@brouer.com>, (C)2014
 * License: GPLv2
 * From: https://github.com/netoptimizer/network-testing
 *
 * Common/shared helper functions
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

extern int verbose;

inline uint64_t rdtsc()
{
	uint32_t low, high;
	asm volatile("rdtsc" : "=a" (low), "=d" (high));
	return low  | (((uint64_t )high ) << 32);
}

unsigned long long gettime(void);

char *malloc_payload_buffer(int msg_sz);

/* Using __builtin_constant_p(x) to ignore cases where the return
 * value is always the same.
 */
# ifndef likely
#  define likely(x)	(__builtin_constant_p(x) ? !!(x) : __builtin_expect((x),1))
# endif
# ifndef unlikely
#  define unlikely(x)	(__builtin_constant_p(x) ? !!(x) : __builtin_expect((x),0))
# endif


static inline uint32_t cmpxchg(uint32_t *dst, uint32_t old, uint32_t new)
{
	volatile uint32_t *ptr = (volatile uint32_t *)dst;
	uint32_t ret;

	asm volatile("lock; cmpxchgl %2, %1"
		     : "=a" (ret), "+m" (*ptr)
		     : "r" (new), "0" (old)
		     : "memory");

	return ret;
}

#endif /* COMMON_H */
