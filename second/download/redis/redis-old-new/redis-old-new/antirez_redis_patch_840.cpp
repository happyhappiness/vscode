@@ -24,9 +24,14 @@ bool		opt_prof_gdump = false;
 bool		opt_prof_final = true;
 bool		opt_prof_leak = false;
 bool		opt_prof_accum = false;
-char		opt_prof_prefix[PATH_MAX + 1];
+char		opt_prof_prefix[
+    /* Minimize memory bloat for non-prof builds. */
+#ifdef JEMALLOC_PROF
+    PATH_MAX +
+#endif
+    1];
 
-uint64_t	prof_interval;
+uint64_t	prof_interval = 0;
 bool		prof_promote;
 
 /*
@@ -54,48 +59,24 @@ static uint64_t		prof_dump_useq;
 
 /*
  * This buffer is rather large for stack allocation, so use a single buffer for
- * all profile dumps.  The buffer is implicitly protected by bt2ctx_mtx, since
- * it must be locked anyway during dumping.
+ * all profile dumps.
  */
-static char		prof_dump_buf[PROF_DUMP_BUFSIZE];
+static malloc_mutex_t	prof_dump_mtx;
+static char		prof_dump_buf[
+    /* Minimize memory bloat for non-prof builds. */
+#ifdef JEMALLOC_PROF
+    PROF_DUMP_BUFSIZE
+#else
+    1
+#endif
+];
 static unsigned		prof_dump_buf_end;
 static int		prof_dump_fd;
 
 /* Do not dump any profiles until bootstrapping is complete. */
 static bool		prof_booted = false;
 
 /******************************************************************************/
-/* Function prototypes for non-inline static functions. */
-
-static prof_bt_t	*bt_dup(prof_bt_t *bt);
-static void	bt_destroy(prof_bt_t *bt);
-#ifdef JEMALLOC_PROF_LIBGCC
-static _Unwind_Reason_Code	prof_unwind_init_callback(
-    struct _Unwind_Context *context, void *arg);
-static _Unwind_Reason_Code	prof_unwind_callback(
-    struct _Unwind_Context *context, void *arg);
-#endif
-static bool	prof_flush(bool propagate_err);
-static bool	prof_write(bool propagate_err, const char *s);
-static bool	prof_printf(bool propagate_err, const char *format, ...)
-    JEMALLOC_ATTR(format(printf, 2, 3));
-static void	prof_ctx_sum(prof_ctx_t *ctx, prof_cnt_t *cnt_all,
-    size_t *leak_nctx);
-static void	prof_ctx_destroy(prof_ctx_t *ctx);
-static void	prof_ctx_merge(prof_ctx_t *ctx, prof_thr_cnt_t *cnt);
-static bool	prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx,
-    prof_bt_t *bt);
-static bool	prof_dump_maps(bool propagate_err);
-static bool	prof_dump(bool propagate_err, const char *filename,
-    bool leakcheck);
-static void	prof_dump_filename(char *filename, char v, int64_t vseq);
-static void	prof_fdump(void);
-static void	prof_bt_hash(const void *key, unsigned minbits, size_t *hash1,
-    size_t *hash2);
-static bool	prof_bt_keycomp(const void *k1, const void *k2);
-static malloc_mutex_t	*prof_ctx_mutex_choose(void);
-
-/******************************************************************************/
 
 void
 bt_init(prof_bt_t *bt, void **vec)
@@ -424,10 +405,169 @@ prof_backtrace(prof_bt_t *bt, unsigned nignore)
 {
 
 	cassert(config_prof);
-	assert(false);
+	not_reached();
 }
 #endif
 
