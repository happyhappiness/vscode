 */
#ifndef assert
#define	assert(e) do {							\
	if (unlikely(config_debug && !(e))) {				\
		malloc_printf(						\
		    "<jemalloc>: %s:%d: Failed assertion: \"%s\"\n",	\
		    __FILE__, __LINE__, #e);				\
