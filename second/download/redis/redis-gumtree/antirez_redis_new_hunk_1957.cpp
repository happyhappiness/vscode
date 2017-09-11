#ifdef JEMALLOC_UTRACE
#  define UTRACE(a, b, c) do {						\
	if (opt_utrace) {						\
		int utrace_serrno = errno;				\
		malloc_utrace_t ut;					\
		ut.p = (a);						\
		ut.s = (b);						\
		ut.r = (c);						\
		utrace(&ut, sizeof(ut));				\
		errno = utrace_serrno;					\
	}								\
} while (0)
#else
#  define UTRACE(a, b, c)
#endif

/******************************************************************************/
/*
 * Function prototypes for static functions that are referenced prior to
 * definition.
 */

static bool	malloc_init_hard(void);

/******************************************************************************/
/*
