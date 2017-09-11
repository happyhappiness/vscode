@@ -10,17 +10,20 @@ malloc_tsd_data(, thread_allocated, thread_allocated_t,
 
 /* Runtime configuration options. */
 const char	*je_malloc_conf;
+bool	opt_abort =
 #ifdef JEMALLOC_DEBUG
-bool	opt_abort = true;
-#  ifdef JEMALLOC_FILL
-bool	opt_junk = true;
-#  else
-bool	opt_junk = false;
-#  endif
+    true
+#else
+    false
+#endif
+    ;
+bool	opt_junk =
+#if (defined(JEMALLOC_DEBUG) && defined(JEMALLOC_FILL))
+    true
 #else
-bool	opt_abort = false;
-bool	opt_junk = false;
+    false
 #endif
+    ;
 size_t	opt_quarantine = ZU(0);
 bool	opt_redzone = false;
 bool	opt_utrace = false;
@@ -83,30 +86,26 @@ typedef struct {
 #ifdef JEMALLOC_UTRACE
 #  define UTRACE(a, b, c) do {						\
 	if (opt_utrace) {						\
+		int utrace_serrno = errno;				\
 		malloc_utrace_t ut;					\
 		ut.p = (a);						\
 		ut.s = (b);						\
 		ut.r = (c);						\
 		utrace(&ut, sizeof(ut));				\
+		errno = utrace_serrno;					\
 	}								\
 } while (0)
 #else
 #  define UTRACE(a, b, c)
 #endif
 
 /******************************************************************************/
-/* Function prototypes for non-inline static functions. */
-
-static void	stats_print_atexit(void);
-static unsigned	malloc_ncpus(void);
-static bool	malloc_conf_next(char const **opts_p, char const **k_p,
-    size_t *klen_p, char const **v_p, size_t *vlen_p);
-static void	malloc_conf_error(const char *msg, const char *k, size_t klen,
-    const char *v, size_t vlen);
-static void	malloc_conf_init(void);
+/*
+ * Function prototypes for static functions that are referenced prior to
+ * definition.
+ */
+
 static bool	malloc_init_hard(void);
-static int	imemalign(void **memptr, size_t alignment, size_t size,
-    size_t min_alignment);
 
 /******************************************************************************/
 /*
@@ -247,7 +246,6 @@ stats_print_atexit(void)
 static unsigned
 malloc_ncpus(void)
 {
-	unsigned ret;
 	long result;
 
 #ifdef _WIN32
@@ -257,14 +255,7 @@ malloc_ncpus(void)
 #else
 	result = sysconf(_SC_NPROCESSORS_ONLN);
 #endif
-	if (result == -1) {
-		/* Error. */
-		ret = 1;
-	}  else {
-    ret = (unsigned)result;
-  }
-
-	return (ret);
+	return ((result == -1) ? 1 : (unsigned)result);
 }
 
 void
@@ -277,12 +268,30 @@ arenas_cleanup(void *arg)
 	malloc_mutex_unlock(&arenas_lock);
 }
 
-static inline bool
+JEMALLOC_ALWAYS_INLINE_C void
+malloc_thread_init(void)
+{
+
+	/*
+	 * TSD initialization can't be safely done as a side effect of
+	 * deallocation, because it is possible for a thread to do nothing but
+	 * deallocate its TLS data via free(), in which case writing to TLS
+	 * would cause write-after-free memory corruption.  The quarantine
+	 * facility *only* gets used as a side effect of deallocation, so make
+	 * a best effort attempt at initializing its TSD by hooking all
+	 * allocation events.
+	 */
+	if (config_fill && opt_quarantine)
+		quarantine_alloc_hook();
+}
+
+JEMALLOC_ALWAYS_INLINE_C bool
 malloc_init(void)
 {
 
-	if (malloc_initialized == false)
-		return (malloc_init_hard());
+	if (malloc_initialized == false && malloc_init_hard())
+		return (true);
+	malloc_thread_init();
 
 	return (false);
 }
@@ -413,8 +422,9 @@ malloc_conf_init(void)
 			}
 			break;
 		case 1: {
+			int linklen = 0;
 #ifndef _WIN32
-			int linklen;
+			int saved_errno = errno;
 			const char *linkname =
 #  ifdef JEMALLOC_PREFIX
 			    "/etc/"JEMALLOC_PREFIX"malloc.conf"
@@ -423,21 +433,20 @@ malloc_conf_init(void)
 #  endif
 			    ;
 
-			if ((linklen = readlink(linkname, buf,
-			    sizeof(buf) - 1)) != -1) {
-				/*
-				 * Use the contents of the "/etc/malloc.conf"
-				 * symbolic link's name.
-				 */
-				buf[linklen] = '\0';
-				opts = buf;
-			} else
-#endif
-			{
+			/*
+			 * Try to use the contents of the "/etc/malloc.conf"
+			 * symbolic link's name.
+			 */
+			linklen = readlink(linkname, buf, sizeof(buf) - 1);
+			if (linklen == -1) {
 				/* No configuration specified. */
-				buf[0] = '\0';
-				opts = buf;
+				linklen = 0;
+				/* restore errno */
+				set_errno(saved_errno);
 			}
+#endif
+			buf[linklen] = '\0';
+			opts = buf;
 			break;
 		} case 2: {
 			const char *envname =
@@ -461,15 +470,14 @@ malloc_conf_init(void)
 			}
 			break;
 		} default:
-			/* NOTREACHED */
-			assert(false);
+			not_reached();
 			buf[0] = '\0';
 			opts = buf;
 		}
 
 		while (*opts != '\0' && malloc_conf_next(&opts, &k, &klen, &v,
 		    &vlen) == false) {
-#define	CONF_HANDLE_BOOL_HIT(o, n, hit)					\
+#define	CONF_HANDLE_BOOL(o, n)						\
 			if (sizeof(n)-1 == klen && strncmp(n, k,	\
 			    klen) == 0) {				\
 				if (strncmp("true", v, vlen) == 0 &&	\
@@ -483,16 +491,9 @@ malloc_conf_init(void)
 					    "Invalid conf value",	\
 					    k, klen, v, vlen);		\
 				}					\
-				hit = true;				\
-			} else						\
-				hit = false;
-#define	CONF_HANDLE_BOOL(o, n) {					\
-			bool hit;					\
-			CONF_HANDLE_BOOL_HIT(o, n, hit);		\
-			if (hit)					\
 				continue;				\
-}
-#define	CONF_HANDLE_SIZE_T(o, n, min, max)				\
+			}
+#define	CONF_HANDLE_SIZE_T(o, n, min, max, clip)			\
 			if (sizeof(n)-1 == klen && strncmp(n, k,	\
 			    klen) == 0) {				\
 				uintmax_t um;				\
@@ -505,12 +506,23 @@ malloc_conf_init(void)
 					malloc_conf_error(		\
 					    "Invalid conf value",	\
 					    k, klen, v, vlen);		\
-				} else if (um < min || um > max) {	\
-					malloc_conf_error(		\
-					    "Out-of-range conf value",	\
-					    k, klen, v, vlen);		\
-				} else					\
-					o = um;				\
+				} else if (clip) {			\
+					if (min != 0 && um < min)	\
+						o = min;		\
+					else if (um > max)		\
+						o = max;		\
+					else				\
+						o = um;			\
+				} else {				\
+					if ((min != 0 && um < min) ||	\
+					    um > max) {			\
+						malloc_conf_error(	\
+						    "Out-of-range "	\
+						    "conf value",	\
+						    k, klen, v, vlen);	\
+					} else				\
+						o = um;			\
+				}					\
 				continue;				\
 			}
 #define	CONF_HANDLE_SSIZE_T(o, n, min, max)				\
