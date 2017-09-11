	malloc_tsd_dalloc(wrapper);					\
	return (false);							\
}									\
a_attr bool								\
a_name##_tsd_boot(void)							\
{									\
									\
	a_name##_tsd = TlsAlloc();					\
	if (a_name##_tsd == TLS_OUT_OF_INDEXES)				\
		return (true);						\
	if (a_cleanup != malloc_tsd_no_cleanup) {			\
		malloc_tsd_cleanup_register(				\
		    &a_name##_tsd_cleanup_wrapper);			\
	}								\
	a_name##_booted = true;						\
	return (false);							\
}									\
/* Get/set. */								\
a_attr a_name##_tsd_wrapper_t *						\
a_name##_tsd_get_wrapper(void)						\
{									\
	a_name##_tsd_wrapper_t *wrapper = (a_name##_tsd_wrapper_t *)	\
	    TlsGetValue(a_name##_tsd);					\
									\
	if (wrapper == NULL) {						\
		wrapper = (a_name##_tsd_wrapper_t *)			\
		    malloc_tsd_malloc(sizeof(a_name##_tsd_wrapper_t));	\
		if (wrapper == NULL) {					\
			malloc_write("<jemalloc>: Error allocating"	\
			    " TSD for "#a_name"\n");			\
			abort();					\
		} else {						\
			static a_type tsd_static_data = a_initializer;	\
			wrapper->initialized = false;			\
			wrapper->val = tsd_static_data;			\
		}							\
		if (!TlsSetValue(a_name##_tsd, (void *)wrapper)) {	\
			malloc_write("<jemalloc>: Error setting"	\
			    " TSD for "#a_name"\n");			\
			abort();					\
		}							\
	}								\
	return (wrapper);						\
}									\
a_attr a_type *								\
a_name##_tsd_get(void)							\
{									\
	a_name##_tsd_wrapper_t *wrapper;				\
									\
	assert(a_name##_booted);					\
	wrapper = a_name##_tsd_get_wrapper();				\
	return (&wrapper->val);						\
}									\
a_attr void								\
a_name##_tsd_set(a_type *val)						\
{									\
	a_name##_tsd_wrapper_t *wrapper;				\
									\
	assert(a_name##_booted);					\
	wrapper = a_name##_tsd_get_wrapper();				\
	wrapper->val = *(val);						\
	if (a_cleanup != malloc_tsd_no_cleanup)				\
		wrapper->initialized = true;				\
}
#else
#define	malloc_tsd_funcs(a_attr, a_name, a_type, a_initializer,		\
    a_cleanup)								\
/* Data structure. */							\
typedef struct {							\
	bool	initialized;						\
	a_type	val;							\
} a_name##_tsd_wrapper_t;						\
/* Initialization/cleanup. */						\
a_attr void								\
a_name##_tsd_cleanup_wrapper(void *arg)					\
{									\
	a_name##_tsd_wrapper_t *wrapper = (a_name##_tsd_wrapper_t *)arg;\
									\
	if (a_cleanup != malloc_tsd_no_cleanup &&			\
	    wrapper->initialized) {					\
		wrapper->initialized = false;				\
		a_cleanup(&wrapper->val);				\
		if (wrapper->initialized) {				\
			/* Trigger another cleanup round. */		\
			if (pthread_setspecific(a_name##_tsd,		\
			    (void *)wrapper)) {				\
				malloc_write("<jemalloc>: Error"	\
				    " setting TSD for "#a_name"\n");	\
