#elif (defined(_WIN32))
#define	malloc_tsd_funcs(a_attr, a_name, a_type, a_initializer,		\
    a_cleanup)								\
/* Initialization/cleanup. */						\
a_attr bool								\
a_name##tsd_cleanup_wrapper(void)					\
{									\
	DWORD error = GetLastError();					\
	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)	\
	    TlsGetValue(a_name##tsd_tsd);				\
	SetLastError(error);						\
									\
	if (wrapper == NULL)						\
		return (false);						\
	if (a_cleanup != malloc_tsd_no_cleanup &&			\
	    wrapper->initialized) {					\
		wrapper->initialized = false;				\
		a_cleanup(&wrapper->val);				\
		if (wrapper->initialized) {				\
			/* Trigger another cleanup round. */		\
			return (true);					\