@@ -555,7 +567,8 @@ malloc_conf_init(void)
 			 * config_fill.
 			 */
 			CONF_HANDLE_SIZE_T(opt_lg_chunk, "lg_chunk", LG_PAGE +
-			    (config_fill ? 2 : 1), (sizeof(size_t) << 3) - 1)
+			    (config_fill ? 2 : 1), (sizeof(size_t) << 3) - 1,
+			    true)
 			if (strncmp("dss", k, klen) == 0) {
 				int i;
 				bool match = false;
@@ -581,14 +594,14 @@ malloc_conf_init(void)
 				continue;
 			}
 			CONF_HANDLE_SIZE_T(opt_narenas, "narenas", 1,
-			    SIZE_T_MAX)
+			    SIZE_T_MAX, false)
 			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
 			    -1, (sizeof(size_t) << 3) - 1)
 			CONF_HANDLE_BOOL(opt_stats_print, "stats_print")
 			if (config_fill) {
 				CONF_HANDLE_BOOL(opt_junk, "junk")
 				CONF_HANDLE_SIZE_T(opt_quarantine, "quarantine",
-				    0, SIZE_T_MAX)
+				    0, SIZE_T_MAX, false)
 				CONF_HANDLE_BOOL(opt_redzone, "redzone")
 				CONF_HANDLE_BOOL(opt_zero, "zero")
 			}
@@ -668,17 +681,6 @@ malloc_init_hard(void)
 
 	malloc_conf_init();
 
-#if (!defined(JEMALLOC_MUTEX_INIT_CB) && !defined(JEMALLOC_ZONE) \
-    && !defined(_WIN32))
-	/* Register fork handlers. */
-	if (pthread_atfork(jemalloc_prefork, jemalloc_postfork_parent,
-	    jemalloc_postfork_child) != 0) {
-		malloc_write("<jemalloc>: Error in pthread_atfork()\n");
-		if (opt_abort)
-			abort();
-	}
-#endif
-
 	if (opt_stats_print) {
 		/* Print statistics at exit. */
 		if (atexit(stats_print_atexit) != 0) {
@@ -718,8 +720,10 @@ malloc_init_hard(void)
 		return (true);
 	}
 
-	if (malloc_mutex_init(&arenas_lock))
+	if (malloc_mutex_init(&arenas_lock)) {
+		malloc_mutex_unlock(&init_lock);
 		return (true);
+	}
 
 	/*
 	 * Create enough scaffolding to allow recursive allocation in
@@ -765,9 +769,25 @@ malloc_init_hard(void)
 		return (true);
 	}
 
-	/* Get number of CPUs. */
 	malloc_mutex_unlock(&init_lock);
+	/**********************************************************************/
+	/* Recursive allocation may follow. */
+
 	ncpus = malloc_ncpus();
+
+#if (!defined(JEMALLOC_MUTEX_INIT_CB) && !defined(JEMALLOC_ZONE) \
+    && !defined(_WIN32))
+	/* LinuxThreads's pthread_atfork() allocates. */
+	if (pthread_atfork(jemalloc_prefork, jemalloc_postfork_parent,
+	    jemalloc_postfork_child) != 0) {
+		malloc_write("<jemalloc>: Error in pthread_atfork()\n");
+		if (opt_abort)
+			abort();
+	}
+#endif
+
+	/* Done recursively allocating. */
+	/**********************************************************************/
 	malloc_mutex_lock(&init_lock);
 
 	if (mutex_boot()) {
@@ -814,6 +834,7 @@ malloc_init_hard(void)
 
 	malloc_initialized = true;
 	malloc_mutex_unlock(&init_lock);
+
 	return (false);
 }
 
@@ -825,42 +846,88 @@ malloc_init_hard(void)
  * Begin malloc(3)-compatible functions.
  */
 
