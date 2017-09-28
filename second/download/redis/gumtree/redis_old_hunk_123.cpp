					o = false;			\
				else {					\
					malloc_conf_error(		\
					    "Invalid conf value",	\
					    k, klen, v, vlen);		\
				}					\
				hit = true;				\
			} else						\
				hit = false;
#define	CONF_HANDLE_BOOL(o, n) {					\
			bool hit;					\
			CONF_HANDLE_BOOL_HIT(o, n, hit);		\
			if (hit)					\
				continue;				\
}
#define	CONF_HANDLE_SIZE_T(o, n, min, max)				\
			if (sizeof(n)-1 == klen && strncmp(n, k,	\
			    klen) == 0) {				\
				uintmax_t um;				\
				char *end;				\
									\
				set_errno(0);				\
				um = malloc_strtoumax(v, &end, 0);	\
				if (get_errno() != 0 || (uintptr_t)end -\
				    (uintptr_t)v != vlen) {		\
					malloc_conf_error(		\
					    "Invalid conf value",	\
					    k, klen, v, vlen);		\
				} else if (um < min || um > max) {	\
					malloc_conf_error(		\
					    "Out-of-range conf value",	\
					    k, klen, v, vlen);		\
				} else					\
					o = um;				\
				continue;				\
			}
#define	CONF_HANDLE_SSIZE_T(o, n, min, max)				\
			if (sizeof(n)-1 == klen && strncmp(n, k,	\
			    klen) == 0) {				\
				long l;					\