+static malloc_mutex_t *
+prof_ctx_mutex_choose(void)
+{
+	unsigned nctxs = atomic_add_u(&cum_ctxs, 1);
+
+	return (&ctx_locks[(nctxs - 1) % PROF_NCTX_LOCKS]);
+}
+
+static void
+prof_ctx_init(prof_ctx_t *ctx, prof_bt_t *bt)
+{
+
+	ctx->bt = bt;
+	ctx->lock = prof_ctx_mutex_choose();
+	/*
+	 * Set nlimbo to 1, in order to avoid a race condition with
+	 * prof_ctx_merge()/prof_ctx_destroy().
+	 */
+	ctx->nlimbo = 1;
+	ql_elm_new(ctx, dump_link);
+	memset(&ctx->cnt_merged, 0, sizeof(prof_cnt_t));
+	ql_new(&ctx->cnts_ql);
+}
+
+static void
+prof_ctx_destroy(prof_ctx_t *ctx)
+{
+	prof_tdata_t *prof_tdata;
+
+	cassert(config_prof);
+
+	/*
+	 * Check that ctx is still unused by any thread cache before destroying
+	 * it.  prof_lookup() increments ctx->nlimbo in order to avoid a race
+	 * condition with this function, as does prof_ctx_merge() in order to
+	 * avoid a race between the main body of prof_ctx_merge() and entry
+	 * into this function.
+	 */
+	prof_tdata = prof_tdata_get(false);
+	assert((uintptr_t)prof_tdata > (uintptr_t)PROF_TDATA_STATE_MAX);
+	prof_enter(prof_tdata);
+	malloc_mutex_lock(ctx->lock);
+	if (ql_first(&ctx->cnts_ql) == NULL && ctx->cnt_merged.curobjs == 0 &&
+	    ctx->nlimbo == 1) {
+		assert(ctx->cnt_merged.curbytes == 0);
+		assert(ctx->cnt_merged.accumobjs == 0);
+		assert(ctx->cnt_merged.accumbytes == 0);
+		/* Remove ctx from bt2ctx. */
+		if (ckh_remove(&bt2ctx, ctx->bt, NULL, NULL))
+			not_reached();
+		prof_leave(prof_tdata);
+		/* Destroy ctx. */
+		malloc_mutex_unlock(ctx->lock);
+		bt_destroy(ctx->bt);
+		idalloc(ctx);
+	} else {
+		/*
+		 * Compensate for increment in prof_ctx_merge() or
+		 * prof_lookup().
+		 */
+		ctx->nlimbo--;
+		malloc_mutex_unlock(ctx->lock);
+		prof_leave(prof_tdata);
+	}
+}
+
+static void
+prof_ctx_merge(prof_ctx_t *ctx, prof_thr_cnt_t *cnt)
+{
+	bool destroy;
+
+	cassert(config_prof);
+
+	/* Merge cnt stats and detach from ctx. */
+	malloc_mutex_lock(ctx->lock);
+	ctx->cnt_merged.curobjs += cnt->cnts.curobjs;
+	ctx->cnt_merged.curbytes += cnt->cnts.curbytes;
+	ctx->cnt_merged.accumobjs += cnt->cnts.accumobjs;
+	ctx->cnt_merged.accumbytes += cnt->cnts.accumbytes;
+	ql_remove(&ctx->cnts_ql, cnt, cnts_link);
+	if (opt_prof_accum == false && ql_first(&ctx->cnts_ql) == NULL &&
+	    ctx->cnt_merged.curobjs == 0 && ctx->nlimbo == 0) {
+		/*
+		 * Increment ctx->nlimbo in order to keep another thread from
+		 * winning the race to destroy ctx while this one has ctx->lock
+		 * dropped.  Without this, it would be possible for another
+		 * thread to:
+		 *
+		 * 1) Sample an allocation associated with ctx.
+		 * 2) Deallocate the sampled object.
+		 * 3) Successfully prof_ctx_destroy(ctx).
+		 *
+		 * The result would be that ctx no longer exists by the time
+		 * this thread accesses it in prof_ctx_destroy().
+		 */
+		ctx->nlimbo++;
+		destroy = true;
+	} else
+		destroy = false;
+	malloc_mutex_unlock(ctx->lock);
+	if (destroy)
+		prof_ctx_destroy(ctx);
+}
+
+static bool
+prof_lookup_global(prof_bt_t *bt, prof_tdata_t *prof_tdata, void **p_btkey,
+    prof_ctx_t **p_ctx, bool *p_new_ctx)
+{
+	union {
+		prof_ctx_t	*p;
+		void		*v;
+	} ctx;
+	union {
+		prof_bt_t	*p;
+		void		*v;
+	} btkey;
+	bool new_ctx;
+
+	prof_enter(prof_tdata);
+	if (ckh_search(&bt2ctx, bt, &btkey.v, &ctx.v)) {
+		/* bt has never been seen before.  Insert it. */
+		ctx.v = imalloc(sizeof(prof_ctx_t));
+		if (ctx.v == NULL) {
+			prof_leave(prof_tdata);
+			return (true);
+		}
+		btkey.p = bt_dup(bt);
+		if (btkey.v == NULL) {
+			prof_leave(prof_tdata);
+			idalloc(ctx.v);
+			return (true);
+		}
+		prof_ctx_init(ctx.p, btkey.p);
+		if (ckh_insert(&bt2ctx, btkey.v, ctx.v)) {
+			/* OOM. */
+			prof_leave(prof_tdata);
+			idalloc(btkey.v);
+			idalloc(ctx.v);
+			return (true);
+		}
+		new_ctx = true;
+	} else {
+		/*
+		 * Increment nlimbo, in order to avoid a race condition with
+		 * prof_ctx_merge()/prof_ctx_destroy().
+		 */
+		malloc_mutex_lock(ctx.p->lock);
+		ctx.p->nlimbo++;
+		malloc_mutex_unlock(ctx.p->lock);
+		new_ctx = false;
+	}
+	prof_leave(prof_tdata);
+
+	*p_btkey = btkey.v;
+	*p_ctx = ctx.p;
+	*p_new_ctx = new_ctx;
+	return (false);
+}
+
 prof_thr_cnt_t *
 prof_lookup(prof_bt_t *bt)
 {
@@ -439,67 +579,21 @@ prof_lookup(prof_bt_t *bt)
 
 	cassert(config_prof);
 
-	prof_tdata = prof_tdata_get();
+	prof_tdata = prof_tdata_get(false);
 	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
 		return (NULL);
 
 	if (ckh_search(&prof_tdata->bt2cnt, bt, NULL, &ret.v)) {
-		union {
-			prof_bt_t	*p;
-			void		*v;
-		} btkey;
-		union {
-			prof_ctx_t	*p;
-			void		*v;
-		} ctx;
+		void *btkey;
+		prof_ctx_t *ctx;
 		bool new_ctx;
 
 		/*
 		 * This thread's cache lacks bt.  Look for it in the global
 		 * cache.
 		 */
-		prof_enter(prof_tdata);
-		if (ckh_search(&bt2ctx, bt, &btkey.v, &ctx.v)) {
-			/* bt has never been seen before.  Insert it. */
-			ctx.v = imalloc(sizeof(prof_ctx_t));
-			if (ctx.v == NULL) {
-				prof_leave(prof_tdata);
-				return (NULL);
-			}
-			btkey.p = bt_dup(bt);
-			if (btkey.v == NULL) {
-				prof_leave(prof_tdata);
-				idalloc(ctx.v);
-				return (NULL);
-			}
-			ctx.p->bt = btkey.p;
-			ctx.p->lock = prof_ctx_mutex_choose();
-			/*
-			 * Set nlimbo to 1, in order to avoid a race condition
-			 * with prof_ctx_merge()/prof_ctx_destroy().
-			 */
-			ctx.p->nlimbo = 1;
-			memset(&ctx.p->cnt_merged, 0, sizeof(prof_cnt_t));
-			ql_new(&ctx.p->cnts_ql);
-			if (ckh_insert(&bt2ctx, btkey.v, ctx.v)) {
-				/* OOM. */
-				prof_leave(prof_tdata);
-				idalloc(btkey.v);
-				idalloc(ctx.v);
-				return (NULL);
-			}
-			new_ctx = true;
-		} else {
-			/*
-			 * Increment nlimbo, in order to avoid a race condition
-			 * with prof_ctx_merge()/prof_ctx_destroy().
-			 */
-			malloc_mutex_lock(ctx.p->lock);
-			ctx.p->nlimbo++;
-			malloc_mutex_unlock(ctx.p->lock);
-			new_ctx = false;
-		}
-		prof_leave(prof_tdata);
+		if (prof_lookup_global(bt, prof_tdata, &btkey, &ctx, &new_ctx))
+			return (NULL);
 
 		/* Link a prof_thd_cnt_t into ctx for this thread. */
 		if (ckh_count(&prof_tdata->bt2cnt) == PROF_TCMAX) {
@@ -512,7 +606,7 @@ prof_lookup(prof_bt_t *bt)
 			assert(ret.v != NULL);
 			if (ckh_remove(&prof_tdata->bt2cnt, ret.p->ctx->bt,
 			    NULL, NULL))
-				assert(false);
+				not_reached();
 			ql_remove(&prof_tdata->lru_ql, ret.p, lru_link);
 			prof_ctx_merge(ret.p->ctx, ret.p);
 			/* ret can now be re-used. */
@@ -522,27 +616,27 @@ prof_lookup(prof_bt_t *bt)
 			ret.v = imalloc(sizeof(prof_thr_cnt_t));
 			if (ret.p == NULL) {
 				if (new_ctx)
-					prof_ctx_destroy(ctx.p);
+					prof_ctx_destroy(ctx);
 				return (NULL);
 			}
 			ql_elm_new(ret.p, cnts_link);
 			ql_elm_new(ret.p, lru_link);
 		}
 		/* Finish initializing ret. */
-		ret.p->ctx = ctx.p;
+		ret.p->ctx = ctx;
 		ret.p->epoch = 0;
 		memset(&ret.p->cnts, 0, sizeof(prof_cnt_t));
-		if (ckh_insert(&prof_tdata->bt2cnt, btkey.v, ret.v)) {
+		if (ckh_insert(&prof_tdata->bt2cnt, btkey, ret.v)) {
 			if (new_ctx)
-				prof_ctx_destroy(ctx.p);
+				prof_ctx_destroy(ctx);
 			idalloc(ret.v);
 			return (NULL);
 		}
 		ql_head_insert(&prof_tdata->lru_ql, ret.p, lru_link);
-		malloc_mutex_lock(ctx.p->lock);
-		ql_tail_insert(&ctx.p->cnts_ql, ret.p, cnts_link);
-		ctx.p->nlimbo--;
-		malloc_mutex_unlock(ctx.p->lock);
+		malloc_mutex_lock(ctx->lock);
+		ql_tail_insert(&ctx->cnts_ql, ret.p, cnts_link);
+		ctx->nlimbo--;
+		malloc_mutex_unlock(ctx->lock);
 	} else {
 		/* Move ret to the front of the LRU. */
 		ql_remove(&prof_tdata->lru_ql, ret.p, lru_link);
@@ -552,8 +646,52 @@ prof_lookup(prof_bt_t *bt)
 	return (ret.p);
 }
 
+#ifdef JEMALLOC_JET
+size_t
+prof_bt_count(void)
+{
+	size_t bt_count;
+	prof_tdata_t *prof_tdata;
+
+	prof_tdata = prof_tdata_get(false);
+	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
+		return (0);
+
+	prof_enter(prof_tdata);
+	bt_count = ckh_count(&bt2ctx);
+	prof_leave(prof_tdata);
+
+	return (bt_count);
+}
+#endif
+
+#ifdef JEMALLOC_JET
+#undef prof_dump_open
+#define	prof_dump_open JEMALLOC_N(prof_dump_open_impl)
+#endif
+static int
+prof_dump_open(bool propagate_err, const char *filename)
+{
+	int fd;
+
+	fd = creat(filename, 0644);
+	if (fd == -1 && propagate_err == false) {
+		malloc_printf("<jemalloc>: creat(\"%s\"), 0644) failed\n",
+		    filename);
+		if (opt_abort)
+			abort();
+	}
+
+	return (fd);
+}
+#ifdef JEMALLOC_JET
+#undef prof_dump_open
+#define	prof_dump_open JEMALLOC_N(prof_dump_open)
+prof_dump_open_t *prof_dump_open = JEMALLOC_N(prof_dump_open_impl);
+#endif
+
 static bool
-prof_flush(bool propagate_err)
+prof_dump_flush(bool propagate_err)
 {
 	bool ret = false;
 	ssize_t err;
@@ -576,7 +714,20 @@ prof_flush(bool propagate_err)
 }
 
 static bool
-prof_write(bool propagate_err, const char *s)
+prof_dump_close(bool propagate_err)
+{
+	bool ret;
+
+	assert(prof_dump_fd != -1);
+	ret = prof_dump_flush(propagate_err);
+	close(prof_dump_fd);
+	prof_dump_fd = -1;
+
+	return (ret);
+}
+
+static bool
+prof_dump_write(bool propagate_err, const char *s)
 {
 	unsigned i, slen, n;
 
@@ -587,7 +738,7 @@ prof_write(bool propagate_err, const char *s)
 	while (i < slen) {
 		/* Flush the buffer if it is full. */
 		if (prof_dump_buf_end == PROF_DUMP_BUFSIZE)
-			if (prof_flush(propagate_err) && propagate_err)
+			if (prof_dump_flush(propagate_err) && propagate_err)
 				return (true);
 
 		if (prof_dump_buf_end + slen <= PROF_DUMP_BUFSIZE) {
@@ -607,7 +758,7 @@ prof_write(bool propagate_err, const char *s)
 
 JEMALLOC_ATTR(format(printf, 2, 3))
 static bool
-prof_printf(bool propagate_err, const char *format, ...)
+prof_dump_printf(bool propagate_err, const char *format, ...)
 {
 	bool ret;
 	va_list ap;
@@ -616,13 +767,14 @@ prof_printf(bool propagate_err, const char *format, ...)
 	va_start(ap, format);
 	malloc_vsnprintf(buf, sizeof(buf), format, ap);
 	va_end(ap);
-	ret = prof_write(propagate_err, buf);
+	ret = prof_dump_write(propagate_err, buf);
 
 	return (ret);
 }
 
 static void
-prof_ctx_sum(prof_ctx_t *ctx, prof_cnt_t *cnt_all, size_t *leak_nctx)
+prof_dump_ctx_prep(prof_ctx_t *ctx, prof_cnt_t *cnt_all, size_t *leak_nctx,
+    prof_ctx_list_t *ctx_ql)
 {
 	prof_thr_cnt_t *thr_cnt;
 	prof_cnt_t tcnt;
@@ -631,6 +783,14 @@ prof_ctx_sum(prof_ctx_t *ctx, prof_cnt_t *cnt_all, size_t *leak_nctx)
 
 	malloc_mutex_lock(ctx->lock);
 
+	/*
+	 * Increment nlimbo so that ctx won't go away before dump.
+	 * Additionally, link ctx into the dump list so that it is included in
+	 * prof_dump()'s second pass.
+	 */
+	ctx->nlimbo++;
+	ql_tail_insert(ctx_ql, ctx, dump_link);
+
 	memcpy(&ctx->cnt_summed, &ctx->cnt_merged, sizeof(prof_cnt_t));
 	ql_foreach(thr_cnt, &ctx->cnts_ql, cnts_link) {
 		volatile unsigned *epoch = &thr_cnt->epoch;
@@ -671,89 +831,52 @@ prof_ctx_sum(prof_ctx_t *ctx, prof_cnt_t *cnt_all, size_t *leak_nctx)
 	malloc_mutex_unlock(ctx->lock);
 }
 
-static void
-prof_ctx_destroy(prof_ctx_t *ctx)
+static bool
+prof_dump_header(bool propagate_err, const prof_cnt_t *cnt_all)
 {
-	prof_tdata_t *prof_tdata;
-
-	cassert(config_prof);
 
-	/*
-	 * Check that ctx is still unused by any thread cache before destroying
-	 * it.  prof_lookup() increments ctx->nlimbo in order to avoid a race
-	 * condition with this function, as does prof_ctx_merge() in order to
-	 * avoid a race between the main body of prof_ctx_merge() and entry
-	 * into this function.
-	 */
-	prof_tdata = *prof_tdata_tsd_get();
-	assert((uintptr_t)prof_tdata > (uintptr_t)PROF_TDATA_STATE_MAX);
-	prof_enter(prof_tdata);
-	malloc_mutex_lock(ctx->lock);
-	if (ql_first(&ctx->cnts_ql) == NULL && ctx->cnt_merged.curobjs == 0 &&
-	    ctx->nlimbo == 1) {
-		assert(ctx->cnt_merged.curbytes == 0);
-		assert(ctx->cnt_merged.accumobjs == 0);
-		assert(ctx->cnt_merged.accumbytes == 0);
-		/* Remove ctx from bt2ctx. */
-		if (ckh_remove(&bt2ctx, ctx->bt, NULL, NULL))
-			assert(false);
-		prof_leave(prof_tdata);
-		/* Destroy ctx. */
-		malloc_mutex_unlock(ctx->lock);
-		bt_destroy(ctx->bt);
-		idalloc(ctx);
+	if (opt_lg_prof_sample == 0) {
+		if (prof_dump_printf(propagate_err,
+		    "heap profile: %"PRId64": %"PRId64
+		    " [%"PRIu64": %"PRIu64"] @ heapprofile\n",
+		    cnt_all->curobjs, cnt_all->curbytes,
+		    cnt_all->accumobjs, cnt_all->accumbytes))
+			return (true);
 	} else {
-		/*
-		 * Compensate for increment in prof_ctx_merge() or
-		 * prof_lookup().
-		 */
-		ctx->nlimbo--;
-		malloc_mutex_unlock(ctx->lock);
-		prof_leave(prof_tdata);
+		if (prof_dump_printf(propagate_err,
+		    "heap profile: %"PRId64": %"PRId64
+		    " [%"PRIu64": %"PRIu64"] @ heap_v2/%"PRIu64"\n",
+		    cnt_all->curobjs, cnt_all->curbytes,
+		    cnt_all->accumobjs, cnt_all->accumbytes,
+		    ((uint64_t)1U << opt_lg_prof_sample)))
+			return (true);
 	}
+
+	return (false);
 }
 
 static void
-prof_ctx_merge(prof_ctx_t *ctx, prof_thr_cnt_t *cnt)
+prof_dump_ctx_cleanup_locked(prof_ctx_t *ctx, prof_ctx_list_t *ctx_ql)
 {
-	bool destroy;
 
-	cassert(config_prof);
+	ctx->nlimbo--;
+	ql_remove(ctx_ql, ctx, dump_link);
+}
+
+static void
+prof_dump_ctx_cleanup(prof_ctx_t *ctx, prof_ctx_list_t *ctx_ql)
+{
 
-	/* Merge cnt stats and detach from ctx. */
 	malloc_mutex_lock(ctx->lock);
-	ctx->cnt_merged.curobjs += cnt->cnts.curobjs;
-	ctx->cnt_merged.curbytes += cnt->cnts.curbytes;
-	ctx->cnt_merged.accumobjs += cnt->cnts.accumobjs;
-	ctx->cnt_merged.accumbytes += cnt->cnts.accumbytes;
-	ql_remove(&ctx->cnts_ql, cnt, cnts_link);
-	if (opt_prof_accum == false && ql_first(&ctx->cnts_ql) == NULL &&
-	    ctx->cnt_merged.curobjs == 0 && ctx->nlimbo == 0) {
-		/*
-		 * Increment ctx->nlimbo in order to keep another thread from
-		 * winning the race to destroy ctx while this one has ctx->lock
-		 * dropped.  Without this, it would be possible for another
-		 * thread to:
-		 *
-		 * 1) Sample an allocation associated with ctx.
-		 * 2) Deallocate the sampled object.
-		 * 3) Successfully prof_ctx_destroy(ctx).
-		 *
-		 * The result would be that ctx no longer exists by the time
-		 * this thread accesses it in prof_ctx_destroy().
-		 */
-		ctx->nlimbo++;
-		destroy = true;
-	} else
-		destroy = false;
+	prof_dump_ctx_cleanup_locked(ctx, ctx_ql);
 	malloc_mutex_unlock(ctx->lock);
-	if (destroy)
-		prof_ctx_destroy(ctx);
 }
 
 static bool
-prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, prof_bt_t *bt)
+prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, const prof_bt_t *bt,
+    prof_ctx_list_t *ctx_ql)
 {
+	bool ret;
 	unsigned i;
 
 	cassert(config_prof);
@@ -765,66 +888,109 @@ prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, prof_bt_t *bt)
 	 * filled in.  Avoid dumping any ctx that is an artifact of either
 	 * implementation detail.
 	 */
+	malloc_mutex_lock(ctx->lock);
 	if ((opt_prof_accum == false && ctx->cnt_summed.curobjs == 0) ||
 	    (opt_prof_accum && ctx->cnt_summed.accumobjs == 0)) {
 		assert(ctx->cnt_summed.curobjs == 0);
 		assert(ctx->cnt_summed.curbytes == 0);
 		assert(ctx->cnt_summed.accumobjs == 0);
 		assert(ctx->cnt_summed.accumbytes == 0);
-		return (false);
+		ret = false;
+		goto label_return;
 	}
 
-	if (prof_printf(propagate_err, "%"PRId64": %"PRId64
+	if (prof_dump_printf(propagate_err, "%"PRId64": %"PRId64
 	    " [%"PRIu64": %"PRIu64"] @",
 	    ctx->cnt_summed.curobjs, ctx->cnt_summed.curbytes,
-	    ctx->cnt_summed.accumobjs, ctx->cnt_summed.accumbytes))
-		return (true);
+	    ctx->cnt_summed.accumobjs, ctx->cnt_summed.accumbytes)) {
+		ret = true;
+		goto label_return;
+	}
 
 	for (i = 0; i < bt->len; i++) {
-		if (prof_printf(propagate_err, " %#"PRIxPTR,
-		    (uintptr_t)bt->vec[i]))
-			return (true);
+		if (prof_dump_printf(propagate_err, " %#"PRIxPTR,
+		    (uintptr_t)bt->vec[i])) {
+			ret = true;
+			goto label_return;
+		}
 	}
 
-	if (prof_write(propagate_err, "\n"))
-		return (true);
+	if (prof_dump_write(propagate_err, "\n")) {
+		ret = true;
+		goto label_return;
+	}
 
-	return (false);
+	ret = false;
+label_return:
+	prof_dump_ctx_cleanup_locked(ctx, ctx_ql);
+	malloc_mutex_unlock(ctx->lock);
+	return (ret);
 }
 
 static bool
 prof_dump_maps(bool propagate_err)
 {
+	bool ret;
 	int mfd;
 	char filename[PATH_MAX + 1];
 
 	cassert(config_prof);
-
+#ifdef __FreeBSD__
+	malloc_snprintf(filename, sizeof(filename), "/proc/curproc/map");
+#else
 	malloc_snprintf(filename, sizeof(filename), "/proc/%d/maps",
 	    (int)getpid());
+#endif
 	mfd = open(filename, O_RDONLY);
 	if (mfd != -1) {
 		ssize_t nread;
 
-		if (prof_write(propagate_err, "\nMAPPED_LIBRARIES:\n") &&
-		    propagate_err)
-			return (true);
+		if (prof_dump_write(propagate_err, "\nMAPPED_LIBRARIES:\n") &&
+		    propagate_err) {
+			ret = true;
+			goto label_return;
+		}
 		nread = 0;
 		do {
 			prof_dump_buf_end += nread;
 			if (prof_dump_buf_end == PROF_DUMP_BUFSIZE) {
 				/* Make space in prof_dump_buf before read(). */
-				if (prof_flush(propagate_err) && propagate_err)
-					return (true);
+				if (prof_dump_flush(propagate_err) &&
+				    propagate_err) {
+					ret = true;
+					goto label_return;
+				}
 			}
 			nread = read(mfd, &prof_dump_buf[prof_dump_buf_end],
 			    PROF_DUMP_BUFSIZE - prof_dump_buf_end);
 		} while (nread > 0);
+	} else {
+		ret = true;
+		goto label_return;
+	}
+
+	ret = false;
+label_return:
+	if (mfd != -1)
 		close(mfd);
-	} else
-		return (true);
+	return (ret);
+}
 
-	return (false);
+static void
+prof_leakcheck(const prof_cnt_t *cnt_all, size_t leak_nctx,
+    const char *filename)
+{
+
+	if (cnt_all->curbytes != 0) {
+		malloc_printf("<jemalloc>: Leak summary: %"PRId64" byte%s, %"
+		    PRId64" object%s, %zu context%s\n",
+		    cnt_all->curbytes, (cnt_all->curbytes != 1) ? "s" : "",
+		    cnt_all->curobjs, (cnt_all->curobjs != 1) ? "s" : "",
+		    leak_nctx, (leak_nctx != 1) ? "s" : "");
+		malloc_printf(
+		    "<jemalloc>: Run pprof on \"%s\" for leak detail\n",
+		    filename);
+	}
 }
 
 static bool
@@ -834,98 +1000,74 @@ prof_dump(bool propagate_err, const char *filename, bool leakcheck)
 	prof_cnt_t cnt_all;
 	size_t tabind;
 	union {
-		prof_bt_t	*p;
-		void		*v;
-	} bt;
-	union {
 		prof_ctx_t	*p;
 		void		*v;
 	} ctx;
 	size_t leak_nctx;
+	prof_ctx_list_t ctx_ql;
 
 	cassert(config_prof);
 
-	prof_tdata = prof_tdata_get();
+	prof_tdata = prof_tdata_get(false);
 	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
 		return (true);
-	prof_enter(prof_tdata);
-	prof_dump_fd = creat(filename, 0644);
-	if (prof_dump_fd == -1) {
-		if (propagate_err == false) {
-			malloc_printf(
-			    "<jemalloc>: creat(\"%s\"), 0644) failed\n",
-			    filename);
-			if (opt_abort)
-				abort();
-		}
-		goto label_error;
-	}
+
+	malloc_mutex_lock(&prof_dump_mtx);
 
 	/* Merge per thread profile stats, and sum them in cnt_all. */
 	memset(&cnt_all, 0, sizeof(prof_cnt_t));
 	leak_nctx = 0;
+	ql_new(&ctx_ql);
+	prof_enter(prof_tdata);
 	for (tabind = 0; ckh_iter(&bt2ctx, &tabind, NULL, &ctx.v) == false;)
-		prof_ctx_sum(ctx.p, &cnt_all, &leak_nctx);
+		prof_dump_ctx_prep(ctx.p, &cnt_all, &leak_nctx, &ctx_ql);
+	prof_leave(prof_tdata);
+
+	/* Create dump file. */
+	if ((prof_dump_fd = prof_dump_open(propagate_err, filename)) == -1)
+		goto label_open_close_error;
 
 	/* Dump profile header. */
-	if (opt_lg_prof_sample == 0) {
-		if (prof_printf(propagate_err,
-		    "heap profile: %"PRId64": %"PRId64
-		    " [%"PRIu64": %"PRIu64"] @ heapprofile\n",
-		    cnt_all.curobjs, cnt_all.curbytes,
-		    cnt_all.accumobjs, cnt_all.accumbytes))
-			goto label_error;
-	} else {
-		if (prof_printf(propagate_err,
-		    "heap profile: %"PRId64": %"PRId64
-		    " [%"PRIu64": %"PRIu64"] @ heap_v2/%"PRIu64"\n",
-		    cnt_all.curobjs, cnt_all.curbytes,
-		    cnt_all.accumobjs, cnt_all.accumbytes,
-		    ((uint64_t)1U << opt_lg_prof_sample)))
-			goto label_error;
-	}
+	if (prof_dump_header(propagate_err, &cnt_all))
+		goto label_write_error;
 
-	/* Dump  per ctx profile stats. */
-	for (tabind = 0; ckh_iter(&bt2ctx, &tabind, &bt.v, &ctx.v)
-	    == false;) {
-		if (prof_dump_ctx(propagate_err, ctx.p, bt.p))
-			goto label_error;
+	/* Dump per ctx profile stats. */
+	while ((ctx.p = ql_first(&ctx_ql)) != NULL) {
+		if (prof_dump_ctx(propagate_err, ctx.p, ctx.p->bt, &ctx_ql))
+			goto label_write_error;
 	}
 
 	/* Dump /proc/<pid>/maps if possible. */
 	if (prof_dump_maps(propagate_err))
-		goto label_error;
+		goto label_write_error;
 
-	if (prof_flush(propagate_err))
-		goto label_error;
-	close(prof_dump_fd);
-	prof_leave(prof_tdata);
+	if (prof_dump_close(propagate_err))
+		goto label_open_close_error;
 
-	if (leakcheck && cnt_all.curbytes != 0) {
-		malloc_printf("<jemalloc>: Leak summary: %"PRId64" byte%s, %"
-		    PRId64" object%s, %zu context%s\n",
-		    cnt_all.curbytes, (cnt_all.curbytes != 1) ? "s" : "",
-		    cnt_all.curobjs, (cnt_all.curobjs != 1) ? "s" : "",
-		    leak_nctx, (leak_nctx != 1) ? "s" : "");
-		malloc_printf(
-		    "<jemalloc>: Run pprof on \"%s\" for leak detail\n",
-		    filename);
-	}
+	malloc_mutex_unlock(&prof_dump_mtx);
+
+	if (leakcheck)
+		prof_leakcheck(&cnt_all, leak_nctx, filename);
 
 	return (false);
-label_error:
-	prof_leave(prof_tdata);
+label_write_error:
+	prof_dump_close(propagate_err);
+label_open_close_error:
+	while ((ctx.p = ql_first(&ctx_ql)) != NULL)
+		prof_dump_ctx_cleanup(ctx.p, &ctx_ql);
+	malloc_mutex_unlock(&prof_dump_mtx);
 	return (true);
 }
 
 #define	DUMP_FILENAME_BUFSIZE	(PATH_MAX + 1)
+#define	VSEQ_INVALID		UINT64_C(0xffffffffffffffff)
 static void
 prof_dump_filename(char *filename, char v, int64_t vseq)
 {
 
 	cassert(config_prof);
 
-	if (vseq != UINT64_C(0xffffffffffffffff)) {
+	if (vseq != VSEQ_INVALID) {
 	        /* "<prefix>.<pid>.<seq>.v<vseq>.heap" */
 		malloc_snprintf(filename, DUMP_FILENAME_BUFSIZE,
 		    "%s.%d.%"PRIu64".%c%"PRId64".heap",
@@ -951,7 +1093,7 @@ prof_fdump(void)
 
 	if (opt_prof_final && opt_prof_prefix[0] != '\0') {
 		malloc_mutex_lock(&prof_dump_seq_mtx);
-		prof_dump_filename(filename, 'f', UINT64_C(0xffffffffffffffff));
+		prof_dump_filename(filename, 'f', VSEQ_INVALID);
 		malloc_mutex_unlock(&prof_dump_seq_mtx);
 		prof_dump(false, filename, opt_prof_leak);
 	}
@@ -967,11 +1109,7 @@ prof_idump(void)
 
 	if (prof_booted == false)
 		return;
-	/*
-	 * Don't call prof_tdata_get() here, because it could cause recursive
-	 * allocation.
-	 */
-	prof_tdata = *prof_tdata_tsd_get();
+	prof_tdata = prof_tdata_get(false);
 	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
 		return;
 	if (prof_tdata->enq) {
@@ -1021,11 +1159,7 @@ prof_gdump(void)
 
 	if (prof_booted == false)
 		return;
-	/*
-	 * Don't call prof_tdata_get() here, because it could cause recursive
-	 * allocation.
-	 */
-	prof_tdata = *prof_tdata_tsd_get();
+	prof_tdata = prof_tdata_get(false);
 	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
 		return;
 	if (prof_tdata->enq) {
@@ -1043,34 +1177,13 @@ prof_gdump(void)
 }
 
 static void
-prof_bt_hash(const void *key, unsigned minbits, size_t *hash1, size_t *hash2)
+prof_bt_hash(const void *key, size_t r_hash[2])
 {
-	size_t ret1, ret2;
-	uint64_t h;
 	prof_bt_t *bt = (prof_bt_t *)key;
 
 	cassert(config_prof);
-	assert(minbits <= 32 || (SIZEOF_PTR == 8 && minbits <= 64));
-	assert(hash1 != NULL);
-	assert(hash2 != NULL);
 
-	h = hash(bt->vec, bt->len * sizeof(void *),
-	    UINT64_C(0x94122f335b332aea));
-	if (minbits <= 32) {
-		/*
-		 * Avoid doing multiple hashes, since a single hash provides
-		 * enough bits.
-		 */
-		ret1 = h & ZU(0xffffffffU);
-		ret2 = h >> 32;
-	} else {
-		ret1 = h;
-		ret2 = hash(bt->vec, bt->len * sizeof(void *),
-		    UINT64_C(0x8432a476666bbc13));
-	}
-
-	*hash1 = ret1;
-	*hash2 = ret2;
+	hash(bt->vec, bt->len * sizeof(void *), 0x94122f33U, r_hash);
 }
 
 static bool
@@ -1086,14 +1199,6 @@ prof_bt_keycomp(const void *k1, const void *k2)
 	return (memcmp(bt1->vec, bt2->vec, bt1->len * sizeof(void *)) == 0);
 }
 
-static malloc_mutex_t *
-prof_ctx_mutex_choose(void)
-{
-	unsigned nctxs = atomic_add_u(&cum_ctxs, 1);
-
-	return (&ctx_locks[(nctxs - 1) % PROF_NCTX_LOCKS]);
-}
-
 prof_tdata_t *
 prof_tdata_init(void)
 {
@@ -1206,13 +1311,11 @@ prof_boot1(void)
 		 */
 		opt_prof = true;
 		opt_prof_gdump = false;
-		prof_interval = 0;
 	} else if (opt_prof) {
 		if (opt_lg_prof_interval >= 0) {
 			prof_interval = (((uint64_t)1U) <<
 			    opt_lg_prof_interval);
-		} else
-			prof_interval = 0;
+		}
 	}
 
 	prof_promote = (opt_prof && opt_lg_prof_sample > LG_PAGE);
@@ -1240,6 +1343,8 @@ prof_boot2(void)
 
 		if (malloc_mutex_init(&prof_dump_seq_mtx))
 			return (true);
+		if (malloc_mutex_init(&prof_dump_mtx))
+			return (true);
 
 		if (atexit(prof_fdump) != 0) {
 			malloc_write("<jemalloc>: Error in atexit()\n");
@@ -1277,10 +1382,10 @@ prof_prefork(void)
 	if (opt_prof) {
 		unsigned i;
 
-		malloc_mutex_lock(&bt2ctx_mtx);
-		malloc_mutex_lock(&prof_dump_seq_mtx);
+		malloc_mutex_prefork(&bt2ctx_mtx);
+		malloc_mutex_prefork(&prof_dump_seq_mtx);
 		for (i = 0; i < PROF_NCTX_LOCKS; i++)
-			malloc_mutex_lock(&ctx_locks[i]);
+			malloc_mutex_prefork(&ctx_locks[i]);
 	}
 }
 