+static void *
+imalloc_prof_sample(size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if (cnt == NULL)
+		return (NULL);
+	if (prof_promote && usize <= SMALL_MAXCLASS) {
+		p = imalloc(SMALL_MAXCLASS+1);
+		if (p == NULL)
+			return (NULL);
+		arena_prof_promoted(p, usize);
+	} else
+		p = imalloc(usize);
+
+	return (p);
+}
+
+JEMALLOC_ALWAYS_INLINE_C void *
+imalloc_prof(size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if ((uintptr_t)cnt != (uintptr_t)1U)
+		p = imalloc_prof_sample(usize, cnt);
+	else
+		p = imalloc(usize);
+	if (p == NULL)
+		return (NULL);
+	prof_malloc(p, usize, cnt);
+
+	return (p);
+}
+
+/*
+ * MALLOC_BODY() is a macro rather than a function because its contents are in
+ * the fast path, but inlining would cause reliability issues when determining
+ * how many frames to discard from heap profiling backtraces.
+ */
+#define	MALLOC_BODY(ret, size, usize) do {				\
+	if (malloc_init())						\
+		ret = NULL;						\
+	else {								\
+		if (config_prof && opt_prof) {				\
+			prof_thr_cnt_t *cnt;				\
+									\
+			usize = s2u(size);				\
+			/*						\
+			 * Call PROF_ALLOC_PREP() here rather than in	\
+			 * imalloc_prof() so that imalloc_prof() can be	\
+			 * inlined without introducing uncertainty	\
+			 * about the number of backtrace frames to	\
+			 * ignore.  imalloc_prof() is in the fast path	\
+			 * when heap profiling is enabled, so inlining	\
+			 * is critical to performance.  (For		\
+			 * consistency all callers of PROF_ALLOC_PREP()	\
+			 * are structured similarly, even though e.g.	\
+			 * realloc() isn't called enough for inlining	\
+			 * to be critical.)				\
+			 */						\
+			PROF_ALLOC_PREP(1, usize, cnt);			\
+			ret = imalloc_prof(usize, cnt);			\
+		} else {						\
+			if (config_stats || (config_valgrind &&		\
+			    opt_valgrind))				\
+				usize = s2u(size);			\
+			ret = imalloc(size);				\
+		}							\
+	}								\
+} while (0)
+
 void *
 je_malloc(size_t size)
 {
 	void *ret;
 	size_t usize JEMALLOC_CC_SILENCE_INIT(0);
-	prof_thr_cnt_t *cnt JEMALLOC_CC_SILENCE_INIT(NULL);
-
-	if (malloc_init()) {
-		ret = NULL;
-		goto label_oom;
-	}
 
 	if (size == 0)
 		size = 1;
 
-	if (config_prof && opt_prof) {
-		usize = s2u(size);
-		PROF_ALLOC_PREP(1, usize, cnt);
-		if (cnt == NULL) {
-			ret = NULL;
-			goto label_oom;
-		}
-		if (prof_promote && (uintptr_t)cnt != (uintptr_t)1U && usize <=
-		    SMALL_MAXCLASS) {
-			ret = imalloc(SMALL_MAXCLASS+1);
-			if (ret != NULL)
-				arena_prof_promoted(ret, usize);
-		} else
-			ret = imalloc(size);
-	} else {
-		if (config_stats || (config_valgrind && opt_valgrind))
-			usize = s2u(size);
-		ret = imalloc(size);
-	}
+	MALLOC_BODY(ret, size, usize);
 
-label_oom:
 	if (ret == NULL) {
 		if (config_xmalloc && opt_xmalloc) {
 			malloc_write("<jemalloc>: Error in malloc(): "
@@ -869,8 +936,6 @@ je_malloc(size_t size)
 		}
 		set_errno(ENOMEM);
 	}
-	if (config_prof && opt_prof && ret != NULL)
-		prof_malloc(ret, usize, cnt);
 	if (config_stats && ret != NULL) {
 		assert(usize == isalloc(ret, config_prof));
 		thread_allocated_tsd_get()->allocated += usize;
@@ -880,28 +945,63 @@ je_malloc(size_t size)
 	return (ret);
 }
 
+static void *
+imemalign_prof_sample(size_t alignment, size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if (cnt == NULL)
+		return (NULL);
+	if (prof_promote && usize <= SMALL_MAXCLASS) {
+		assert(sa2u(SMALL_MAXCLASS+1, alignment) != 0);
+		p = ipalloc(sa2u(SMALL_MAXCLASS+1, alignment), alignment,
+		    false);
+		if (p == NULL)
+			return (NULL);
+		arena_prof_promoted(p, usize);
+	} else
+		p = ipalloc(usize, alignment, false);
+
+	return (p);
+}
+
+JEMALLOC_ALWAYS_INLINE_C void *
+imemalign_prof(size_t alignment, size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if ((uintptr_t)cnt != (uintptr_t)1U)
+		p = imemalign_prof_sample(alignment, usize, cnt);
+	else
+		p = ipalloc(usize, alignment, false);
+	if (p == NULL)
+		return (NULL);
+	prof_malloc(p, usize, cnt);
+
+	return (p);
+}
+
 JEMALLOC_ATTR(nonnull(1))
 #ifdef JEMALLOC_PROF
 /*
  * Avoid any uncertainty as to how many backtrace frames to ignore in
  * PROF_ALLOC_PREP().
  */
-JEMALLOC_ATTR(noinline)
+JEMALLOC_NOINLINE
 #endif
 static int
-imemalign(void **memptr, size_t alignment, size_t size,
-    size_t min_alignment)
+imemalign(void **memptr, size_t alignment, size_t size, size_t min_alignment)
 {
 	int ret;
 	size_t usize;
 	void *result;
-	prof_thr_cnt_t *cnt JEMALLOC_CC_SILENCE_INIT(NULL);
 
 	assert(min_alignment != 0);
 
-	if (malloc_init())
+	if (malloc_init()) {
 		result = NULL;
-	else {
+		goto label_oom;
+	} else {
 		if (size == 0)
 			size = 1;
 
@@ -921,57 +1021,38 @@ imemalign(void **memptr, size_t alignment, size_t size,
 		usize = sa2u(size, alignment);
 		if (usize == 0) {
 			result = NULL;
-			ret = ENOMEM;
-			goto label_return;
+			goto label_oom;
 		}
 
 		if (config_prof && opt_prof) {
+			prof_thr_cnt_t *cnt;
+
 			PROF_ALLOC_PREP(2, usize, cnt);
-			if (cnt == NULL) {
-				result = NULL;
-				ret = EINVAL;
-			} else {
-				if (prof_promote && (uintptr_t)cnt !=
-				    (uintptr_t)1U && usize <= SMALL_MAXCLASS) {
-					assert(sa2u(SMALL_MAXCLASS+1,
-					    alignment) != 0);
-					result = ipalloc(sa2u(SMALL_MAXCLASS+1,
-					    alignment), alignment, false);
-					if (result != NULL) {
-						arena_prof_promoted(result,
-						    usize);
-					}
-				} else {
-					result = ipalloc(usize, alignment,
-					    false);
-				}
-			}
+			result = imemalign_prof(alignment, usize, cnt);
 		} else
 			result = ipalloc(usize, alignment, false);
-	}
-
-	if (result == NULL) {
-		if (config_xmalloc && opt_xmalloc) {
-			malloc_write("<jemalloc>: Error allocating aligned "
-			    "memory: out of memory\n");
-			abort();
-		}
-		ret = ENOMEM;
-		goto label_return;
+		if (result == NULL)
+			goto label_oom;
 	}
 
 	*memptr = result;
 	ret = 0;
-
 label_return:
 	if (config_stats && result != NULL) {
 		assert(usize == isalloc(result, config_prof));
 		thread_allocated_tsd_get()->allocated += usize;
 	}
-	if (config_prof && opt_prof && result != NULL)
-		prof_malloc(result, usize, cnt);
 	UTRACE(0, size, result);
 	return (ret);
+label_oom:
+	assert(result == NULL);
+	if (config_xmalloc && opt_xmalloc) {
+		malloc_write("<jemalloc>: Error allocating aligned memory: "
+		    "out of memory\n");
+		abort();
+	}
+	ret = ENOMEM;
+	goto label_return;
 }
 
 int
@@ -998,13 +1079,46 @@ je_aligned_alloc(size_t alignment, size_t size)
 	return (ret);
 }
 
+static void *
+icalloc_prof_sample(size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if (cnt == NULL)
+		return (NULL);
+	if (prof_promote && usize <= SMALL_MAXCLASS) {
+		p = icalloc(SMALL_MAXCLASS+1);
+		if (p == NULL)
+			return (NULL);
+		arena_prof_promoted(p, usize);
+	} else
+		p = icalloc(usize);
+
+	return (p);
+}
+
+JEMALLOC_ALWAYS_INLINE_C void *
+icalloc_prof(size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if ((uintptr_t)cnt != (uintptr_t)1U)
+		p = icalloc_prof_sample(usize, cnt);
+	else
+		p = icalloc(usize);
+	if (p == NULL)
+		return (NULL);
+	prof_malloc(p, usize, cnt);
+
+	return (p);
+}
+
 void *
 je_calloc(size_t num, size_t size)
 {
 	void *ret;
 	size_t num_size;
 	size_t usize JEMALLOC_CC_SILENCE_INIT(0);
-	prof_thr_cnt_t *cnt JEMALLOC_CC_SILENCE_INIT(NULL);
 
 	if (malloc_init()) {
 		num_size = 0;
@@ -1033,19 +1147,11 @@ je_calloc(size_t num, size_t size)
 	}
 
 	if (config_prof && opt_prof) {
+		prof_thr_cnt_t *cnt;
+
 		usize = s2u(num_size);
 		PROF_ALLOC_PREP(1, usize, cnt);
-		if (cnt == NULL) {
-			ret = NULL;
-			goto label_return;
-		}
-		if (prof_promote && (uintptr_t)cnt != (uintptr_t)1U && usize
-		    <= SMALL_MAXCLASS) {
-			ret = icalloc(SMALL_MAXCLASS+1);
-			if (ret != NULL)
-				arena_prof_promoted(ret, usize);
-		} else
-			ret = icalloc(num_size);
+		ret = icalloc_prof(usize, cnt);
 	} else {
 		if (config_stats || (config_valgrind && opt_valgrind))
 			usize = s2u(num_size);
@@ -1061,9 +1167,6 @@ je_calloc(size_t num, size_t size)
 		}
 		set_errno(ENOMEM);
 	}
-
-	if (config_prof && opt_prof && ret != NULL)
-		prof_malloc(ret, usize, cnt);
 	if (config_stats && ret != NULL) {
 		assert(usize == isalloc(ret, config_prof));
 		thread_allocated_tsd_get()->allocated += usize;
@@ -1073,150 +1176,126 @@ je_calloc(size_t num, size_t size)
 	return (ret);
 }
 
+static void *
+irealloc_prof_sample(void *oldptr, size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+
+	if (cnt == NULL)
+		return (NULL);
+	if (prof_promote && usize <= SMALL_MAXCLASS) {
+		p = iralloc(oldptr, SMALL_MAXCLASS+1, 0, 0, false);
+		if (p == NULL)
+			return (NULL);
+		arena_prof_promoted(p, usize);
+	} else
+		p = iralloc(oldptr, usize, 0, 0, false);
+
+	return (p);
+}
+
+JEMALLOC_ALWAYS_INLINE_C void *
+irealloc_prof(void *oldptr, size_t old_usize, size_t usize, prof_thr_cnt_t *cnt)
+{
+	void *p;
+	prof_ctx_t *old_ctx;
+
+	old_ctx = prof_ctx_get(oldptr);
+	if ((uintptr_t)cnt != (uintptr_t)1U)
+		p = irealloc_prof_sample(oldptr, usize, cnt);
+	else
+		p = iralloc(oldptr, usize, 0, 0, false);
+	if (p == NULL)
+		return (NULL);
+	prof_realloc(p, usize, cnt, old_usize, old_ctx);
+
+	return (p);
+}
+
+JEMALLOC_INLINE_C void
+ifree(void *ptr)
+{
+	size_t usize;
+	UNUSED size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);
+
+	assert(ptr != NULL);
+	assert(malloc_initialized || IS_INITIALIZER);
+
+	if (config_prof && opt_prof) {
+		usize = isalloc(ptr, config_prof);
+		prof_free(ptr, usize);
+	} else if (config_stats || config_valgrind)
+		usize = isalloc(ptr, config_prof);
+	if (config_stats)
+		thread_allocated_tsd_get()->deallocated += usize;
+	if (config_valgrind && opt_valgrind)
+		rzsize = p2rz(ptr);
+	iqalloc(ptr);
+	JEMALLOC_VALGRIND_FREE(ptr, rzsize);
+}
+
 void *
 je_realloc(void *ptr, size_t size)
 {
 	void *ret;
 	size_t usize JEMALLOC_CC_SILENCE_INIT(0);
-	size_t old_size = 0;
-	size_t old_rzsize JEMALLOC_CC_SILENCE_INIT(0);
-	prof_thr_cnt_t *cnt JEMALLOC_CC_SILENCE_INIT(NULL);
-	prof_ctx_t *old_ctx JEMALLOC_CC_SILENCE_INIT(NULL);
+	size_t old_usize = 0;
+	UNUSED size_t old_rzsize JEMALLOC_CC_SILENCE_INIT(0);
 
 	if (size == 0) {
 		if (ptr != NULL) {
-			/* realloc(ptr, 0) is equivalent to free(p). */
-			if (config_prof) {
-				old_size = isalloc(ptr, true);
-				if (config_valgrind && opt_valgrind)
-					old_rzsize = p2rz(ptr);
-			} else if (config_stats) {
-				old_size = isalloc(ptr, false);
-				if (config_valgrind && opt_valgrind)
-					old_rzsize = u2rz(old_size);
-			} else if (config_valgrind && opt_valgrind) {
-				old_size = isalloc(ptr, false);
-				old_rzsize = u2rz(old_size);
-			}
-			if (config_prof && opt_prof) {
-				old_ctx = prof_ctx_get(ptr);
-				cnt = NULL;
-			}
-			iqalloc(ptr);
-			ret = NULL;
-			goto label_return;
-		} else
-			size = 1;
+			/* realloc(ptr, 0) is equivalent to free(ptr). */
+			UTRACE(ptr, 0, 0);
+			ifree(ptr);
+			return (NULL);
+		}
+		size = 1;
 	}
 
 	if (ptr != NULL) {
 		assert(malloc_initialized || IS_INITIALIZER);
+		malloc_thread_init();
+
+		if ((config_prof && opt_prof) || config_stats ||
+		    (config_valgrind && opt_valgrind))
+			old_usize = isalloc(ptr, config_prof);
+		if (config_valgrind && opt_valgrind)
+			old_rzsize = config_prof ? p2rz(ptr) : u2rz(old_usize);
 
-		if (config_prof) {
-			old_size = isalloc(ptr, true);
-			if (config_valgrind && opt_valgrind)
-				old_rzsize = p2rz(ptr);
-		} else if (config_stats) {
-			old_size = isalloc(ptr, false);
-			if (config_valgrind && opt_valgrind)
-				old_rzsize = u2rz(old_size);
-		} else if (config_valgrind && opt_valgrind) {
-			old_size = isalloc(ptr, false);
-			old_rzsize = u2rz(old_size);
-		}
 		if (config_prof && opt_prof) {
+			prof_thr_cnt_t *cnt;
+
 			usize = s2u(size);
-			old_ctx = prof_ctx_get(ptr);
 			PROF_ALLOC_PREP(1, usize, cnt);
-			if (cnt == NULL) {
-				old_ctx = NULL;
-				ret = NULL;
-				goto label_oom;
-			}
-			if (prof_promote && (uintptr_t)cnt != (uintptr_t)1U &&
-			    usize <= SMALL_MAXCLASS) {
-				ret = iralloc(ptr, SMALL_MAXCLASS+1, 0, 0,
-				    false, false);
-				if (ret != NULL)
-					arena_prof_promoted(ret, usize);
-				else
-					old_ctx = NULL;
-			} else {
-				ret = iralloc(ptr, size, 0, 0, false, false);
-				if (ret == NULL)
-					old_ctx = NULL;
-			}
+			ret = irealloc_prof(ptr, old_usize, usize, cnt);
 		} else {
 			if (config_stats || (config_valgrind && opt_valgrind))
 				usize = s2u(size);
-			ret = iralloc(ptr, size, 0, 0, false, false);
-		}
-
-label_oom:
-		if (ret == NULL) {
-			if (config_xmalloc && opt_xmalloc) {
-				malloc_write("<jemalloc>: Error in realloc(): "
-				    "out of memory\n");
-				abort();
-			}
-			set_errno(ENOMEM);
+			ret = iralloc(ptr, size, 0, 0, false);
 		}
 	} else {
 		/* realloc(NULL, size) is equivalent to malloc(size). */
-		if (config_prof && opt_prof)
-			old_ctx = NULL;
-		if (malloc_init()) {
-			if (config_prof && opt_prof)
-				cnt = NULL;
-			ret = NULL;
-		} else {
-			if (config_prof && opt_prof) {
-				usize = s2u(size);
-				PROF_ALLOC_PREP(1, usize, cnt);
-				if (cnt == NULL)
-					ret = NULL;
-				else {
-					if (prof_promote && (uintptr_t)cnt !=
-					    (uintptr_t)1U && usize <=
-					    SMALL_MAXCLASS) {
-						ret = imalloc(SMALL_MAXCLASS+1);
-						if (ret != NULL) {
-							arena_prof_promoted(ret,
-							    usize);
-						}
-					} else
-						ret = imalloc(size);
-				}
-			} else {
-				if (config_stats || (config_valgrind &&
-				    opt_valgrind))
-					usize = s2u(size);
-				ret = imalloc(size);
-			}
-		}
+		MALLOC_BODY(ret, size, usize);
+	}
 
-		if (ret == NULL) {
-			if (config_xmalloc && opt_xmalloc) {
-				malloc_write("<jemalloc>: Error in realloc(): "
-				    "out of memory\n");
-				abort();
-			}
-			set_errno(ENOMEM);
+	if (ret == NULL) {
+		if (config_xmalloc && opt_xmalloc) {
+			malloc_write("<jemalloc>: Error in realloc(): "
+			    "out of memory\n");
+			abort();
 		}
+		set_errno(ENOMEM);
 	}
-
-label_return:
-	if (config_prof && opt_prof)
-		prof_realloc(ret, usize, cnt, old_size, old_ctx);
 	if (config_stats && ret != NULL) {
 		thread_allocated_t *ta;
 		assert(usize == isalloc(ret, config_prof));
 		ta = thread_allocated_tsd_get();
 		ta->allocated += usize;
-		ta->deallocated += old_size;
+		ta->deallocated += old_usize;
 	}
 	UTRACE(ptr, size, ret);
-	JEMALLOC_VALGRIND_REALLOC(ret, usize, ptr, old_size, old_rzsize, false);
+	JEMALLOC_VALGRIND_REALLOC(ret, usize, ptr, old_usize, old_rzsize,
+	    false);
 	return (ret);
 }
 
@@ -1225,24 +1304,8 @@ je_free(void *ptr)
 {
 
 	UTRACE(ptr, 0, 0);
-	if (ptr != NULL) {
-		size_t usize;
-		size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);
-
-		assert(malloc_initialized || IS_INITIALIZER);
-
-		if (config_prof && opt_prof) {
-			usize = isalloc(ptr, config_prof);
-			prof_free(ptr, usize);
-		} else if (config_stats || config_valgrind)
-			usize = isalloc(ptr, config_prof);
-		if (config_stats)
-			thread_allocated_tsd_get()->deallocated += usize;
-		if (config_valgrind && opt_valgrind)
-			rzsize = p2rz(ptr);
-		iqalloc(ptr);
-		JEMALLOC_VALGRIND_FREE(ptr, rzsize);
-	}
+	if (ptr != NULL)
+		ifree(ptr);
 }
 
 /*
@@ -1308,318 +1371,396 @@ JEMALLOC_EXPORT void *(* __memalign_hook)(size_t alignment, size_t size) =
  * Begin non-standard functions.
  */
 
-size_t
-je_malloc_usable_size(JEMALLOC_USABLE_SIZE_CONST void *ptr)
+JEMALLOC_ALWAYS_INLINE_C void *
+imallocx(size_t usize, size_t alignment, bool zero, bool try_tcache,
+    arena_t *arena)
 {
-	size_t ret;
 
-	assert(malloc_initialized || IS_INITIALIZER);
+	assert(usize == ((alignment == 0) ? s2u(usize) : sa2u(usize,
+	    alignment)));
 
-	if (config_ivsalloc)
-		ret = ivsalloc(ptr, config_prof);
+	if (alignment != 0)
+		return (ipalloct(usize, alignment, zero, try_tcache, arena));
+	else if (zero)
+		return (icalloct(usize, try_tcache, arena));
 	else
-		ret = (ptr != NULL) ? isalloc(ptr, config_prof) : 0;
-
-	return (ret);
+		return (imalloct(usize, try_tcache, arena));
 }
 
-void
-je_malloc_stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
-    const char *opts)
+static void *
+imallocx_prof_sample(size_t usize, size_t alignment, bool zero, bool try_tcache,
+    arena_t *arena, prof_thr_cnt_t *cnt)
 {
+	void *p;
 
-	stats_print(write_cb, cbopaque, opts);
+	if (cnt == NULL)
+		return (NULL);
+	if (prof_promote && usize <= SMALL_MAXCLASS) {
+		size_t usize_promoted = (alignment == 0) ?
+		    s2u(SMALL_MAXCLASS+1) : sa2u(SMALL_MAXCLASS+1, alignment);
+		assert(usize_promoted != 0);
+		p = imallocx(usize_promoted, alignment, zero, try_tcache,
+		    arena);
+		if (p == NULL)
+			return (NULL);
+		arena_prof_promoted(p, usize);
+	} else
+		p = imallocx(usize, alignment, zero, try_tcache, arena);
+
+	return (p);
 }
 
