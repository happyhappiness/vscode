 					    "Invalid conf value",	\
 					    k, klen, v, vlen);		\
 				}					\
 				if (cont)				\
 					continue;			\
 			}
-#define	CONF_HANDLE_SIZE_T(o, n, min, max, clip)			\
+#define	CONF_MIN_no(um, min)	false
+#define	CONF_MIN_yes(um, min)	((um) < (min))
+#define	CONF_MAX_no(um, max)	false
+#define	CONF_MAX_yes(um, max)	((um) > (max))
+#define	CONF_HANDLE_T_U(t, o, n, min, max, check_min, check_max, clip)	\
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
-					if ((min) != 0 && um < (min))	\
-						o = (min);		\
-					else if (um > (max))		\
-						o = (max);		\
+					if (CONF_MIN_##check_min(um,	\
+					    (min)))			\
+						o = (t)(min);		\
+					else if (CONF_MAX_##check_max(	\
+					    um, (max)))			\
+						o = (t)(max);		\
 					else				\
-						o = um;			\
+						o = (t)um;		\
 				} else {				\
-					if (((min) != 0 && um < (min))	\
-					    || um > (max)) {		\
+					if (CONF_MIN_##check_min(um,	\
+					    (min)) ||			\
+					    CONF_MAX_##check_max(um,	\
+					    (max))) {			\
 						malloc_conf_error(	\
 						    "Out-of-range "	\
 						    "conf value",	\
 						    k, klen, v, vlen);	\
 					} else				\
-						o = um;			\
+						o = (t)um;		\
 				}					\
 				continue;				\
 			}
+#define	CONF_HANDLE_UNSIGNED(o, n, min, max, check_min, check_max,	\
+    clip)								\
+			CONF_HANDLE_T_U(unsigned, o, n, min, max,	\
+			    check_min, check_max, clip)
+#define	CONF_HANDLE_SIZE_T(o, n, min, max, check_min, check_max, clip)	\
+			CONF_HANDLE_T_U(size_t, o, n, min, max,		\
+			    check_min, check_max, clip)
 #define	CONF_HANDLE_SSIZE_T(o, n, min, max)				\
 			if (CONF_MATCH(n)) {				\
 				long l;					\
 				char *end;				\
 									\
 				set_errno(0);				\
