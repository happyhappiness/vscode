@@ -33,7 +33,8 @@ unsigned	ncpus;
 
 malloc_mutex_t		arenas_lock;
 arena_t			**arenas;
-unsigned		narenas;
+unsigned		narenas_total;
+unsigned		narenas_auto;
 
 /* Set to true once the allocator has been initialized. */
 static bool		malloc_initialized = false;
@@ -144,14 +145,14 @@ choose_arena_hard(void)
 {
 	arena_t *ret;
 
-	if (narenas > 1) {
+	if (narenas_auto > 1) {
 		unsigned i, choose, first_null;
 
 		choose = 0;
-		first_null = narenas;
+		first_null = narenas_auto;
 		malloc_mutex_lock(&arenas_lock);
 		assert(arenas[0] != NULL);
-		for (i = 1; i < narenas; i++) {
+		for (i = 1; i < narenas_auto; i++) {
 			if (arenas[i] != NULL) {
 				/*
 				 * Choose the first arena that has the lowest
@@ -160,7 +161,7 @@ choose_arena_hard(void)
 				if (arenas[i]->nthreads <
 				    arenas[choose]->nthreads)
 					choose = i;
-			} else if (first_null == narenas) {
+			} else if (first_null == narenas_auto) {
 				/*
 				 * Record the index of the first uninitialized
 				 * arena, in case all extant arenas are in use.
@@ -174,7 +175,8 @@ choose_arena_hard(void)
 			}
 		}
 
-		if (arenas[choose]->nthreads == 0 || first_null == narenas) {
+		if (arenas[choose]->nthreads == 0
+		    || first_null == narenas_auto) {
 			/*
 			 * Use an unloaded arena, or the least loaded arena if
 			 * all arenas are already initialized.
@@ -203,7 +205,7 @@ stats_print_atexit(void)
 {
 
 	if (config_tcache && config_stats) {
-		unsigned i;
+		unsigned narenas, i;
 
 		/*
 		 * Merge stats from extant threads.  This is racy, since
@@ -212,7 +214,7 @@ stats_print_atexit(void)
 		 * out of date by the time they are reported, if other threads
 		 * continue to allocate.
 		 */
-		for (i = 0; i < narenas; i++) {
+		for (i = 0, narenas = narenas_total_get(); i < narenas; i++) {
 			arena_t *arena = arenas[i];
 			if (arena != NULL) {
 				tcache_t *tcache;
@@ -254,12 +256,13 @@ malloc_ncpus(void)
 	result = si.dwNumberOfProcessors;
 #else
 	result = sysconf(_SC_NPROCESSORS_ONLN);
+#endif
 	if (result == -1) {
 		/* Error. */
 		ret = 1;
-	}
-#endif
-	ret = (unsigned)result;
+	}  else {
+    ret = (unsigned)result;
+  }
 
 	return (ret);
 }
@@ -377,6 +380,22 @@ malloc_conf_init(void)
 	const char *opts, *k, *v;
 	size_t klen, vlen;
 
+	/*
+	 * Automatically configure valgrind before processing options.  The
+	 * valgrind option remains in jemalloc 3.x for compatibility reasons.
+	 */
+	if (config_valgrind) {
+		opt_valgrind = (RUNNING_ON_VALGRIND != 0) ? true : false;
+		if (config_fill && opt_valgrind) {
+			opt_junk = false;
+			assert(opt_zero == false);
+			opt_quarantine = JEMALLOC_VALGRIND_QUARANTINE_DEFAULT;
+			opt_redzone = true;
+		}
+		if (config_tcache && opt_valgrind)
+			opt_tcache = false;
+	}
+
 	for (i = 0; i < 3; i++) {
 		/* Get runtime configuration. */
 		switch (i) {
@@ -537,6 +556,30 @@ malloc_conf_init(void)
 			 */
 			CONF_HANDLE_SIZE_T(opt_lg_chunk, "lg_chunk", LG_PAGE +
 			    (config_fill ? 2 : 1), (sizeof(size_t) << 3) - 1)
+			if (strncmp("dss", k, klen) == 0) {
+				int i;
+				bool match = false;
+				for (i = 0; i < dss_prec_limit; i++) {
+					if (strncmp(dss_prec_names[i], v, vlen)
+					    == 0) {
+						if (chunk_dss_prec_set(i)) {
+							malloc_conf_error(
+							    "Error setting dss",
+							    k, klen, v, vlen);
+						} else {
+							opt_dss =
+							    dss_prec_names[i];
+							match = true;
+							break;
+						}
+					}
+				}
+				if (match == false) {
+					malloc_conf_error("Invalid conf value",
+					    k, klen, v, vlen);
+				}
+				continue;
+			}
 			CONF_HANDLE_SIZE_T(opt_narenas, "narenas", 1,
 			    SIZE_T_MAX)
 			CONF_HANDLE_SSIZE_T(opt_lg_dirty_mult, "lg_dirty_mult",
@@ -553,20 +596,7 @@ malloc_conf_init(void)
 				CONF_HANDLE_BOOL(opt_utrace, "utrace")
 			}
 			if (config_valgrind) {
-				bool hit;
-				CONF_HANDLE_BOOL_HIT(opt_valgrind,
-				    "valgrind", hit)
-				if (config_fill && opt_valgrind && hit) {
-					opt_junk = false;
-					opt_zero = false;
-					if (opt_quarantine == 0) {
-						opt_quarantine =
-						    JEMALLOC_VALGRIND_QUARANTINE_DEFAULT;
-					}
-					opt_redzone = true;
-				}
-				if (hit)
-					continue;
+				CONF_HANDLE_BOOL(opt_valgrind, "valgrind")
 			}
 			if (config_xmalloc) {
 				CONF_HANDLE_BOOL(opt_xmalloc, "xmalloc")
@@ -695,9 +725,9 @@ malloc_init_hard(void)
 	 * Create enough scaffolding to allow recursive allocation in
 	 * malloc_ncpus().
 	 */
-	narenas = 1;
+	narenas_total = narenas_auto = 1;
 	arenas = init_arenas;
-	memset(arenas, 0, sizeof(arena_t *) * narenas);
+	memset(arenas, 0, sizeof(arena_t *) * narenas_auto);
 
 	/*
 	 * Initialize one arena here.  The rest are lazily created in
@@ -755,20 +785,21 @@ malloc_init_hard(void)
 		else
 			opt_narenas = 1;
 	}
-	narenas = opt_narenas;
+	narenas_auto = opt_narenas;
 	/*
 	 * Make sure that the arenas array can be allocated.  In practice, this
 	 * limit is enough to allow the allocator to function, but the ctl
 	 * machinery will fail to allocate memory at far lower limits.
 	 */
-	if (narenas > chunksize / sizeof(arena_t *)) {
-		narenas = chunksize / sizeof(arena_t *);
+	if (narenas_auto > chunksize / sizeof(arena_t *)) {
+		narenas_auto = chunksize / sizeof(arena_t *);
 		malloc_printf("<jemalloc>: Reducing narenas to limit (%d)\n",
-		    narenas);
+		    narenas_auto);
 	}
+	narenas_total = narenas_auto;
 
 	/* Allocate and initialize arenas. */
-	arenas = (arena_t **)base_alloc(sizeof(arena_t *) * narenas);
+	arenas = (arena_t **)base_alloc(sizeof(arena_t *) * narenas_total);
 	if (arenas == NULL) {
 		malloc_mutex_unlock(&init_lock);
 		return (true);
@@ -777,7 +808,7 @@ malloc_init_hard(void)
 	 * Zero the array.  In practice, this should always be pre-zeroed,
 	 * since it was just mmap()ed, but let's be sure.
 	 */
-	memset(arenas, 0, sizeof(arena_t *) * narenas);
+	memset(arenas, 0, sizeof(arena_t *) * narenas_total);
 	/* Copy the pointer to the one arena that was already initialized. */
 	arenas[0] = init_arenas[0];
 
@@ -1262,11 +1293,10 @@ je_valloc(size_t size)
  * passed an extra argument for the caller return address, which will be
  * ignored.
  */
-JEMALLOC_EXPORT void (* const __free_hook)(void *ptr) = je_free;
-JEMALLOC_EXPORT void *(* const __malloc_hook)(size_t size) = je_malloc;
-JEMALLOC_EXPORT void *(* const __realloc_hook)(void *ptr, size_t size) =
-    je_realloc;
-JEMALLOC_EXPORT void *(* const __memalign_hook)(size_t alignment, size_t size) =
+JEMALLOC_EXPORT void (* __free_hook)(void *ptr) = je_free;
+JEMALLOC_EXPORT void *(* __malloc_hook)(size_t size) = je_malloc;
+JEMALLOC_EXPORT void *(* __realloc_hook)(void *ptr, size_t size) = je_realloc;
+JEMALLOC_EXPORT void *(* __memalign_hook)(size_t alignment, size_t size) =
     je_memalign;
 #endif
 
@@ -1279,7 +1309,7 @@ JEMALLOC_EXPORT void *(* const __memalign_hook)(size_t alignment, size_t size) =
  */
 
 size_t
-je_malloc_usable_size(const void *ptr)
+je_malloc_usable_size(JEMALLOC_USABLE_SIZE_CONST void *ptr)
 {
 	size_t ret;
 
@@ -1343,18 +1373,19 @@ je_mallctlbymib(const size_t *mib, size_t miblen, void *oldp, size_t *oldlenp,
 #ifdef JEMALLOC_EXPERIMENTAL
 
 JEMALLOC_INLINE void *
-iallocm(size_t usize, size_t alignment, bool zero)
+iallocm(size_t usize, size_t alignment, bool zero, bool try_tcache,
+    arena_t *arena)
 {
 
 	assert(usize == ((alignment == 0) ? s2u(usize) : sa2u(usize,
 	    alignment)));
 
 	if (alignment != 0)
-		return (ipalloc(usize, alignment, zero));
+		return (ipallocx(usize, alignment, zero, try_tcache, arena));
 	else if (zero)
-		return (icalloc(usize));
+		return (icallocx(usize, try_tcache, arena));
 	else
-		return (imalloc(usize));
+		return (imallocx(usize, try_tcache, arena));
 }
 
 int
@@ -1365,13 +1396,24 @@ je_allocm(void **ptr, size_t *rsize, size_t size, int flags)
 	size_t alignment = (ZU(1) << (flags & ALLOCM_LG_ALIGN_MASK)
 	    & (SIZE_T_MAX-1));
 	bool zero = flags & ALLOCM_ZERO;
+	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
+	arena_t *arena;
+	bool try_tcache;
 
 	assert(ptr != NULL);
 	assert(size != 0);
 
 	if (malloc_init())
 		goto label_oom;
 
+	if (arena_ind != UINT_MAX) {
+		arena = arenas[arena_ind];
+		try_tcache = false;
+	} else {
+		arena = NULL;
+		try_tcache = true;
+	}
+
 	usize = (alignment == 0) ? s2u(size) : sa2u(size, alignment);
 	if (usize == 0)
 		goto label_oom;
@@ -1388,18 +1430,19 @@ je_allocm(void **ptr, size_t *rsize, size_t size, int flags)
 			    s2u(SMALL_MAXCLASS+1) : sa2u(SMALL_MAXCLASS+1,
 			    alignment);
 			assert(usize_promoted != 0);
-			p = iallocm(usize_promoted, alignment, zero);
+			p = iallocm(usize_promoted, alignment, zero,
+			    try_tcache, arena);
 			if (p == NULL)
 				goto label_oom;
 			arena_prof_promoted(p, usize);
 		} else {
-			p = iallocm(usize, alignment, zero);
+			p = iallocm(usize, alignment, zero, try_tcache, arena);
 			if (p == NULL)
 				goto label_oom;
 		}
 		prof_malloc(p, usize, cnt);
 	} else {
-		p = iallocm(usize, alignment, zero);
+		p = iallocm(usize, alignment, zero, try_tcache, arena);
 		if (p == NULL)
 			goto label_oom;
 	}
@@ -1436,13 +1479,29 @@ je_rallocm(void **ptr, size_t *rsize, size_t size, size_t extra, int flags)
 	    & (SIZE_T_MAX-1));
 	bool zero = flags & ALLOCM_ZERO;
 	bool no_move = flags & ALLOCM_NO_MOVE;
+	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
+	bool try_tcache_alloc, try_tcache_dalloc;
+	arena_t *arena;
 
 	assert(ptr != NULL);
 	assert(*ptr != NULL);
 	assert(size != 0);
 	assert(SIZE_T_MAX - size >= extra);
 	assert(malloc_initialized || IS_INITIALIZER);
 
+	if (arena_ind != UINT_MAX) {
+		arena_chunk_t *chunk;
+		try_tcache_alloc = true;
+		chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(*ptr);
+		try_tcache_dalloc = (chunk == *ptr || chunk->arena !=
+		    arenas[arena_ind]);
+		arena = arenas[arena_ind];
+	} else {
+		try_tcache_alloc = true;
+		try_tcache_dalloc = true;
+		arena = NULL;
+	}
+
 	p = *ptr;
 	if (config_prof && opt_prof) {
 		prof_thr_cnt_t *cnt;
@@ -1469,9 +1528,10 @@ je_rallocm(void **ptr, size_t *rsize, size_t size, size_t extra, int flags)
 		if (prof_promote && (uintptr_t)cnt != (uintptr_t)1U
 		    && ((alignment == 0) ? s2u(size) : sa2u(size, alignment))
 		    <= SMALL_MAXCLASS) {
-			q = iralloc(p, SMALL_MAXCLASS+1, (SMALL_MAXCLASS+1 >=
+			q = irallocx(p, SMALL_MAXCLASS+1, (SMALL_MAXCLASS+1 >=
 			    size+extra) ? 0 : size+extra - (SMALL_MAXCLASS+1),
-			    alignment, zero, no_move);
+			    alignment, zero, no_move, try_tcache_alloc,
+			    try_tcache_dalloc, arena);
 			if (q == NULL)
 				goto label_err;
 			if (max_usize < PAGE) {
@@ -1480,7 +1540,8 @@ je_rallocm(void **ptr, size_t *rsize, size_t size, size_t extra, int flags)
 			} else
 				usize = isalloc(q, config_prof);
 		} else {
-			q = iralloc(p, size, extra, alignment, zero, no_move);
+			q = irallocx(p, size, extra, alignment, zero, no_move,
+			    try_tcache_alloc, try_tcache_dalloc, arena);
 			if (q == NULL)
 				goto label_err;
 			usize = isalloc(q, config_prof);
@@ -1497,7 +1558,8 @@ je_rallocm(void **ptr, size_t *rsize, size_t size, size_t extra, int flags)
 			old_size = isalloc(p, false);
 			old_rzsize = u2rz(old_size);
 		}
-		q = iralloc(p, size, extra, alignment, zero, no_move);
+		q = irallocx(p, size, extra, alignment, zero, no_move,
+		    try_tcache_alloc, try_tcache_dalloc, arena);
 		if (q == NULL)
 			goto label_err;
 		if (config_stats)
@@ -1558,10 +1620,19 @@ je_dallocm(void *ptr, int flags)
 {
 	size_t usize;
 	size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);
+	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
+	bool try_tcache;
 
 	assert(ptr != NULL);
 	assert(malloc_initialized || IS_INITIALIZER);
 
+	if (arena_ind != UINT_MAX) {
+		arena_chunk_t *chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
+		try_tcache = (chunk == ptr || chunk->arena !=
+		    arenas[arena_ind]);
+	} else
+		try_tcache = true;
+
 	UTRACE(ptr, 0, 0);
 	if (config_stats || config_valgrind)
 		usize = isalloc(ptr, config_prof);
@@ -1574,7 +1645,7 @@ je_dallocm(void *ptr, int flags)
 		thread_allocated_tsd_get()->deallocated += usize;
 	if (config_valgrind && opt_valgrind)
 		rzsize = p2rz(ptr);
-	iqalloc(ptr);
+	iqallocx(ptr, try_tcache);
 	JEMALLOC_VALGRIND_FREE(ptr, rzsize);
 
 	return (ALLOCM_SUCCESS);
@@ -1611,6 +1682,27 @@ je_nallocm(size_t *rsize, size_t size, int flags)
  * malloc during fork().
  */
 
+/*
+ * If an application creates a thread before doing any allocation in the main
+ * thread, then calls fork(2) in the main thread followed by memory allocation
+ * in the child process, a race can occur that results in deadlock within the
+ * child: the main thread may have forked while the created thread had
+ * partially initialized the allocator.  Ordinarily jemalloc prevents
+ * fork/malloc races via the following functions it registers during
+ * initialization using pthread_atfork(), but of course that does no good if
+ * the allocator isn't fully initialized at fork time.  The following library
+ * constructor is a partial solution to this problem.  It may still possible to
+ * trigger the deadlock described above, but doing so would involve forking via
+ * a library constructor that runs before jemalloc's runs.
+ */
+JEMALLOC_ATTR(constructor)
+static void
+jemalloc_constructor(void)
+{
+
+	malloc_init();
+}
+
 #ifndef JEMALLOC_MUTEX_INIT_CB
 void
 jemalloc_prefork(void)
@@ -1628,14 +1720,16 @@ _malloc_prefork(void)
 	assert(malloc_initialized);
 
 	/* Acquire all mutexes in a safe order. */
+	ctl_prefork();
 	malloc_mutex_prefork(&arenas_lock);
-	for (i = 0; i < narenas; i++) {
+	for (i = 0; i < narenas_total; i++) {
 		if (arenas[i] != NULL)
 			arena_prefork(arenas[i]);
 	}
+	prof_prefork();
+	chunk_prefork();
 	base_prefork();
 	huge_prefork();
-	chunk_dss_prefork();
 }
 
 #ifndef JEMALLOC_MUTEX_INIT_CB
@@ -1655,14 +1749,16 @@ _malloc_postfork(void)
 	assert(malloc_initialized);
 
 	/* Release all mutexes, now that fork() has completed. */
-	chunk_dss_postfork_parent();
 	huge_postfork_parent();
 	base_postfork_parent();
-	for (i = 0; i < narenas; i++) {
+	chunk_postfork_parent();
+	prof_postfork_parent();
+	for (i = 0; i < narenas_total; i++) {
 		if (arenas[i] != NULL)
 			arena_postfork_parent(arenas[i]);
 	}
 	malloc_mutex_postfork_parent(&arenas_lock);
+	ctl_postfork_parent();
 }
 
 void
@@ -1673,14 +1769,16 @@ jemalloc_postfork_child(void)
 	assert(malloc_initialized);
 
 	/* Release all mutexes, now that fork() has completed. */
-	chunk_dss_postfork_child();
 	huge_postfork_child();
 	base_postfork_child();
-	for (i = 0; i < narenas; i++) {
+	chunk_postfork_child();
+	prof_postfork_child();
+	for (i = 0; i < narenas_total; i++) {
 		if (arenas[i] != NULL)
 			arena_postfork_child(arenas[i]);
 	}
 	malloc_mutex_postfork_child(&arenas_lock);
+	ctl_postfork_child();
 }
 
 /******************************************************************************/