-int
-je_mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp,
-    size_t newlen)
+JEMALLOC_ALWAYS_INLINE_C void *
+imallocx_prof(size_t usize, size_t alignment, bool zero, bool try_tcache,
+    arena_t *arena, prof_thr_cnt_t *cnt)
 {
+	void *p;
 
-	if (malloc_init())
-		return (EAGAIN);
+	if ((uintptr_t)cnt != (uintptr_t)1U) {
+		p = imallocx_prof_sample(usize, alignment, zero, try_tcache,
+		    arena, cnt);
+	} else
+		p = imallocx(usize, alignment, zero, try_tcache, arena);
+	if (p == NULL)
+		return (NULL);
+	prof_malloc(p, usize, cnt);
 
-	return (ctl_byname(name, oldp, oldlenp, newp, newlen));
+	return (p);
 }
 
-int
-je_mallctlnametomib(const char *name, size_t *mibp, size_t *miblenp)
+void *
+je_mallocx(size_t size, int flags)
 {
+	void *p;
+	size_t usize;
+	size_t alignment = (ZU(1) << (flags & MALLOCX_LG_ALIGN_MASK)
+	    & (SIZE_T_MAX-1));
+	bool zero = flags & MALLOCX_ZERO;
+	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
+	arena_t *arena;
+	bool try_tcache;
+
+	assert(size != 0);
 
 	if (malloc_init())
-		return (EAGAIN);
+		goto label_oom;
 
-	return (ctl_nametomib(name, mibp, miblenp));
+	if (arena_ind != UINT_MAX) {
+		arena = arenas[arena_ind];
+		try_tcache = false;
+	} else {
+		arena = NULL;
+		try_tcache = true;
+	}
+
+	usize = (alignment == 0) ? s2u(size) : sa2u(size, alignment);
+	assert(usize != 0);
+
+	if (config_prof && opt_prof) {
+		prof_thr_cnt_t *cnt;
+
+		PROF_ALLOC_PREP(1, usize, cnt);
+		p = imallocx_prof(usize, alignment, zero, try_tcache, arena,
+		    cnt);
+	} else
+		p = imallocx(usize, alignment, zero, try_tcache, arena);
+	if (p == NULL)
+		goto label_oom;
+
+	if (config_stats) {
+		assert(usize == isalloc(p, config_prof));
+		thread_allocated_tsd_get()->allocated += usize;
+	}
+	UTRACE(0, size, p);
+	JEMALLOC_VALGRIND_MALLOC(true, p, usize, zero);
+	return (p);
+label_oom:
+	if (config_xmalloc && opt_xmalloc) {
+		malloc_write("<jemalloc>: Error in mallocx(): out of memory\n");
+		abort();
+	}
+	UTRACE(0, size, 0);
+	return (NULL);
 }
 
