	malloc_tsd_dalloc(wrapper);					\
	return (false);							\
}									\
a_attr void								\
a_name##tsd_wrapper_set(a_name##tsd_wrapper_t *wrapper)			\
{									\
									\
	if (!TlsSetValue(a_name##tsd_tsd, (void *)wrapper)) {		\
		malloc_write("<jemalloc>: Error setting"		\
		    " TSD for "#a_name"\n");				\
		abort();						\
	}								\
}									\
a_attr a_name##tsd_wrapper_t *						\
a_name##tsd_wrapper_get(void)						\
{									\
	DWORD error = GetLastError();					\
	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)	\
	    TlsGetValue(a_name##tsd_tsd);				\
	SetLastError(error);						\
									\
	if (unlikely(wrapper == NULL)) {				\
		wrapper = (a_name##tsd_wrapper_t *)			\
		    malloc_tsd_malloc(sizeof(a_name##tsd_wrapper_t));	\
		if (wrapper == NULL) {					\
			malloc_write("<jemalloc>: Error allocating"	\
			    " TSD for "#a_name"\n");			\
			abort();					\
		} else {						\
			wrapper->initialized = false;			\
			wrapper->val = a_initializer;			\
		}							\
		a_name##tsd_wrapper_set(wrapper);			\
	}								\
	return (wrapper);						\
}									\
a_attr bool								\
a_name##tsd_boot0(void)							\
{									\
									\
	a_name##tsd_tsd = TlsAlloc();					\
	if (a_name##tsd_tsd == TLS_OUT_OF_INDEXES)			\
		return (true);						\
	if (a_cleanup != malloc_tsd_no_cleanup) {			\
		malloc_tsd_cleanup_register(				\
		    &a_name##tsd_cleanup_wrapper);			\
	}								\
	a_name##tsd_wrapper_set(&a_name##tsd_boot_wrapper);		\
	a_name##tsd_booted = true;					\
	return (false);							\
}									\
a_attr void								\
a_name##tsd_boot1(void)							\
{									\
	a_name##tsd_wrapper_t *wrapper;					\
	wrapper = (a_name##tsd_wrapper_t *)				\
	    malloc_tsd_malloc(sizeof(a_name##tsd_wrapper_t));		\
	if (wrapper == NULL) {						\
		malloc_write("<jemalloc>: Error allocating"		\
		    " TSD for "#a_name"\n");				\
		abort();						\
	}								\
	memcpy(wrapper, &a_name##tsd_boot_wrapper,			\
	    sizeof(a_name##tsd_wrapper_t));				\
	a_name##tsd_wrapper_set(wrapper);				\
}									\
a_attr bool								\
a_name##tsd_boot(void)							\
{									\
									\
	if (a_name##tsd_boot0())					\
		return (true);						\
	a_name##tsd_boot1();						\
	return (false);							\
}									\
/* Get/set. */								\
a_attr a_type *								\
a_name##tsd_get(void)							\
{									\
	a_name##tsd_wrapper_t *wrapper;					\
									\
	assert(a_name##tsd_booted);					\
	wrapper = a_name##tsd_wrapper_get();				\
	return (&wrapper->val);						\
}									\
a_attr void								\
a_name##tsd_set(a_type *val)						\
{									\
	a_name##tsd_wrapper_t *wrapper;					\
									\
	assert(a_name##tsd_booted);					\
	wrapper = a_name##tsd_wrapper_get();				\
	wrapper->val = *(val);						\
	if (a_cleanup != malloc_tsd_no_cleanup)				\
		wrapper->initialized = true;				\
}
#else
#define	malloc_tsd_funcs(a_attr, a_name, a_type, a_initializer,		\
    a_cleanup)								\
/* Initialization/cleanup. */						\
a_attr void								\
a_name##tsd_cleanup_wrapper(void *arg)					\
{									\
	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)arg;	\
									\
	if (a_cleanup != malloc_tsd_no_cleanup &&			\
	    wrapper->initialized) {					\
		wrapper->initialized = false;				\
		a_cleanup(&wrapper->val);				\
		if (wrapper->initialized) {				\
			/* Trigger another cleanup round. */		\
			if (pthread_setspecific(a_name##tsd_tsd,	\
			    (void *)wrapper)) {				\
				malloc_write("<jemalloc>: Error"	\
				    " setting TSD for "#a_name"\n");	\
