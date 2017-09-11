@@ -206,6 +206,7 @@ stats_arena_print(void (*write_cb)(void *, const char *), void *cbopaque,
     unsigned i, bool bins, bool large)
 {
 	unsigned nthreads;
+	const char *dss;
 	size_t page, pactive, pdirty, mapped;
 	uint64_t npurge, nmadvise, purged;
 	size_t small_allocated;
@@ -218,6 +219,9 @@ stats_arena_print(void (*write_cb)(void *, const char *), void *cbopaque,
 	CTL_I_GET("stats.arenas.0.nthreads", &nthreads, unsigned);
 	malloc_cprintf(write_cb, cbopaque,
 	    "assigned threads: %u\n", nthreads);
+	CTL_I_GET("stats.arenas.0.dss", &dss, const char *);
+	malloc_cprintf(write_cb, cbopaque, "dss allocation precedence: %s\n",
+	    dss);
 	CTL_I_GET("stats.arenas.0.pactive", &pactive, size_t);
 	CTL_I_GET("stats.arenas.0.pdirty", &pdirty, size_t);
 	CTL_I_GET("stats.arenas.0.npurge", &npurge, uint64_t);
@@ -370,6 +374,7 @@ stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
 		    "Run-time option settings:\n");
 		OPT_WRITE_BOOL(abort)
 		OPT_WRITE_SIZE_T(lg_chunk)
+		OPT_WRITE_CHAR_P(dss)
 		OPT_WRITE_SIZE_T(narenas)
 		OPT_WRITE_SSIZE_T(lg_dirty_mult)
 		OPT_WRITE_BOOL(stats_print)
@@ -400,7 +405,7 @@ stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
 		malloc_cprintf(write_cb, cbopaque, "CPUs: %u\n", ncpus);
 
 		CTL_GET("arenas.narenas", &uv, unsigned);
-		malloc_cprintf(write_cb, cbopaque, "Max arenas: %u\n", uv);
+		malloc_cprintf(write_cb, cbopaque, "Arenas: %u\n", uv);
 
 		malloc_cprintf(write_cb, cbopaque, "Pointer size: %zu\n",
 		    sizeof(void *));
@@ -472,7 +477,8 @@ stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
 		CTL_GET("stats.chunks.current", &chunks_current, size_t);
 		malloc_cprintf(write_cb, cbopaque, "chunks: nchunks   "
 		    "highchunks    curchunks\n");
-		malloc_cprintf(write_cb, cbopaque, "  %13"PRIu64"%13zu%13zu\n",
+		malloc_cprintf(write_cb, cbopaque,
+		    "  %13"PRIu64" %12zu %12zu\n",
 		    chunks_total, chunks_high, chunks_current);
 
 		/* Print huge stats. */