-int
-je_mallctlbymib(const size_t *mib, size_t miblen, void *oldp, size_t *oldlenp,
-  void *newp, size_t newlen)
+static void *
+irallocx_prof_sample(void *oldptr, size_t size, size_t alignment, size_t usize,
+    bool zero, bool try_tcache_alloc, bool try_tcache_dalloc, arena_t *arena,
+    prof_thr_cnt_t *cnt)
 {
+	void *p;
 
-	if (malloc_init())
-		return (EAGAIN);
+	if (cnt == NULL)
+		return (NULL);
+	if (prof_promote && usize <= SMALL_MAXCLASS) {
+		p = iralloct(oldptr, SMALL_MAXCLASS+1, (SMALL_MAXCLASS+1 >=
+		    size) ? 0 : size - (SMALL_MAXCLASS+1), alignment, zero,
+		    try_tcache_alloc, try_tcache_dalloc, arena);
+		if (p == NULL)
+			return (NULL);
+		arena_prof_promoted(p, usize);
+	} else {
+		p = iralloct(oldptr, size, 0, alignment, zero,
+		    try_tcache_alloc, try_tcache_dalloc, arena);
+	}
 
-	return (ctl_bymib(mib, miblen, oldp, oldlenp, newp, newlen));
+	return (p);
 }
 
