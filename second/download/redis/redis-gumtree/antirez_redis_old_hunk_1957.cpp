#ifdef JEMALLOC_UTRACE
#  define UTRACE(a, b, c) do {						\
	if (opt_utrace) {						\
		malloc_utrace_t ut;					\
		ut.p = (a);						\
		ut.s = (b);						\
		ut.r = (c);						\
		utrace(&ut, sizeof(ut));				\
	}								\
} while (0)
#else
#  define UTRACE(a, b, c)
#endif

/******************************************************************************/
/* Function prototypes for non-inline static functions. */

static void	stats_print_atexit(void);
static unsigned	malloc_ncpus(void);
static bool	malloc_conf_next(char const **opts_p, char const **k_p,
    size_t *klen_p, char const **v_p, size_t *vlen_p);
static void	malloc_conf_error(const char *msg, const char *k, size_t klen,
    const char *v, size_t vlen);
static void	malloc_conf_init(void);
static bool	malloc_init_hard(void);
static int	imemalign(void **memptr, size_t alignment, size_t size,
    size_t min_alignment);

/******************************************************************************/
/*
