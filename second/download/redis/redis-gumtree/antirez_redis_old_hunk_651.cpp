#elif (defined(_WIN32))
#define	malloc_tsd_funcs(a_attr, a_name, a_type, a_initializer,		\
    a_cleanup)								\
/* Data structure. */							\
typedef struct {							\
	bool	initialized;						\
	a_type	val;							\
} a_name##_tsd_wrapper_t;						\
/* Initialization/cleanup. */						\
a_attr bool								\
a_name##_tsd_cleanup_wrapper(void)					\
{									\
	a_name##_tsd_wrapper_t *wrapper;				\
									\
	wrapper = (a_name##_tsd_wrapper_t *) TlsGetValue(a_name##_tsd);	\
	if (wrapper == NULL)						\
		return (false);						\
	if (a_cleanup != malloc_tsd_no_cleanup &&			\
	    wrapper->initialized) {					\
		a_type val = wrapper->val;				\
		a_type tsd_static_data = a_initializer;			\
		wrapper->initialized = false;				\
		wrapper->val = tsd_static_data;				\
		a_cleanup(&val);					\
		if (wrapper->initialized) {				\
			/* Trigger another cleanup round. */		\
			return (true);					\