-/*
- * End non-standard functions.
- */
-/******************************************************************************/
-/*
- * Begin experimental functions.
- */
-#ifdef JEMALLOC_EXPERIMENTAL
-
-JEMALLOC_INLINE void *
-iallocm(size_t usize, size_t alignment, bool zero, bool try_tcache,
-    arena_t *arena)
+JEMALLOC_ALWAYS_INLINE_C void *
+irallocx_prof(void *oldptr, size_t old_usize, size_t size, size_t alignment,
+    size_t *usize, bool zero, bool try_tcache_alloc, bool try_tcache_dalloc,
+    arena_t *arena, prof_thr_cnt_t *cnt)
 {
+	void *p;
+	prof_ctx_t *old_ctx;
 
-	assert(usize == ((alignment == 0) ? s2u(usize) : sa2u(usize,
-	    alignment)));
+	old_ctx = prof_ctx_get(oldptr);
+	if ((uintptr_t)cnt != (uintptr_t)1U)
+		p = irallocx_prof_sample(oldptr, size, alignment, *usize, zero,
+		    try_tcache_alloc, try_tcache_dalloc, arena, cnt);
+	else {
+		p = iralloct(oldptr, size, 0, alignment, zero,
+		    try_tcache_alloc, try_tcache_dalloc, arena);
+	}
+	if (p == NULL)
+		return (NULL);
 
-	if (alignment != 0)
-		return (ipallocx(usize, alignment, zero, try_tcache, arena));
-	else if (zero)
-		return (icallocx(usize, try_tcache, arena));
-	else
-		return (imallocx(usize, try_tcache, arena));
+	if (p == oldptr && alignment != 0) {
+		/*
+		 * The allocation did not move, so it is possible that the size
+		 * class is smaller than would guarantee the requested
+		 * alignment, and that the alignment constraint was
+		 * serendipitously satisfied.  Additionally, old_usize may not
+		 * be the same as the current usize because of in-place large
+		 * reallocation.  Therefore, query the actual value of usize.
+		 */
+		*usize = isalloc(p, config_prof);
+	}
+	prof_realloc(p, *usize, cnt, old_usize, old_ctx);
+
+	return (p);
 }
 
