					malloc_conf_error(		\
					    "Invalid conf value",	\
					    k, klen, v, vlen);		\
				} else if (clip) {			\
					if (min != 0 && um < min)	\
						o = min;		\
					else if (um > max)		\
						o = max;		\
					else				\
						o = um;			\
				} else {				\
					if ((min != 0 && um < min) ||	\
					    um > max) {			\
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
