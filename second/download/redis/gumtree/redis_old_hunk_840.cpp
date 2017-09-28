					    "Invalid conf value",	\
					    k, klen, v, vlen);		\
				}					\
				if (cont)				\
					continue;			\
			}
#define	CONF_HANDLE_SIZE_T(o, n, min, max, clip)			\
			if (CONF_MATCH(n)) {				\
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
				} else if (clip) {			\
					if ((min) != 0 && um < (min))	\
						o = (min);		\
					else if (um > (max))		\
						o = (max);		\
					else				\
						o = um;			\
				} else {				\
					if (((min) != 0 && um < (min))	\
					    || um > (max)) {		\
						malloc_conf_error(	\
						    "Out-of-range "	\
						    "conf value",	\
						    k, klen, v, vlen);	\
					} else				\
						o = um;			\
				}					\
				continue;				\
			}
#define	CONF_HANDLE_SSIZE_T(o, n, min, max)				\
			if (CONF_MATCH(n)) {				\
				long l;					\
				char *end;				\
									\
				set_errno(0);				\
