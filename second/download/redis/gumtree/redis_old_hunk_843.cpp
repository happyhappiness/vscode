#define	assert(e) do {							\
	if (config_debug && !(e)) {					\
		malloc_write("<jemalloc>: Failed assertion\n");		\
		abort();						\
	}								\
} while (0)

#define	not_reached() do {						\
	if (config_debug) {						\
		malloc_write("<jemalloc>: Unreachable code reached\n");	\
		abort();						\
	}								\
} while (0)

#define	not_implemented() do {						\
	if (config_debug) {						\
		malloc_write("<jemalloc>: Not implemented\n");		\
		abort();						\
