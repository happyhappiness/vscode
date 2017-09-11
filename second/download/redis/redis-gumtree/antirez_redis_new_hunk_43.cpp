#	define JEMALLOC_CC_SILENCE_INIT(v)
#endif

#define	JEMALLOC_GNUC_PREREQ(major, minor)				\
    (!defined(__clang__) &&						\
    (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor))))
#ifndef __has_builtin
#  define __has_builtin(builtin) (0)
#endif
#define	JEMALLOC_CLANG_HAS_BUILTIN(builtin)				\
    (defined(__clang__) && __has_builtin(builtin))

#ifdef __GNUC__
#	define likely(x)   __builtin_expect(!!(x), 1)
#	define unlikely(x) __builtin_expect(!!(x), 0)
#  if JEMALLOC_GNUC_PREREQ(4, 6) ||					\
      JEMALLOC_CLANG_HAS_BUILTIN(__builtin_unreachable)
#	define unreachable() __builtin_unreachable()
#  else
#	define unreachable()
#  endif
#else
#	define likely(x)   !!(x)
#	define unlikely(x) !!(x)
#	define unreachable()
#endif

/*
 * Define a custom assert() in order to reduce the chances of deadlock during
 * assertion failure.
 */
#ifndef assert
#define	assert(e) do {							\
	if (unlikely(config_debug && !(e))) {				\
		malloc_printf(						\
		    "<jemalloc>: %s:%d: Failed assertion: \"%s\"\n",	\
		    __FILE__, __LINE__, #e);				\
		abort();						\
	}								\
} while (0)
#endif

#ifndef not_reached
#define	not_reached() do {						\
	if (config_debug) {						\
		malloc_printf(						\
		    "<jemalloc>: %s:%d: Unreachable code reached\n",	\
		    __FILE__, __LINE__);				\
		abort();						\
	}								\
	unreachable();							\
} while (0)
#endif

#ifndef not_implemented
#define	not_implemented() do {						\
	if (config_debug) {						\
		malloc_printf("<jemalloc>: %s:%d: Not implemented\n",	\
		    __FILE__, __LINE__);				\
		abort();						\
	}								\
} while (0)
#endif

#ifndef assert_not_implemented
#define	assert_not_implemented(e) do {					\
	if (unlikely(config_debug && !(e)))				\
		not_implemented();					\
} while (0)
#endif

/* Use to assert a particular configuration, e.g., cassert(config_debug). */
#define	cassert(c) do {							\