-int
-je_allocm(void **ptr, size_t *rsize, size_t size, int flags)
+void *
+je_rallocx(void *ptr, size_t size, int flags)
 {
 	void *p;
-	size_t usize;
-	size_t alignment = (ZU(1) << (flags & ALLOCM_LG_ALIGN_MASK)
+	size_t usize, old_usize;
+	UNUSED size_t old_rzsize JEMALLOC_CC_SILENCE_INIT(0);
+	size_t alignment = (ZU(1) << (flags & MALLOCX_LG_ALIGN_MASK)
 	    & (SIZE_T_MAX-1));
-	bool zero = flags & ALLOCM_ZERO;
+	bool zero = flags & MALLOCX_ZERO;
 	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
+	bool try_tcache_alloc, try_tcache_dalloc;
 	arena_t *arena;
-	bool try_tcache;
 
 	assert(ptr != NULL);
 	assert(size != 0);
-
-	if (malloc_init())
-		goto label_oom;
+	assert(malloc_initialized || IS_INITIALIZER);
+	malloc_thread_init();
 
 	if (arena_ind != UINT_MAX) {
+		arena_chunk_t *chunk;
+		try_tcache_alloc = false;
+		chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
+		try_tcache_dalloc = (chunk == ptr || chunk->arena !=
+		    arenas[arena_ind]);
 		arena = arenas[arena_ind];
-		try_tcache = false;
 	} else {
+		try_tcache_alloc = true;
+		try_tcache_dalloc = true;
 		arena = NULL;
-		try_tcache = true;
 	}
 
-	usize = (alignment == 0) ? s2u(size) : sa2u(size, alignment);
-	if (usize == 0)
-		goto label_oom;
+	if ((config_prof && opt_prof) || config_stats ||
+	    (config_valgrind && opt_valgrind))
+		old_usize = isalloc(ptr, config_prof);
+	if (config_valgrind && opt_valgrind)
+		old_rzsize = u2rz(old_usize);
 
 	if (config_prof && opt_prof) {
 		prof_thr_cnt_t *cnt;
 
+		usize = (alignment == 0) ? s2u(size) : sa2u(size, alignment);
+		assert(usize != 0);
 		PROF_ALLOC_PREP(1, usize, cnt);
-		if (cnt == NULL)
+		p = irallocx_prof(ptr, old_usize, size, alignment, &usize, zero,
+		    try_tcache_alloc, try_tcache_dalloc, arena, cnt);
+		if (p == NULL)
 			goto label_oom;
-		if (prof_promote && (uintptr_t)cnt != (uintptr_t)1U && usize <=
-		    SMALL_MAXCLASS) {
-			size_t usize_promoted = (alignment == 0) ?
-			    s2u(SMALL_MAXCLASS+1) : sa2u(SMALL_MAXCLASS+1,
-			    alignment);
-			assert(usize_promoted != 0);
-			p = iallocm(usize_promoted, alignment, zero,
-			    try_tcache, arena);
-			if (p == NULL)
-				goto label_oom;
-			arena_prof_promoted(p, usize);
-		} else {
-			p = iallocm(usize, alignment, zero, try_tcache, arena);
-			if (p == NULL)
-				goto label_oom;
-		}
-		prof_malloc(p, usize, cnt);
 	} else {
-		p = iallocm(usize, alignment, zero, try_tcache, arena);
+		p = iralloct(ptr, size, 0, alignment, zero, try_tcache_alloc,
+		    try_tcache_dalloc, arena);
 		if (p == NULL)
 			goto label_oom;
+		if (config_stats || (config_valgrind && opt_valgrind))
+			usize = isalloc(p, config_prof);
 	}
-	if (rsize != NULL)
-		*rsize = usize;
 
-	*ptr = p;
 	if (config_stats) {
-		assert(usize == isalloc(p, config_prof));
-		thread_allocated_tsd_get()->allocated += usize;
+		thread_allocated_t *ta;
+		ta = thread_allocated_tsd_get();
+		ta->allocated += usize;
+		ta->deallocated += old_usize;
 	}
-	UTRACE(0, size, p);
-	JEMALLOC_VALGRIND_MALLOC(true, p, usize, zero);
-	return (ALLOCM_SUCCESS);
+	UTRACE(ptr, size, p);
+	JEMALLOC_VALGRIND_REALLOC(p, usize, ptr, old_usize, old_rzsize, zero);
+	return (p);
 label_oom:
 	if (config_xmalloc && opt_xmalloc) {
-		malloc_write("<jemalloc>: Error in allocm(): "
-		    "out of memory\n");
+		malloc_write("<jemalloc>: Error in rallocx(): out of memory\n");
 		abort();
 	}
-	*ptr = NULL;
-	UTRACE(0, size, 0);
-	return (ALLOCM_ERR_OOM);
+	UTRACE(ptr, size, 0);
+	return (NULL);
 }
 
-int
-je_rallocm(void **ptr, size_t *rsize, size_t size, size_t extra, int flags)
+JEMALLOC_ALWAYS_INLINE_C size_t
+ixallocx_helper(void *ptr, size_t old_usize, size_t size, size_t extra,
+    size_t alignment, bool zero, arena_t *arena)
 {
-	void *p, *q;
 	size_t usize;
-	size_t old_size;
-	size_t old_rzsize JEMALLOC_CC_SILENCE_INIT(0);
-	size_t alignment = (ZU(1) << (flags & ALLOCM_LG_ALIGN_MASK)
+
+	if (ixalloc(ptr, size, extra, alignment, zero))
+		return (old_usize);
+	usize = isalloc(ptr, config_prof);
+
+	return (usize);
+}
+
+static size_t
+ixallocx_prof_sample(void *ptr, size_t old_usize, size_t size, size_t extra,
+    size_t alignment, size_t max_usize, bool zero, arena_t *arena,
+    prof_thr_cnt_t *cnt)
+{
+	size_t usize;
+
+	if (cnt == NULL)
+		return (old_usize);
+	/* Use minimum usize to determine whether promotion may happen. */
+	if (prof_promote && ((alignment == 0) ? s2u(size) : sa2u(size,
+	    alignment)) <= SMALL_MAXCLASS) {
+		if (ixalloc(ptr, SMALL_MAXCLASS+1, (SMALL_MAXCLASS+1 >=
+		    size+extra) ? 0 : size+extra - (SMALL_MAXCLASS+1),
+		    alignment, zero))
+			return (old_usize);
+		usize = isalloc(ptr, config_prof);
+		if (max_usize < PAGE)
+			arena_prof_promoted(ptr, usize);
+	} else {
+		usize = ixallocx_helper(ptr, old_usize, size, extra, alignment,
+		    zero, arena);
+	}
+
+	return (usize);
+}
+
+JEMALLOC_ALWAYS_INLINE_C size_t
+ixallocx_prof(void *ptr, size_t old_usize, size_t size, size_t extra,
+    size_t alignment, size_t max_usize, bool zero, arena_t *arena,
+    prof_thr_cnt_t *cnt)
+{
+	size_t usize;
+	prof_ctx_t *old_ctx;
+
+	old_ctx = prof_ctx_get(ptr);
+	if ((uintptr_t)cnt != (uintptr_t)1U) {
+		usize = ixallocx_prof_sample(ptr, old_usize, size, extra,
+		    alignment, zero, max_usize, arena, cnt);
+	} else {
+		usize = ixallocx_helper(ptr, old_usize, size, extra, alignment,
+		    zero, arena);
+	}
+	if (usize == old_usize)
+		return (usize);
+	prof_realloc(ptr, usize, cnt, old_usize, old_ctx);
+
+	return (usize);
+}
+
+size_t
+je_xallocx(void *ptr, size_t size, size_t extra, int flags)
+{
+	size_t usize, old_usize;
+	UNUSED size_t old_rzsize JEMALLOC_CC_SILENCE_INIT(0);
+	size_t alignment = (ZU(1) << (flags & MALLOCX_LG_ALIGN_MASK)
 	    & (SIZE_T_MAX-1));
-	bool zero = flags & ALLOCM_ZERO;
-	bool no_move = flags & ALLOCM_NO_MOVE;
+	bool zero = flags & MALLOCX_ZERO;
 	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
-	bool try_tcache_alloc, try_tcache_dalloc;
 	arena_t *arena;
 
 	assert(ptr != NULL);
-	assert(*ptr != NULL);
 	assert(size != 0);
 	assert(SIZE_T_MAX - size >= extra);
 	assert(malloc_initialized || IS_INITIALIZER);
+	malloc_thread_init();
 
-	if (arena_ind != UINT_MAX) {
-		arena_chunk_t *chunk;
-		try_tcache_alloc = true;
-		chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(*ptr);
-		try_tcache_dalloc = (chunk == *ptr || chunk->arena !=
-		    arenas[arena_ind]);
+	if (arena_ind != UINT_MAX)
 		arena = arenas[arena_ind];
-	} else {
-		try_tcache_alloc = true;
-		try_tcache_dalloc = true;
+	else
 		arena = NULL;
-	}
 
-	p = *ptr;
+	old_usize = isalloc(ptr, config_prof);
+	if (config_valgrind && opt_valgrind)
+		old_rzsize = u2rz(old_usize);
+
 	if (config_prof && opt_prof) {
 		prof_thr_cnt_t *cnt;
-
 		/*
-		 * usize isn't knowable before iralloc() returns when extra is
+		 * usize isn't knowable before ixalloc() returns when extra is
 		 * non-zero.  Therefore, compute its maximum possible value and
 		 * use that in PROF_ALLOC_PREP() to decide whether to capture a
 		 * backtrace.  prof_realloc() will use the actual usize to
 		 * decide whether to sample.
 		 */
 		size_t max_usize = (alignment == 0) ? s2u(size+extra) :
 		    sa2u(size+extra, alignment);
-		prof_ctx_t *old_ctx = prof_ctx_get(p);
-		old_size = isalloc(p, true);
-		if (config_valgrind && opt_valgrind)
-			old_rzsize = p2rz(p);
 		PROF_ALLOC_PREP(1, max_usize, cnt);
-		if (cnt == NULL)
-			goto label_oom;
-		/*
-		 * Use minimum usize to determine whether promotion may happen.
-		 */
-		if (prof_promote && (uintptr_t)cnt != (uintptr_t)1U
-		    && ((alignment == 0) ? s2u(size) : sa2u(size, alignment))
-		    <= SMALL_MAXCLASS) {
-			q = irallocx(p, SMALL_MAXCLASS+1, (SMALL_MAXCLASS+1 >=
-			    size+extra) ? 0 : size+extra - (SMALL_MAXCLASS+1),
-			    alignment, zero, no_move, try_tcache_alloc,
-			    try_tcache_dalloc, arena);
-			if (q == NULL)
-				goto label_err;
-			if (max_usize < PAGE) {
-				usize = max_usize;
-				arena_prof_promoted(q, usize);
-			} else
-				usize = isalloc(q, config_prof);
-		} else {
-			q = irallocx(p, size, extra, alignment, zero, no_move,
-			    try_tcache_alloc, try_tcache_dalloc, arena);
-			if (q == NULL)
-				goto label_err;
-			usize = isalloc(q, config_prof);
-		}
-		prof_realloc(q, usize, cnt, old_size, old_ctx);
-		if (rsize != NULL)
-			*rsize = usize;
+		usize = ixallocx_prof(ptr, old_usize, size, extra, alignment,
+		    max_usize, zero, arena, cnt);
 	} else {
-		if (config_stats) {
-			old_size = isalloc(p, false);
-			if (config_valgrind && opt_valgrind)
-				old_rzsize = u2rz(old_size);
-		} else if (config_valgrind && opt_valgrind) {
-			old_size = isalloc(p, false);
-			old_rzsize = u2rz(old_size);
-		}
-		q = irallocx(p, size, extra, alignment, zero, no_move,
-		    try_tcache_alloc, try_tcache_dalloc, arena);
-		if (q == NULL)
-			goto label_err;
-		if (config_stats)
-			usize = isalloc(q, config_prof);
-		if (rsize != NULL) {
-			if (config_stats == false)
-				usize = isalloc(q, config_prof);
-			*rsize = usize;
-		}
+		usize = ixallocx_helper(ptr, old_usize, size, extra, alignment,
+		    zero, arena);
 	}
+	if (usize == old_usize)
+		goto label_not_resized;
 
-	*ptr = q;
 	if (config_stats) {
 		thread_allocated_t *ta;
 		ta = thread_allocated_tsd_get();
 		ta->allocated += usize;
-		ta->deallocated += old_size;
-	}
-	UTRACE(p, size, q);
-	JEMALLOC_VALGRIND_REALLOC(q, usize, p, old_size, old_rzsize, zero);
-	return (ALLOCM_SUCCESS);
-label_err:
-	if (no_move) {
-		UTRACE(p, size, q);
-		return (ALLOCM_ERR_NOT_MOVED);
+		ta->deallocated += old_usize;
 	}
-label_oom:
-	if (config_xmalloc && opt_xmalloc) {
-		malloc_write("<jemalloc>: Error in rallocm(): "
-		    "out of memory\n");
-		abort();
-	}
-	UTRACE(p, size, 0);
-	return (ALLOCM_ERR_OOM);
+	JEMALLOC_VALGRIND_REALLOC(ptr, usize, ptr, old_usize, old_rzsize, zero);
+label_not_resized:
+	UTRACE(ptr, size, ptr);
+	return (usize);
 }
 
-int
-je_sallocm(const void *ptr, size_t *rsize, int flags)
+size_t
+je_sallocx(const void *ptr, int flags)
 {
-	size_t sz;
+	size_t usize;
 
 	assert(malloc_initialized || IS_INITIALIZER);
+	malloc_thread_init();
 
 	if (config_ivsalloc)
-		sz = ivsalloc(ptr, config_prof);
+		usize = ivsalloc(ptr, config_prof);
 	else {
 		assert(ptr != NULL);
-		sz = isalloc(ptr, config_prof);
+		usize = isalloc(ptr, config_prof);
 	}
-	assert(rsize != NULL);
-	*rsize = sz;
 
-	return (ALLOCM_SUCCESS);
+	return (usize);
 }
 
-int
-je_dallocm(void *ptr, int flags)
+void
+je_dallocx(void *ptr, int flags)
 {
 	size_t usize;
-	size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);
+	UNUSED size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);
 	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
 	bool try_tcache;
 
@@ -1645,28 +1786,162 @@ je_dallocm(void *ptr, int flags)
 		thread_allocated_tsd_get()->deallocated += usize;
 	if (config_valgrind && opt_valgrind)
 		rzsize = p2rz(ptr);
-	iqallocx(ptr, try_tcache);
+	iqalloct(ptr, try_tcache);
 	JEMALLOC_VALGRIND_FREE(ptr, rzsize);
-
-	return (ALLOCM_SUCCESS);
 }
 
