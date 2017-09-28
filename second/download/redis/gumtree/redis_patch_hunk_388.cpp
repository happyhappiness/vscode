 		} default:
 			not_reached();
 			buf[0] = '\0';
 			opts = buf;
 		}
 
-		while (*opts != '\0' && malloc_conf_next(&opts, &k, &klen, &v,
-		    &vlen) == false) {
-#define	CONF_HANDLE_BOOL(o, n)						\
-			if (sizeof(n)-1 == klen && strncmp(n, k,	\
-			    klen) == 0) {				\
-				if (strncmp("true", v, vlen) == 0 &&	\
-				    vlen == sizeof("true")-1)		\
+		while (*opts != '\0' && !malloc_conf_next(&opts, &k, &klen, &v,
+		    &vlen)) {
+#define	CONF_MATCH(n)							\
+	(sizeof(n)-1 == klen && strncmp(n, k, klen) == 0)
+#define	CONF_MATCH_VALUE(n)						\
+	(sizeof(n)-1 == vlen && strncmp(n, v, vlen) == 0)
+#define	CONF_HANDLE_BOOL(o, n, cont)					\
+			if (CONF_MATCH(n)) {				\
+				if (CONF_MATCH_VALUE("true"))		\
 					o = true;			\
-				else if (strncmp("false", v, vlen) ==	\
-				    0 && vlen == sizeof("false")-1)	\
+				else if (CONF_MATCH_VALUE("false"))	\
 					o = false;			\
 				else {					\
 					malloc_conf_error(		\
 					    "Invalid conf value",	\
 					    k, klen, v, vlen);		\
 				}					\
-				continue;				\
+				if (cont)				\
+					continue;			\
 			}
 #define	CONF_HANDLE_SIZE_T(o, n, min, max, clip)			\
-			if (sizeof(n)-1 == klen && strncmp(n, k,	\
-			    klen) == 0) {				\
+			if (CONF_MATCH(n)) {				\
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
-					if (min != 0 && um < min)	\
-						o = min;		\
-					else if (um > max)		\
-						o = max;		\
+					if ((min) != 0 && um < (min))	\
+						o = (min);		\
+					else if (um > (max))		\
+						o = (max);		\
 					else				\
 						o = um;			\
 				} else {				\
-					if ((min != 0 && um < min) ||	\
-					    um > max) {			\
+					if (((min) != 0 && um < (min))	\
+					    || um > (max)) {		\
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
-			if (sizeof(n)-1 == klen && strncmp(n, k,	\
-			    klen) == 0) {				\
+			if (CONF_MATCH(n)) {				\
 				long l;					\
 				char *end;				\
 									\
 				set_errno(0);				\
 				l = strtol(v, &end, 0);			\
 				if (get_errno() != 0 || (uintptr_t)end -\
 				    (uintptr_t)v != vlen) {		\
 					malloc_conf_error(		\
 					    "Invalid conf value",	\
 					    k, klen, v, vlen);		\
-				} else if (l < (ssize_t)min || l >	\
-				    (ssize_t)max) {			\
+				} else if (l < (ssize_t)(min) || l >	\
+				    (ssize_t)(max)) {			\
 					malloc_conf_error(		\
 					    "Out-of-range conf value",	\
 					    k, klen, v, vlen);		\
 				} else					\
 					o = l;				\
 				continue;				\
 			}
 #define	CONF_HANDLE_CHAR_P(o, n, d)					\
-			if (sizeof(n)-1 == klen && strncmp(n, k,	\
-			    klen) == 0) {				\
+			if (CONF_MATCH(n)) {				\
 				size_t cpylen = (vlen <=		\
 				    sizeof(o)-1) ? vlen :		\
 				    sizeof(o)-1;			\
 				strncpy(o, v, cpylen);			\
 				o[cpylen] = '\0';			\
 				continue;				\
 			}
 
-			CONF_HANDLE_BOOL(opt_abort, "abort")
+			CONF_HANDLE_BOOL(opt_abort, "abort", true)
 			/*
-			 * Chunks always require at least one header page, plus
-			 * one data page in the absence of redzones, or three
-			 * pages in the presence of redzones.  In order to
-			 * simplify options processing, fix the limit based on
-			 * config_fill.
+			 * Chunks always require at least one header page,
+			 * as many as 2^(LG_SIZE_CLASS_GROUP+1) data pages, and
+			 * possibly an additional page in the presence of
+			 * redzones.  In order to simplify options processing,
+			 * use a conservative bound that accommodates all these
+			 * constraints.
 			 */
 			CONF_HANDLE_SIZE_T(opt_lg_chunk, "lg_chunk", LG_PAGE +
-			    (config_fill ? 2 : 1), (sizeof(size_t) << 3) - 1,
-			    true)
+			    LG_SIZE_CLASS_GROUP + (config_fill ? 2 : 1),
+			    (sizeof(size_t) << 3) - 1, true)
 			if (strncmp("dss", k, klen) == 0) {
 				int i;
 				bool match = false;
 				for (i = 0; i < dss_prec_limit; i++) {
 					if (strncmp(dss_prec_names[i], v, vlen)
 					    == 0) {
