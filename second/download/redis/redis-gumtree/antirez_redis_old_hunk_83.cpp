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