-int
-je_nallocm(size_t *rsize, size_t size, int flags)
+size_t
+je_nallocx(size_t size, int flags)
 {
 	size_t usize;
-	size_t alignment = (ZU(1) << (flags & ALLOCM_LG_ALIGN_MASK)
+	size_t alignment = (ZU(1) << (flags & MALLOCX_LG_ALIGN_MASK)
 	    & (SIZE_T_MAX-1));
 
 	assert(size != 0);
 
 	if (malloc_init())
-		return (ALLOCM_ERR_OOM);
+		return (0);
 
 	usize = (alignment == 0) ? s2u(size) : sa2u(size, alignment);
-	if (usize == 0)
+	assert(usize != 0);
+	return (usize);
+}
+
+int
+je_mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp,
+    size_t newlen)
+{
+
+	if (malloc_init())
+		return (EAGAIN);
+
+	return (ctl_byname(name, oldp, oldlenp, newp, newlen));
+}
+
+int
+je_mallctlnametomib(const char *name, size_t *mibp, size_t *miblenp)
+{
+
+	if (malloc_init())
+		return (EAGAIN);
+
+	return (ctl_nametomib(name, mibp, miblenp));
+}
+
+int
+je_mallctlbymib(const size_t *mib, size_t miblen, void *oldp, size_t *oldlenp,
+  void *newp, size_t newlen)
+{
+
+	if (malloc_init())
+		return (EAGAIN);
+
+	return (ctl_bymib(mib, miblen, oldp, oldlenp, newp, newlen));
+}
+
+void
+je_malloc_stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
+    const char *opts)
+{
+
+	stats_print(write_cb, cbopaque, opts);
+}
+
+size_t
+je_malloc_usable_size(JEMALLOC_USABLE_SIZE_CONST void *ptr)
+{
+	size_t ret;
+
+	assert(malloc_initialized || IS_INITIALIZER);
+	malloc_thread_init();
+
+	if (config_ivsalloc)
+		ret = ivsalloc(ptr, config_prof);
+	else
+		ret = (ptr != NULL) ? isalloc(ptr, config_prof) : 0;
+
+	return (ret);
+}
+
+/*
+ * End non-standard functions.
+ */
+/******************************************************************************/
+/*
+ * Begin experimental functions.
+ */
+#ifdef JEMALLOC_EXPERIMENTAL
+
+int
+je_allocm(void **ptr, size_t *rsize, size_t size, int flags)
+{
+	void *p;
+
+	assert(ptr != NULL);
+
+	p = je_mallocx(size, flags);
+	if (p == NULL)
 		return (ALLOCM_ERR_OOM);
+	if (rsize != NULL)
+		*rsize = isalloc(p, config_prof);
+	*ptr = p;
+	return (ALLOCM_SUCCESS);
+}
+
+int
+je_rallocm(void **ptr, size_t *rsize, size_t size, size_t extra, int flags)
+{
+	int ret;
+	bool no_move = flags & ALLOCM_NO_MOVE;
 
+	assert(ptr != NULL);
+	assert(*ptr != NULL);
+	assert(size != 0);
+	assert(SIZE_T_MAX - size >= extra);
+
+	if (no_move) {
+		size_t usize = je_xallocx(*ptr, size, extra, flags);
+		ret = (usize >= size) ? ALLOCM_SUCCESS : ALLOCM_ERR_NOT_MOVED;
+		if (rsize != NULL)
+			*rsize = usize;
+	} else {
+		void *p = je_rallocx(*ptr, size+extra, flags);
+		if (p != NULL) {
+			*ptr = p;
+			ret = ALLOCM_SUCCESS;
+		} else
+			ret = ALLOCM_ERR_OOM;
+		if (rsize != NULL)
+			*rsize = isalloc(*ptr, config_prof);
+	}
+	return (ret);
+}
+
+int
+je_sallocm(const void *ptr, size_t *rsize, int flags)
+{
+
+	assert(rsize != NULL);
+	*rsize = je_sallocx(ptr, flags);
+	return (ALLOCM_SUCCESS);
+}
+
+int
+je_dallocm(void *ptr, int flags)
+{
+
+	je_dallocx(ptr, flags);
+	return (ALLOCM_SUCCESS);
+}
+
+int
+je_nallocm(size_t *rsize, size_t size, int flags)
+{
+	size_t usize;
+
+	usize = je_nallocx(size, flags);
+	if (usize == 0)
+		return (ALLOCM_ERR_OOM);
 	if (rsize != NULL)
 		*rsize = usize;
 	return (ALLOCM_SUCCESS);
@@ -1721,12 +1996,12 @@ _malloc_prefork(void)
 
 	/* Acquire all mutexes in a safe order. */
 	ctl_prefork();
+	prof_prefork();
 	malloc_mutex_prefork(&arenas_lock);
 	for (i = 0; i < narenas_total; i++) {
 		if (arenas[i] != NULL)
 			arena_prefork(arenas[i]);
 	}
-	prof_prefork();
 	chunk_prefork();
 	base_prefork();
 	huge_prefork();
@@ -1752,12 +2027,12 @@ _malloc_postfork(void)
 	huge_postfork_parent();
 	base_postfork_parent();
 	chunk_postfork_parent();
-	prof_postfork_parent();
 	for (i = 0; i < narenas_total; i++) {
 		if (arenas[i] != NULL)
 			arena_postfork_parent(arenas[i]);
 	}
 	malloc_mutex_postfork_parent(&arenas_lock);
+	prof_postfork_parent();
 	ctl_postfork_parent();
 }
 
@@ -1772,12 +2047,12 @@ jemalloc_postfork_child(void)
 	huge_postfork_child();
 	base_postfork_child();
 	chunk_postfork_child();
-	prof_postfork_child();
 	for (i = 0; i < narenas_total; i++) {
 		if (arenas[i] != NULL)
 			arena_postfork_child(arenas[i]);
 	}
 	malloc_mutex_postfork_child(&arenas_lock);
+	prof_postfork_child();
 	ctl_postfork_child();
 }
 
@@ -1801,7 +2076,7 @@ a0alloc(size_t size, bool zero)
 	if (size <= arena_maxclass)
 		return (arena_malloc(arenas[0], size, zero, false));
 	else
-		return (huge_malloc(size, zero));
+		return (huge_malloc(size, zero, huge_dss_prec_get(arenas[0])));
 }
 
 void *