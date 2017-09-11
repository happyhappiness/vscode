#	define JEMALLOC_CC_SILENCE_INIT(v)
#endif

#ifdef __GNUC__
#	define likely(x)   __builtin_expect(!!(x), 1)
#	define unlikely(x) __builtin_expect(!!(x), 0)
#else
#	define likely(x)   !!(x)
#	define unlikely(x) !!(x)
#endif

#if !defined(JEMALLOC_INTERNAL_UNREACHABLE)
#  error JEMALLOC_INTERNAL_UNREACHABLE should have been defined by configure
#endif

#define unreachable() JEMALLOC_INTERNAL_UNREACHABLE()

#include "jemalloc/internal/assert.h"

/* Use to assert a particular configuration, e.g., cassert(config_debug). */
#define	cassert(c) do {							\
