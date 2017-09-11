@@ -38,52 +38,18 @@ const uint8_t	small_size2bin[] = {
 };
 
 /******************************************************************************/
-/* Function prototypes for non-inline static functions. */
-
-static void	arena_avail_insert(arena_t *arena, arena_chunk_t *chunk,
-    size_t pageind, size_t npages, bool maybe_adjac_pred,
-    bool maybe_adjac_succ);
-static void	arena_avail_remove(arena_t *arena, arena_chunk_t *chunk,
-    size_t pageind, size_t npages, bool maybe_adjac_pred,
-    bool maybe_adjac_succ);
-static void	arena_run_split(arena_t *arena, arena_run_t *run, size_t size,
-    bool large, size_t binind, bool zero);
-static arena_chunk_t *arena_chunk_alloc(arena_t *arena);
-static void	arena_chunk_dealloc(arena_t *arena, arena_chunk_t *chunk);
-static arena_run_t	*arena_run_alloc_helper(arena_t *arena, size_t size,
-    bool large, size_t binind, bool zero);
-static arena_run_t *arena_run_alloc(arena_t *arena, size_t size, bool large,
-    size_t binind, bool zero);
-static arena_chunk_t	*chunks_dirty_iter_cb(arena_chunk_tree_t *tree,
-    arena_chunk_t *chunk, void *arg);
+/*
+ * Function prototypes for static functions that are referenced prior to
+ * definition.
+ */
+
 static void	arena_purge(arena_t *arena, bool all);
 static void	arena_run_dalloc(arena_t *arena, arena_run_t *run, bool dirty,
     bool cleaned);
-static void	arena_run_trim_head(arena_t *arena, arena_chunk_t *chunk,
-    arena_run_t *run, size_t oldsize, size_t newsize);
-static void	arena_run_trim_tail(arena_t *arena, arena_chunk_t *chunk,
-    arena_run_t *run, size_t oldsize, size_t newsize, bool dirty);
-static arena_run_t	*arena_bin_runs_first(arena_bin_t *bin);
-static void	arena_bin_runs_insert(arena_bin_t *bin, arena_run_t *run);
-static void	arena_bin_runs_remove(arena_bin_t *bin, arena_run_t *run);
-static arena_run_t *arena_bin_nonfull_run_tryget(arena_bin_t *bin);
-static arena_run_t *arena_bin_nonfull_run_get(arena_t *arena, arena_bin_t *bin);
-static void	*arena_bin_malloc_hard(arena_t *arena, arena_bin_t *bin);
-static void	arena_dissociate_bin_run(arena_chunk_t *chunk, arena_run_t *run,
-    arena_bin_t *bin);
 static void	arena_dalloc_bin_run(arena_t *arena, arena_chunk_t *chunk,
     arena_run_t *run, arena_bin_t *bin);
 static void	arena_bin_lower_run(arena_t *arena, arena_chunk_t *chunk,
     arena_run_t *run, arena_bin_t *bin);
-static void	arena_ralloc_large_shrink(arena_t *arena, arena_chunk_t *chunk,
-    void *ptr, size_t oldsize, size_t size);
-static bool	arena_ralloc_large_grow(arena_t *arena, arena_chunk_t *chunk,
-    void *ptr, size_t oldsize, size_t size, size_t extra, bool zero);
-static bool	arena_ralloc_large(void *ptr, size_t oldsize, size_t size,
-    size_t extra, bool zero);
-static size_t	bin_info_run_size_calc(arena_bin_info_t *bin_info,
-    size_t min_run_size);
-static void	bin_info_init(void);
 
 /******************************************************************************/
 
@@ -359,60 +325,73 @@ arena_run_reg_dalloc(arena_run_t *run, void *ptr)
 }
 
 static inline void
-arena_chunk_validate_zeroed(arena_chunk_t *chunk, size_t run_ind)
+arena_run_zero(arena_chunk_t *chunk, size_t run_ind, size_t npages)
+{
+
+	VALGRIND_MAKE_MEM_UNDEFINED((void *)((uintptr_t)chunk + (run_ind <<
+	    LG_PAGE)), (npages << LG_PAGE));
+	memset((void *)((uintptr_t)chunk + (run_ind << LG_PAGE)), 0,
+	    (npages << LG_PAGE));
+}
+
+static inline void
+arena_run_page_mark_zeroed(arena_chunk_t *chunk, size_t run_ind)
+{
+
+	VALGRIND_MAKE_MEM_DEFINED((void *)((uintptr_t)chunk + (run_ind <<
+	    LG_PAGE)), PAGE);
+}
+
+static inline void
+arena_run_page_validate_zeroed(arena_chunk_t *chunk, size_t run_ind)
 {
 	size_t i;
 	UNUSED size_t *p = (size_t *)((uintptr_t)chunk + (run_ind << LG_PAGE));
 
+	arena_run_page_mark_zeroed(chunk, run_ind);
 	for (i = 0; i < PAGE / sizeof(size_t); i++)
 		assert(p[i] == 0);
 }
 
 static void
-arena_run_split(arena_t *arena, arena_run_t *run, size_t size, bool large,
-    size_t binind, bool zero)
+arena_cactive_update(arena_t *arena, size_t add_pages, size_t sub_pages)
 {
-	arena_chunk_t *chunk;
-	size_t run_ind, total_pages, need_pages, rem_pages, i;
-	size_t flag_dirty;
 
-	assert((large && binind == BININD_INVALID) || (large == false && binind
-	    != BININD_INVALID));
+	if (config_stats) {
+		ssize_t cactive_diff = CHUNK_CEILING((arena->nactive +
+		    add_pages) << LG_PAGE) - CHUNK_CEILING((arena->nactive -
+		    sub_pages) << LG_PAGE);
+		if (cactive_diff != 0)
+			stats_cactive_add(cactive_diff);
+	}
+}
+
+static void
+arena_run_split_remove(arena_t *arena, arena_chunk_t *chunk, size_t run_ind,
+    size_t flag_dirty, size_t need_pages)
+{
+	size_t total_pages, rem_pages;
 
-	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(run);
-	run_ind = (unsigned)(((uintptr_t)run - (uintptr_t)chunk) >> LG_PAGE);
-	flag_dirty = arena_mapbits_dirty_get(chunk, run_ind);
 	total_pages = arena_mapbits_unallocated_size_get(chunk, run_ind) >>
 	    LG_PAGE;
 	assert(arena_mapbits_dirty_get(chunk, run_ind+total_pages-1) ==
 	    flag_dirty);
-	need_pages = (size >> LG_PAGE);
-	assert(need_pages > 0);
 	assert(need_pages <= total_pages);
 	rem_pages = total_pages - need_pages;
 
 	arena_avail_remove(arena, chunk, run_ind, total_pages, true, true);
-	if (config_stats) {
-		/*
-		 * Update stats_cactive if nactive is crossing a chunk
-		 * multiple.
-		 */
-		size_t cactive_diff = CHUNK_CEILING((arena->nactive +
-		    need_pages) << LG_PAGE) - CHUNK_CEILING(arena->nactive <<
-		    LG_PAGE);
-		if (cactive_diff != 0)
-			stats_cactive_add(cactive_diff);
-	}
+	arena_cactive_update(arena, need_pages, 0);
 	arena->nactive += need_pages;
 
 	/* Keep track of trailing unused pages for later use. */
 	if (rem_pages > 0) {
 		if (flag_dirty != 0) {
-			arena_mapbits_unallocated_set(chunk, run_ind+need_pages,
-			    (rem_pages << LG_PAGE), CHUNK_MAP_DIRTY);
+			arena_mapbits_unallocated_set(chunk,
+			    run_ind+need_pages, (rem_pages << LG_PAGE),
+			    flag_dirty);
 			arena_mapbits_unallocated_set(chunk,
 			    run_ind+total_pages-1, (rem_pages << LG_PAGE),
-			    CHUNK_MAP_DIRTY);
+			    flag_dirty);
 		} else {
 			arena_mapbits_unallocated_set(chunk, run_ind+need_pages,
 			    (rem_pages << LG_PAGE),
@@ -426,156 +405,219 @@ arena_run_split(arena_t *arena, arena_run_t *run, size_t size, bool large,
 		arena_avail_insert(arena, chunk, run_ind+need_pages, rem_pages,
 		    false, true);
 	}
+}
 
-	/*
-	 * Update the page map separately for large vs. small runs, since it is
-	 * possible to avoid iteration for large mallocs.
-	 */
-	if (large) {
-		if (zero) {
-			if (flag_dirty == 0) {
-				/*
-				 * The run is clean, so some pages may be
-				 * zeroed (i.e. never before touched).
-				 */
-				for (i = 0; i < need_pages; i++) {
-					if (arena_mapbits_unzeroed_get(chunk,
-					    run_ind+i) != 0) {
-						VALGRIND_MAKE_MEM_UNDEFINED(
-						    (void *)((uintptr_t)
-						    chunk + ((run_ind+i) <<
-						    LG_PAGE)), PAGE);
-						memset((void *)((uintptr_t)
-						    chunk + ((run_ind+i) <<
-						    LG_PAGE)), 0, PAGE);
-					} else if (config_debug) {
-						VALGRIND_MAKE_MEM_DEFINED(
-						    (void *)((uintptr_t)
-						    chunk + ((run_ind+i) <<
-						    LG_PAGE)), PAGE);
-						arena_chunk_validate_zeroed(
-						    chunk, run_ind+i);
-					}
+static void
+arena_run_split_large_helper(arena_t *arena, arena_run_t *run, size_t size,
+    bool remove, bool zero)
+{
+	arena_chunk_t *chunk;
+	size_t flag_dirty, run_ind, need_pages, i;
+
+	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(run);
+	run_ind = (unsigned)(((uintptr_t)run - (uintptr_t)chunk) >> LG_PAGE);
+	flag_dirty = arena_mapbits_dirty_get(chunk, run_ind);
+	need_pages = (size >> LG_PAGE);
+	assert(need_pages > 0);
+
+	if (remove) {
+		arena_run_split_remove(arena, chunk, run_ind, flag_dirty,
+		    need_pages);
+	}
+
+	if (zero) {
+		if (flag_dirty == 0) {
+			/*
+			 * The run is clean, so some pages may be zeroed (i.e.
+			 * never before touched).
+			 */
+			for (i = 0; i < need_pages; i++) {
+				if (arena_mapbits_unzeroed_get(chunk, run_ind+i)
+				    != 0)
+					arena_run_zero(chunk, run_ind+i, 1);
+				else if (config_debug) {
+					arena_run_page_validate_zeroed(chunk,
+					    run_ind+i);
+				} else {
+					arena_run_page_mark_zeroed(chunk,
+					    run_ind+i);
 				}
-			} else {
-				/*
-				 * The run is dirty, so all pages must be
-				 * zeroed.
-				 */
-				VALGRIND_MAKE_MEM_UNDEFINED((void
-				    *)((uintptr_t)chunk + (run_ind <<
-				    LG_PAGE)), (need_pages << LG_PAGE));
-				memset((void *)((uintptr_t)chunk + (run_ind <<
-				    LG_PAGE)), 0, (need_pages << LG_PAGE));
 			}
+		} else {
+			/* The run is dirty, so all pages must be zeroed. */
+			arena_run_zero(chunk, run_ind, need_pages);
 		}
-
-		/*
-		 * Set the last element first, in case the run only contains one
-		 * page (i.e. both statements set the same element).
-		 */
-		arena_mapbits_large_set(chunk, run_ind+need_pages-1, 0,
-		    flag_dirty);
-		arena_mapbits_large_set(chunk, run_ind, size, flag_dirty);
 	} else {
-		assert(zero == false);
-		/*
-		 * Propagate the dirty and unzeroed flags to the allocated
-		 * small run, so that arena_dalloc_bin_run() has the ability to
-		 * conditionally trim clean pages.
-		 */
-		arena_mapbits_small_set(chunk, run_ind, 0, binind, flag_dirty);
-		/*
-		 * The first page will always be dirtied during small run
-		 * initialization, so a validation failure here would not
-		 * actually cause an observable failure.
-		 */
-		if (config_debug && flag_dirty == 0 &&
-		    arena_mapbits_unzeroed_get(chunk, run_ind) == 0)
-			arena_chunk_validate_zeroed(chunk, run_ind);
-		for (i = 1; i < need_pages - 1; i++) {
-			arena_mapbits_small_set(chunk, run_ind+i, i, binind, 0);
-			if (config_debug && flag_dirty == 0 &&
-			    arena_mapbits_unzeroed_get(chunk, run_ind+i) == 0)
-				arena_chunk_validate_zeroed(chunk, run_ind+i);
-		}
-		arena_mapbits_small_set(chunk, run_ind+need_pages-1,
-		    need_pages-1, binind, flag_dirty);
-		if (config_debug && flag_dirty == 0 &&
-		    arena_mapbits_unzeroed_get(chunk, run_ind+need_pages-1) ==
-		    0) {
-			arena_chunk_validate_zeroed(chunk,
-			    run_ind+need_pages-1);
-		}
+		VALGRIND_MAKE_MEM_UNDEFINED((void *)((uintptr_t)chunk +
+		    (run_ind << LG_PAGE)), (need_pages << LG_PAGE));
 	}
+
+	/*
+	 * Set the last element first, in case the run only contains one page
+	 * (i.e. both statements set the same element).
+	 */
+	arena_mapbits_large_set(chunk, run_ind+need_pages-1, 0, flag_dirty);
+	arena_mapbits_large_set(chunk, run_ind, size, flag_dirty);
+}
+
+static void
+arena_run_split_large(arena_t *arena, arena_run_t *run, size_t size, bool zero)
+{
+
+	arena_run_split_large_helper(arena, run, size, true, zero);
+}
+
+static void
+arena_run_init_large(arena_t *arena, arena_run_t *run, size_t size, bool zero)
+{
+
+	arena_run_split_large_helper(arena, run, size, false, zero);
+}
+
+static void
+arena_run_split_small(arena_t *arena, arena_run_t *run, size_t size,
+    size_t binind)
+{
+	arena_chunk_t *chunk;
+	size_t flag_dirty, run_ind, need_pages, i;
+
+	assert(binind != BININD_INVALID);
+
+	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(run);
+	run_ind = (unsigned)(((uintptr_t)run - (uintptr_t)chunk) >> LG_PAGE);
+	flag_dirty = arena_mapbits_dirty_get(chunk, run_ind);
+	need_pages = (size >> LG_PAGE);
+	assert(need_pages > 0);
+
+	arena_run_split_remove(arena, chunk, run_ind, flag_dirty, need_pages);
+
+	/*
+	 * Propagate the dirty and unzeroed flags to the allocated small run,
+	 * so that arena_dalloc_bin_run() has the ability to conditionally trim
+	 * clean pages.
+	 */
+	arena_mapbits_small_set(chunk, run_ind, 0, binind, flag_dirty);
+	/*
+	 * The first page will always be dirtied during small run
+	 * initialization, so a validation failure here would not actually
+	 * cause an observable failure.
+	 */
+	if (config_debug && flag_dirty == 0 && arena_mapbits_unzeroed_get(chunk,
+	    run_ind) == 0)
+		arena_run_page_validate_zeroed(chunk, run_ind);
+	for (i = 1; i < need_pages - 1; i++) {
+		arena_mapbits_small_set(chunk, run_ind+i, i, binind, 0);
+		if (config_debug && flag_dirty == 0 &&
+		    arena_mapbits_unzeroed_get(chunk, run_ind+i) == 0)
+			arena_run_page_validate_zeroed(chunk, run_ind+i);
+	}
+	arena_mapbits_small_set(chunk, run_ind+need_pages-1, need_pages-1,
+	    binind, flag_dirty);
+	if (config_debug && flag_dirty == 0 && arena_mapbits_unzeroed_get(chunk,
+	    run_ind+need_pages-1) == 0)
+		arena_run_page_validate_zeroed(chunk, run_ind+need_pages-1);
+	VALGRIND_MAKE_MEM_UNDEFINED((void *)((uintptr_t)chunk +
+	    (run_ind << LG_PAGE)), (need_pages << LG_PAGE));
 }
 
 static arena_chunk_t *
-arena_chunk_alloc(arena_t *arena)
+arena_chunk_init_spare(arena_t *arena)
 {
 	arena_chunk_t *chunk;
-	size_t i;
 
-	if (arena->spare != NULL) {
-		chunk = arena->spare;
-		arena->spare = NULL;
+	assert(arena->spare != NULL);
 
-		assert(arena_mapbits_allocated_get(chunk, map_bias) == 0);
-		assert(arena_mapbits_allocated_get(chunk, chunk_npages-1) == 0);
-		assert(arena_mapbits_unallocated_size_get(chunk, map_bias) ==
-		    arena_maxclass);
-		assert(arena_mapbits_unallocated_size_get(chunk,
-		    chunk_npages-1) == arena_maxclass);
-		assert(arena_mapbits_dirty_get(chunk, map_bias) ==
-		    arena_mapbits_dirty_get(chunk, chunk_npages-1));
-	} else {
-		bool zero;
-		size_t unzeroed;
+	chunk = arena->spare;
+	arena->spare = NULL;
 
-		zero = false;
-		malloc_mutex_unlock(&arena->lock);
-		chunk = (arena_chunk_t *)chunk_alloc(chunksize, chunksize,
-		    false, &zero, arena->dss_prec);
-		malloc_mutex_lock(&arena->lock);
-		if (chunk == NULL)
-			return (NULL);
-		if (config_stats)
-			arena->stats.mapped += chunksize;
+	assert(arena_mapbits_allocated_get(chunk, map_bias) == 0);
+	assert(arena_mapbits_allocated_get(chunk, chunk_npages-1) == 0);
+	assert(arena_mapbits_unallocated_size_get(chunk, map_bias) ==
+	    arena_maxclass);
+	assert(arena_mapbits_unallocated_size_get(chunk, chunk_npages-1) ==
+	    arena_maxclass);
+	assert(arena_mapbits_dirty_get(chunk, map_bias) ==
+	    arena_mapbits_dirty_get(chunk, chunk_npages-1));
 
-		chunk->arena = arena;
+	return (chunk);
+}
 
-		/*
-		 * Claim that no pages are in use, since the header is merely
-		 * overhead.
-		 */
-		chunk->ndirty = 0;
+static arena_chunk_t *
+arena_chunk_init_hard(arena_t *arena)
+{
+	arena_chunk_t *chunk;
+	bool zero;
+	size_t unzeroed, i;
 
-		chunk->nruns_avail = 0;
-		chunk->nruns_adjac = 0;
+	assert(arena->spare == NULL);
 
-		/*
-		 * Initialize the map to contain one maximal free untouched run.
-		 * Mark the pages as zeroed iff chunk_alloc() returned a zeroed
-		 * chunk.
-		 */
-		unzeroed = zero ? 0 : CHUNK_MAP_UNZEROED;
-		arena_mapbits_unallocated_set(chunk, map_bias, arena_maxclass,
-		    unzeroed);
-		/*
-		 * There is no need to initialize the internal page map entries
-		 * unless the chunk is not zeroed.
-		 */
-		if (zero == false) {
-			for (i = map_bias+1; i < chunk_npages-1; i++)
-				arena_mapbits_unzeroed_set(chunk, i, unzeroed);
-		} else if (config_debug) {
+	zero = false;
+	malloc_mutex_unlock(&arena->lock);
+	chunk = (arena_chunk_t *)chunk_alloc(chunksize, chunksize, false,
+	    &zero, arena->dss_prec);
+	malloc_mutex_lock(&arena->lock);
+	if (chunk == NULL)
+		return (NULL);
+	if (config_stats)
+		arena->stats.mapped += chunksize;
+
+	chunk->arena = arena;
+
+	/*
+	 * Claim that no pages are in use, since the header is merely overhead.
+	 */
+	chunk->ndirty = 0;
+
+	chunk->nruns_avail = 0;
+	chunk->nruns_adjac = 0;
+
+	/*
+	 * Initialize the map to contain one maximal free untouched run.  Mark
+	 * the pages as zeroed iff chunk_alloc() returned a zeroed chunk.
+	 */
+	unzeroed = zero ? 0 : CHUNK_MAP_UNZEROED;
+	arena_mapbits_unallocated_set(chunk, map_bias, arena_maxclass,
+	    unzeroed);
+	/*
+	 * There is no need to initialize the internal page map entries unless
+	 * the chunk is not zeroed.
+	 */
+	if (zero == false) {
+		VALGRIND_MAKE_MEM_UNDEFINED((void *)arena_mapp_get(chunk,
+		    map_bias+1), (size_t)((uintptr_t) arena_mapp_get(chunk,
+		    chunk_npages-1) - (uintptr_t)arena_mapp_get(chunk,
+		    map_bias+1)));
+		for (i = map_bias+1; i < chunk_npages-1; i++)
+			arena_mapbits_unzeroed_set(chunk, i, unzeroed);
+	} else {
+		VALGRIND_MAKE_MEM_DEFINED((void *)arena_mapp_get(chunk,
+		    map_bias+1), (size_t)((uintptr_t) arena_mapp_get(chunk,
+		    chunk_npages-1) - (uintptr_t)arena_mapp_get(chunk,
+		    map_bias+1)));
+		if (config_debug) {
 			for (i = map_bias+1; i < chunk_npages-1; i++) {
 				assert(arena_mapbits_unzeroed_get(chunk, i) ==
 				    unzeroed);
 			}
 		}
-		arena_mapbits_unallocated_set(chunk, chunk_npages-1,
-		    arena_maxclass, unzeroed);
+	}
+	arena_mapbits_unallocated_set(chunk, chunk_npages-1, arena_maxclass,
+	    unzeroed);
+
+	return (chunk);
+}
+
+static arena_chunk_t *
+arena_chunk_alloc(arena_t *arena)
+{
+	arena_chunk_t *chunk;
+
+	if (arena->spare != NULL)
+		chunk = arena_chunk_init_spare(arena);
+	else {
+		chunk = arena_chunk_init_hard(arena);
+		if (chunk == NULL)
+			return (NULL);
 	}
 
 	/* Insert the run into the runs_avail tree. */
@@ -618,8 +660,7 @@ arena_chunk_dealloc(arena_t *arena, arena_chunk_t *chunk)
 }
 
 static arena_run_t *
-arena_run_alloc_helper(arena_t *arena, size_t size, bool large, size_t binind,
-    bool zero)
+arena_run_alloc_large_helper(arena_t *arena, size_t size, bool zero)
 {
 	arena_run_t *run;
 	arena_chunk_map_t *mapelm, key;
@@ -634,27 +675,80 @@ arena_run_alloc_helper(arena_t *arena, size_t size, bool large, size_t binind,
 
 		run = (arena_run_t *)((uintptr_t)run_chunk + (pageind <<
 		    LG_PAGE));
-		arena_run_split(arena, run, size, large, binind, zero);
+		arena_run_split_large(arena, run, size, zero);
 		return (run);
 	}
 
 	return (NULL);
 }
 
 static arena_run_t *
-arena_run_alloc(arena_t *arena, size_t size, bool large, size_t binind,
-    bool zero)
+arena_run_alloc_large(arena_t *arena, size_t size, bool zero)
+{
+	arena_chunk_t *chunk;
+	arena_run_t *run;
+
+	assert(size <= arena_maxclass);
+	assert((size & PAGE_MASK) == 0);
+
+	/* Search the arena's chunks for the lowest best fit. */
+	run = arena_run_alloc_large_helper(arena, size, zero);
+	if (run != NULL)
+		return (run);
+
+	/*
+	 * No usable runs.  Create a new chunk from which to allocate the run.
+	 */
+	chunk = arena_chunk_alloc(arena);
+	if (chunk != NULL) {
+		run = (arena_run_t *)((uintptr_t)chunk + (map_bias << LG_PAGE));
+		arena_run_split_large(arena, run, size, zero);
+		return (run);
+	}
+
+	/*
+	 * arena_chunk_alloc() failed, but another thread may have made
+	 * sufficient memory available while this one dropped arena->lock in
+	 * arena_chunk_alloc(), so search one more time.
+	 */
+	return (arena_run_alloc_large_helper(arena, size, zero));
+}
+
+static arena_run_t *
+arena_run_alloc_small_helper(arena_t *arena, size_t size, size_t binind)
+{
+	arena_run_t *run;
+	arena_chunk_map_t *mapelm, key;
+
+	key.bits = size | CHUNK_MAP_KEY;
+	mapelm = arena_avail_tree_nsearch(&arena->runs_avail, &key);
+	if (mapelm != NULL) {
+		arena_chunk_t *run_chunk = CHUNK_ADDR2BASE(mapelm);
+		size_t pageind = (((uintptr_t)mapelm -
+		    (uintptr_t)run_chunk->map) / sizeof(arena_chunk_map_t))
+		    + map_bias;
+
+		run = (arena_run_t *)((uintptr_t)run_chunk + (pageind <<
+		    LG_PAGE));
+		arena_run_split_small(arena, run, size, binind);
+		return (run);
+	}
+
+	return (NULL);
+}
+
+static arena_run_t *
+arena_run_alloc_small(arena_t *arena, size_t size, size_t binind)
 {
 	arena_chunk_t *chunk;
 	arena_run_t *run;
 
 	assert(size <= arena_maxclass);
 	assert((size & PAGE_MASK) == 0);
-	assert((large && binind == BININD_INVALID) || (large == false && binind
-	    != BININD_INVALID));
+	assert(binind != BININD_INVALID);
 
 	/* Search the arena's chunks for the lowest best fit. */
-	run = arena_run_alloc_helper(arena, size, large, binind, zero);
+	run = arena_run_alloc_small_helper(arena, size, binind);
 	if (run != NULL)
 		return (run);
 
@@ -664,7 +758,7 @@ arena_run_alloc(arena_t *arena, size_t size, bool large, size_t binind,
 	chunk = arena_chunk_alloc(arena);
 	if (chunk != NULL) {
 		run = (arena_run_t *)((uintptr_t)chunk + (map_bias << LG_PAGE));
-		arena_run_split(arena, run, size, large, binind, zero);
+		arena_run_split_small(arena, run, size, binind);
 		return (run);
 	}
 
@@ -673,7 +767,7 @@ arena_run_alloc(arena_t *arena, size_t size, bool large, size_t binind,
 	 * sufficient memory available while this one dropped arena->lock in
 	 * arena_chunk_alloc(), so search one more time.
 	 */
-	return (arena_run_alloc_helper(arena, size, large, binind, zero));
+	return (arena_run_alloc_small_helper(arena, size, binind));
 }
 
 static inline void
@@ -699,56 +793,50 @@ arena_maybe_purge(arena_t *arena)
 	arena_purge(arena, false);
 }
 
-static inline size_t
-arena_chunk_purge(arena_t *arena, arena_chunk_t *chunk, bool all)
+static arena_chunk_t *
+chunks_dirty_iter_cb(arena_chunk_tree_t *tree, arena_chunk_t *chunk, void *arg)
 {
-	size_t npurged;
-	ql_head(arena_chunk_map_t) mapelms;
-	arena_chunk_map_t *mapelm;
-	size_t pageind, npages;
-	size_t nmadvise;
+       size_t *ndirty = (size_t *)arg;
 
-	ql_new(&mapelms);
+       assert(chunk->ndirty != 0);
+       *ndirty += chunk->ndirty;
+       return (NULL);
+}
+
+static size_t
+arena_compute_npurgatory(arena_t *arena, bool all)
+{
+	size_t npurgatory, npurgeable;
 
 	/*
-	 * If chunk is the spare, temporarily re-allocate it, 1) so that its
-	 * run is reinserted into runs_avail, and 2) so that it cannot be
-	 * completely discarded by another thread while arena->lock is dropped
-	 * by this thread.  Note that the arena_run_dalloc() call will
-	 * implicitly deallocate the chunk, so no explicit action is required
-	 * in this function to deallocate the chunk.
-	 *
-	 * Note that once a chunk contains dirty pages, it cannot again contain
-	 * a single run unless 1) it is a dirty run, or 2) this function purges
-	 * dirty pages and causes the transition to a single clean run.  Thus
-	 * (chunk == arena->spare) is possible, but it is not possible for
-	 * this function to be called on the spare unless it contains a dirty
-	 * run.
+	 * Compute the minimum number of pages that this thread should try to
+	 * purge.
 	 */
-	if (chunk == arena->spare) {
-		assert(arena_mapbits_dirty_get(chunk, map_bias) != 0);
-		assert(arena_mapbits_dirty_get(chunk, chunk_npages-1) != 0);
+	npurgeable = arena->ndirty - arena->npurgatory;
 
-		arena_chunk_alloc(arena);
-	}
+	if (all == false) {
+		size_t threshold = (arena->nactive >> opt_lg_dirty_mult);
 
-	if (config_stats)
-		arena->stats.purged += chunk->ndirty;
+		npurgatory = npurgeable - threshold;
+	} else
+		npurgatory = npurgeable;
 
-	/*
-	 * Operate on all dirty runs if there is no clean/dirty run
-	 * fragmentation.
-	 */
-	if (chunk->nruns_adjac == 0)
-		all = true;
+	return (npurgatory);
+}
+
+static void
+arena_chunk_stash_dirty(arena_t *arena, arena_chunk_t *chunk, bool all,
+    arena_chunk_mapelms_t *mapelms)
+{
+	size_t pageind, npages;
 
 	/*
 	 * Temporarily allocate free dirty runs within chunk.  If all is false,
 	 * only operate on dirty runs that are fragments; otherwise operate on
 	 * all dirty runs.
 	 */
 	for (pageind = map_bias; pageind < chunk_npages; pageind += npages) {
-		mapelm = arena_mapp_get(chunk, pageind);
+		arena_chunk_map_t *mapelm = arena_mapp_get(chunk, pageind);
 		if (arena_mapbits_allocated_get(chunk, pageind) == 0) {
 			size_t run_size =
 			    arena_mapbits_unallocated_size_get(chunk, pageind);
@@ -764,11 +852,11 @@ arena_chunk_purge(arena_t *arena, arena_chunk_t *chunk, bool all)
 				arena_run_t *run = (arena_run_t *)((uintptr_t)
 				    chunk + (uintptr_t)(pageind << LG_PAGE));
 
-				arena_run_split(arena, run, run_size, true,
-				    BININD_INVALID, false);
+				arena_run_split_large(arena, run, run_size,
+				    false);
 				/* Append to list for later processing. */
 				ql_elm_new(mapelm, u.ql_link);
-				ql_tail_insert(&mapelms, mapelm, u.ql_link);
+				ql_tail_insert(mapelms, mapelm, u.ql_link);
 			}
 		} else {
 			/* Skip run. */
@@ -792,12 +880,20 @@ arena_chunk_purge(arena_t *arena, arena_chunk_t *chunk, bool all)
 	assert(pageind == chunk_npages);
 	assert(chunk->ndirty == 0 || all == false);
 	assert(chunk->nruns_adjac == 0);
+}
+
+static size_t
+arena_chunk_purge_stashed(arena_t *arena, arena_chunk_t *chunk,
+    arena_chunk_mapelms_t *mapelms)
+{
+	size_t npurged, pageind, npages, nmadvise;
+	arena_chunk_map_t *mapelm;
 
 	malloc_mutex_unlock(&arena->lock);
 	if (config_stats)
 		nmadvise = 0;
 	npurged = 0;
-	ql_foreach(mapelm, &mapelms, u.ql_link) {
+	ql_foreach(mapelm, mapelms, u.ql_link) {
 		bool unzeroed;
 		size_t flag_unzeroed, i;
 
@@ -831,30 +927,75 @@ arena_chunk_purge(arena_t *arena, arena_chunk_t *chunk, bool all)
 	if (config_stats)
 		arena->stats.nmadvise += nmadvise;
 
+	return (npurged);
+}
+
+static void
+arena_chunk_unstash_purged(arena_t *arena, arena_chunk_t *chunk,
+    arena_chunk_mapelms_t *mapelms)
+{
+	arena_chunk_map_t *mapelm;
+	size_t pageind;
+
 	/* Deallocate runs. */
-	for (mapelm = ql_first(&mapelms); mapelm != NULL;
-	    mapelm = ql_first(&mapelms)) {
+	for (mapelm = ql_first(mapelms); mapelm != NULL;
+	    mapelm = ql_first(mapelms)) {
 		arena_run_t *run;
 
 		pageind = (((uintptr_t)mapelm - (uintptr_t)chunk->map) /
 		    sizeof(arena_chunk_map_t)) + map_bias;
 		run = (arena_run_t *)((uintptr_t)chunk + (uintptr_t)(pageind <<
 		    LG_PAGE));
-		ql_remove(&mapelms, mapelm, u.ql_link);
+		ql_remove(mapelms, mapelm, u.ql_link);
 		arena_run_dalloc(arena, run, false, true);
 	}
-
-	return (npurged);
 }
 
-static arena_chunk_t *
-chunks_dirty_iter_cb(arena_chunk_tree_t *tree, arena_chunk_t *chunk, void *arg)
+static inline size_t
+arena_chunk_purge(arena_t *arena, arena_chunk_t *chunk, bool all)
 {
-       size_t *ndirty = (size_t *)arg;
+	size_t npurged;
+	arena_chunk_mapelms_t mapelms;
 
-       assert(chunk->ndirty != 0);
-       *ndirty += chunk->ndirty;
-       return (NULL);
+	ql_new(&mapelms);
+
+	/*
+	 * If chunk is the spare, temporarily re-allocate it, 1) so that its
+	 * run is reinserted into runs_avail, and 2) so that it cannot be
+	 * completely discarded by another thread while arena->lock is dropped
+	 * by this thread.  Note that the arena_run_dalloc() call will
+	 * implicitly deallocate the chunk, so no explicit action is required
+	 * in this function to deallocate the chunk.
+	 *
+	 * Note that once a chunk contains dirty pages, it cannot again contain
+	 * a single run unless 1) it is a dirty run, or 2) this function purges
+	 * dirty pages and causes the transition to a single clean run.  Thus
+	 * (chunk == arena->spare) is possible, but it is not possible for
+	 * this function to be called on the spare unless it contains a dirty
+	 * run.
+	 */
+	if (chunk == arena->spare) {
+		assert(arena_mapbits_dirty_get(chunk, map_bias) != 0);
+		assert(arena_mapbits_dirty_get(chunk, chunk_npages-1) != 0);
+
+		arena_chunk_alloc(arena);
+	}
+
+	if (config_stats)
+		arena->stats.purged += chunk->ndirty;
+
+	/*
+	 * Operate on all dirty runs if there is no clean/dirty run
+	 * fragmentation.
+	 */
+	if (chunk->nruns_adjac == 0)
+		all = true;
+
+	arena_chunk_stash_dirty(arena, chunk, all, &mapelms);
+	npurged = arena_chunk_purge_stashed(arena, chunk, &mapelms);
+	arena_chunk_unstash_purged(arena, chunk, &mapelms);
+
+	return (npurged);
 }
 
 static void
@@ -877,21 +1018,11 @@ arena_purge(arena_t *arena, bool all)
 		arena->stats.npurge++;
 
 	/*
-	 * Compute the minimum number of pages that this thread should try to
-	 * purge, and add the result to arena->npurgatory.  This will keep
-	 * multiple threads from racing to reduce ndirty below the threshold.
+	 * Add the minimum number of pages this thread should try to purge to
+	 * arena->npurgatory.  This will keep multiple threads from racing to
+	 * reduce ndirty below the threshold.
 	 */
-	{
-		size_t npurgeable = arena->ndirty - arena->npurgatory;
-
-		if (all == false) {
-			size_t threshold = (arena->nactive >>
-			    opt_lg_dirty_mult);
-
-			npurgatory = npurgeable - threshold;
-		} else
-			npurgatory = npurgeable;
-	}
+	npurgatory = arena_compute_npurgatory(arena, all);
 	arena->npurgatory += npurgatory;
 
 	while (npurgatory > 0) {
@@ -958,61 +1089,12 @@ arena_purge_all(arena_t *arena)
 }
 
 static void
-arena_run_dalloc(arena_t *arena, arena_run_t *run, bool dirty, bool cleaned)
+arena_run_coalesce(arena_t *arena, arena_chunk_t *chunk, size_t *p_size,
+    size_t *p_run_ind, size_t *p_run_pages, size_t flag_dirty)
 {
-	arena_chunk_t *chunk;
-	size_t size, run_ind, run_pages, flag_dirty;
-
-	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(run);
-	run_ind = (size_t)(((uintptr_t)run - (uintptr_t)chunk) >> LG_PAGE);
-	assert(run_ind >= map_bias);
-	assert(run_ind < chunk_npages);
-	if (arena_mapbits_large_get(chunk, run_ind) != 0) {
-		size = arena_mapbits_large_size_get(chunk, run_ind);
-		assert(size == PAGE ||
-		    arena_mapbits_large_size_get(chunk,
-		    run_ind+(size>>LG_PAGE)-1) == 0);
-	} else {
-		size_t binind = arena_bin_index(arena, run->bin);
-		arena_bin_info_t *bin_info = &arena_bin_info[binind];
-		size = bin_info->run_size;
-	}
-	run_pages = (size >> LG_PAGE);
-	if (config_stats) {
-		/*
-		 * Update stats_cactive if nactive is crossing a chunk
-		 * multiple.
-		 */
-		size_t cactive_diff = CHUNK_CEILING(arena->nactive << LG_PAGE) -
-		    CHUNK_CEILING((arena->nactive - run_pages) << LG_PAGE);
-		if (cactive_diff != 0)
-			stats_cactive_sub(cactive_diff);
-	}
-	arena->nactive -= run_pages;
-
-	/*
-	 * The run is dirty if the caller claims to have dirtied it, as well as
-	 * if it was already dirty before being allocated and the caller
-	 * doesn't claim to have cleaned it.
-	 */
-	assert(arena_mapbits_dirty_get(chunk, run_ind) ==
-	    arena_mapbits_dirty_get(chunk, run_ind+run_pages-1));
-	if (cleaned == false && arena_mapbits_dirty_get(chunk, run_ind) != 0)
-		dirty = true;
-	flag_dirty = dirty ? CHUNK_MAP_DIRTY : 0;
-
-	/* Mark pages as unallocated in the chunk map. */
-	if (dirty) {
-		arena_mapbits_unallocated_set(chunk, run_ind, size,
-		    CHUNK_MAP_DIRTY);
-		arena_mapbits_unallocated_set(chunk, run_ind+run_pages-1, size,
-		    CHUNK_MAP_DIRTY);
-	} else {
-		arena_mapbits_unallocated_set(chunk, run_ind, size,
-		    arena_mapbits_unzeroed_get(chunk, run_ind));
-		arena_mapbits_unallocated_set(chunk, run_ind+run_pages-1, size,
-		    arena_mapbits_unzeroed_get(chunk, run_ind+run_pages-1));
-	}
+	size_t size = *p_size;
+	size_t run_ind = *p_run_ind;
+	size_t run_pages = *p_run_pages;
 
 	/* Try to coalesce forward. */
 	if (run_ind + run_pages < chunk_npages &&
@@ -1042,8 +1124,9 @@ arena_run_dalloc(arena_t *arena, arena_run_t *run, bool dirty, bool cleaned)
 	}
 
 	/* Try to coalesce backward. */
-	if (run_ind > map_bias && arena_mapbits_allocated_get(chunk, run_ind-1)
-	    == 0 && arena_mapbits_dirty_get(chunk, run_ind-1) == flag_dirty) {
+	if (run_ind > map_bias && arena_mapbits_allocated_get(chunk,
+	    run_ind-1) == 0 && arena_mapbits_dirty_get(chunk, run_ind-1) ==
+	    flag_dirty) {
 		size_t prun_size = arena_mapbits_unallocated_size_get(chunk,
 		    run_ind-1);
 		size_t prun_pages = prun_size >> LG_PAGE;
@@ -1068,6 +1151,62 @@ arena_run_dalloc(arena_t *arena, arena_run_t *run, bool dirty, bool cleaned)
 		    size);
 	}
 
+	*p_size = size;
+	*p_run_ind = run_ind;
+	*p_run_pages = run_pages;
+}
+
+static void
+arena_run_dalloc(arena_t *arena, arena_run_t *run, bool dirty, bool cleaned)
+{
+	arena_chunk_t *chunk;
+	size_t size, run_ind, run_pages, flag_dirty;
+
+	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(run);
+	run_ind = (size_t)(((uintptr_t)run - (uintptr_t)chunk) >> LG_PAGE);
+	assert(run_ind >= map_bias);
+	assert(run_ind < chunk_npages);
+	if (arena_mapbits_large_get(chunk, run_ind) != 0) {
+		size = arena_mapbits_large_size_get(chunk, run_ind);
+		assert(size == PAGE ||
+		    arena_mapbits_large_size_get(chunk,
+		    run_ind+(size>>LG_PAGE)-1) == 0);
+	} else {
+		size_t binind = arena_bin_index(arena, run->bin);
+		arena_bin_info_t *bin_info = &arena_bin_info[binind];
+		size = bin_info->run_size;
+	}
+	run_pages = (size >> LG_PAGE);
+	arena_cactive_update(arena, 0, run_pages);
+	arena->nactive -= run_pages;
+
+	/*
+	 * The run is dirty if the caller claims to have dirtied it, as well as
+	 * if it was already dirty before being allocated and the caller
+	 * doesn't claim to have cleaned it.
+	 */
+	assert(arena_mapbits_dirty_get(chunk, run_ind) ==
+	    arena_mapbits_dirty_get(chunk, run_ind+run_pages-1));
+	if (cleaned == false && arena_mapbits_dirty_get(chunk, run_ind) != 0)
+		dirty = true;
+	flag_dirty = dirty ? CHUNK_MAP_DIRTY : 0;
+
+	/* Mark pages as unallocated in the chunk map. */
+	if (dirty) {
+		arena_mapbits_unallocated_set(chunk, run_ind, size,
+		    CHUNK_MAP_DIRTY);
+		arena_mapbits_unallocated_set(chunk, run_ind+run_pages-1, size,
+		    CHUNK_MAP_DIRTY);
+	} else {
+		arena_mapbits_unallocated_set(chunk, run_ind, size,
+		    arena_mapbits_unzeroed_get(chunk, run_ind));
+		arena_mapbits_unallocated_set(chunk, run_ind+run_pages-1, size,
+		    arena_mapbits_unzeroed_get(chunk, run_ind+run_pages-1));
+	}
+
+	arena_run_coalesce(arena, chunk, &size, &run_ind, &run_pages,
+	    flag_dirty);
+
 	/* Insert into runs_avail, now that coalescing is complete. */
 	assert(arena_mapbits_unallocated_size_get(chunk, run_ind) ==
 	    arena_mapbits_unallocated_size_get(chunk, run_ind+run_pages-1));
@@ -1235,14 +1374,12 @@ arena_bin_nonfull_run_get(arena_t *arena, arena_bin_t *bin)
 	malloc_mutex_unlock(&bin->lock);
 	/******************************/
 	malloc_mutex_lock(&arena->lock);
-	run = arena_run_alloc(arena, bin_info->run_size, false, binind, false);
+	run = arena_run_alloc_small(arena, bin_info->run_size, binind);
 	if (run != NULL) {
 		bitmap_t *bitmap = (bitmap_t *)((uintptr_t)run +
 		    (uintptr_t)bin_info->bitmap_offset);
 
 		/* Initialize run internals. */
-		VALGRIND_MAKE_MEM_UNDEFINED(run, bin_info->reg0_offset -
-		    bin_info->redzone_size);
 		run->bin = bin;
 		run->nextind = 0;
 		run->nfree = bin_info->nregs;
@@ -1260,7 +1397,7 @@ arena_bin_nonfull_run_get(arena_t *arena, arena_bin_t *bin)
 	}
 
 	/*
-	 * arena_run_alloc() failed, but another thread may have made
+	 * arena_run_alloc_small() failed, but another thread may have made
 	 * sufficient memory available while this one dropped bin->lock above,
 	 * so search one more time.
 	 */
@@ -1295,12 +1432,12 @@ arena_bin_malloc_hard(arena_t *arena, arena_bin_t *bin)
 			arena_chunk_t *chunk;
 
 			/*
-			 * arena_run_alloc() may have allocated run, or it may
-			 * have pulled run from the bin's run tree.  Therefore
-			 * it is unsafe to make any assumptions about how run
-			 * has previously been used, and arena_bin_lower_run()
-			 * must be called, as if a region were just deallocated
-			 * from the run.
+			 * arena_run_alloc_small() may have allocated run, or
+			 * it may have pulled run from the bin's run tree.
+			 * Therefore it is unsafe to make any assumptions about
+			 * how run has previously been used, and
+			 * arena_bin_lower_run() must be called, as if a region
+			 * were just deallocated from the run.
 			 */
 			chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(run);
 			if (run->nfree == bin_info->nregs)
@@ -1322,21 +1459,6 @@ arena_bin_malloc_hard(arena_t *arena, arena_bin_t *bin)
 }
 
 void
-arena_prof_accum(arena_t *arena, uint64_t accumbytes)
-{
-
-	cassert(config_prof);
-
-	if (config_prof && prof_interval != 0) {
-		arena->prof_accumbytes += accumbytes;
-		if (arena->prof_accumbytes >= prof_interval) {
-			prof_idump();
-			arena->prof_accumbytes -= prof_interval;
-		}
-	}
-}
-
-void
 arena_tcache_fill_small(arena_t *arena, tcache_bin_t *tbin, size_t binind,
     uint64_t prof_accumbytes)
 {
@@ -1347,11 +1469,8 @@ arena_tcache_fill_small(arena_t *arena, tcache_bin_t *tbin, size_t binind,
 
 	assert(tbin->ncached == 0);
 
-	if (config_prof) {
-		malloc_mutex_lock(&arena->lock);
-		arena_prof_accum(arena, prof_accumbytes);
-		malloc_mutex_unlock(&arena->lock);
-	}
+	if (config_prof && arena_prof_accum(arena, prof_accumbytes))
+		prof_idump();
 	bin = &arena->bins[binind];
 	malloc_mutex_lock(&bin->lock);
 	for (i = 0, nfill = (tcache_bin_info[binind].ncached_max >>
@@ -1396,38 +1515,90 @@ arena_alloc_junk_small(void *ptr, arena_bin_info_t *bin_info, bool zero)
 	}
 }
 
-void
-arena_dalloc_junk_small(void *ptr, arena_bin_info_t *bin_info)
+#ifdef JEMALLOC_JET
+#undef arena_redzone_corruption
+#define	arena_redzone_corruption JEMALLOC_N(arena_redzone_corruption_impl)
+#endif
+static void
+arena_redzone_corruption(void *ptr, size_t usize, bool after,
+    size_t offset, uint8_t byte)
+{
+
+	malloc_printf("<jemalloc>: Corrupt redzone %zu byte%s %s %p "
+	    "(size %zu), byte=%#x\n", offset, (offset == 1) ? "" : "s",
+	    after ? "after" : "before", ptr, usize, byte);
+}
+#ifdef JEMALLOC_JET
+#undef arena_redzone_corruption
+#define	arena_redzone_corruption JEMALLOC_N(arena_redzone_corruption)
+arena_redzone_corruption_t *arena_redzone_corruption =
+    JEMALLOC_N(arena_redzone_corruption_impl);
+#endif
+
+static void
+arena_redzones_validate(void *ptr, arena_bin_info_t *bin_info, bool reset)
 {
 	size_t size = bin_info->reg_size;
 	size_t redzone_size = bin_info->redzone_size;
 	size_t i;
 	bool error = false;
 
 	for (i = 1; i <= redzone_size; i++) {
-		unsigned byte;
-		if ((byte = *(uint8_t *)((uintptr_t)ptr - i)) != 0xa5) {
+		uint8_t *byte = (uint8_t *)((uintptr_t)ptr - i);
+		if (*byte != 0xa5) {
 			error = true;
-			malloc_printf("<jemalloc>: Corrupt redzone "
-			    "%zu byte%s before %p (size %zu), byte=%#x\n", i,
-			    (i == 1) ? "" : "s", ptr, size, byte);
+			arena_redzone_corruption(ptr, size, false, i, *byte);
+			if (reset)
+				*byte = 0xa5;
 		}
 	}
 	for (i = 0; i < redzone_size; i++) {
-		unsigned byte;
-		if ((byte = *(uint8_t *)((uintptr_t)ptr + size + i)) != 0xa5) {
+		uint8_t *byte = (uint8_t *)((uintptr_t)ptr + size + i);
+		if (*byte != 0xa5) {
 			error = true;
-			malloc_printf("<jemalloc>: Corrupt redzone "
-			    "%zu byte%s after end of %p (size %zu), byte=%#x\n",
-			    i, (i == 1) ? "" : "s", ptr, size, byte);
+			arena_redzone_corruption(ptr, size, true, i, *byte);
+			if (reset)
+				*byte = 0xa5;
 		}
 	}
 	if (opt_abort && error)
 		abort();
+}
 
+#ifdef JEMALLOC_JET
+#undef arena_dalloc_junk_small
+#define	arena_dalloc_junk_small JEMALLOC_N(arena_dalloc_junk_small_impl)
+#endif
+void
+arena_dalloc_junk_small(void *ptr, arena_bin_info_t *bin_info)
+{
+	size_t redzone_size = bin_info->redzone_size;
+
+	arena_redzones_validate(ptr, bin_info, false);
 	memset((void *)((uintptr_t)ptr - redzone_size), 0x5a,
 	    bin_info->reg_interval);
 }
+#ifdef JEMALLOC_JET
+#undef arena_dalloc_junk_small
+#define	arena_dalloc_junk_small JEMALLOC_N(arena_dalloc_junk_small)
+arena_dalloc_junk_small_t *arena_dalloc_junk_small =
+    JEMALLOC_N(arena_dalloc_junk_small_impl);
+#endif
+
+void
+arena_quarantine_junk_small(void *ptr, size_t usize)
+{
+	size_t binind;
+	arena_bin_info_t *bin_info;
+	cassert(config_fill);
+	assert(opt_junk);
+	assert(opt_quarantine);
+	assert(usize <= SMALL_MAXCLASS);
+
+	binind = SMALL_SIZE2BIN(usize);
+	bin_info = &arena_bin_info[binind];
+	arena_redzones_validate(ptr, bin_info, true);
+}
 
 void *
 arena_malloc_small(arena_t *arena, size_t size, bool zero)
@@ -1459,11 +1630,8 @@ arena_malloc_small(arena_t *arena, size_t size, bool zero)
 		bin->stats.nrequests++;
 	}
 	malloc_mutex_unlock(&bin->lock);
-	if (config_prof && isthreaded == false) {
-		malloc_mutex_lock(&arena->lock);
-		arena_prof_accum(arena, size);
-		malloc_mutex_unlock(&arena->lock);
-	}
+	if (config_prof && isthreaded == false && arena_prof_accum(arena, size))
+		prof_idump();
 
 	if (zero == false) {
 		if (config_fill) {
@@ -1473,6 +1641,7 @@ arena_malloc_small(arena_t *arena, size_t size, bool zero)
 			} else if (opt_zero)
 				memset(ret, 0, size);
 		}
+		VALGRIND_MAKE_MEM_UNDEFINED(ret, size);
 	} else {
 		if (config_fill && opt_junk) {
 			arena_alloc_junk_small(ret, &arena_bin_info[binind],
@@ -1489,11 +1658,12 @@ void *
 arena_malloc_large(arena_t *arena, size_t size, bool zero)
 {
 	void *ret;
+	UNUSED bool idump;
 
 	/* Large allocation. */
 	size = PAGE_CEILING(size);
 	malloc_mutex_lock(&arena->lock);
-	ret = (void *)arena_run_alloc(arena, size, true, BININD_INVALID, zero);
+	ret = (void *)arena_run_alloc_large(arena, size, zero);
 	if (ret == NULL) {
 		malloc_mutex_unlock(&arena->lock);
 		return (NULL);
@@ -1507,8 +1677,10 @@ arena_malloc_large(arena_t *arena, size_t size, bool zero)
 		arena->stats.lstats[(size >> LG_PAGE) - 1].curruns++;
 	}
 	if (config_prof)
-		arena_prof_accum(arena, size);
+		idump = arena_prof_accum_locked(arena, size);
 	malloc_mutex_unlock(&arena->lock);
+	if (config_prof && idump)
+		prof_idump();
 
 	if (zero == false) {
 		if (config_fill) {
@@ -1537,7 +1709,7 @@ arena_palloc(arena_t *arena, size_t size, size_t alignment, bool zero)
 	alloc_size = size + alignment - PAGE;
 
 	malloc_mutex_lock(&arena->lock);
-	run = arena_run_alloc(arena, alloc_size, true, BININD_INVALID, zero);
+	run = arena_run_alloc_large(arena, alloc_size, false);
 	if (run == NULL) {
 		malloc_mutex_unlock(&arena->lock);
 		return (NULL);
@@ -1557,6 +1729,7 @@ arena_palloc(arena_t *arena, size_t size, size_t alignment, bool zero)
 		arena_run_trim_tail(arena, chunk, ret, size + trailsize, size,
 		    false);
 	}
+	arena_run_init_large(arena, (arena_run_t *)ret, size, zero);
 
 	if (config_stats) {
 		arena->stats.nmalloc_large++;
@@ -1760,21 +1933,38 @@ arena_dalloc_small(arena_t *arena, arena_chunk_t *chunk, void *ptr,
 	arena_dalloc_bin(arena, chunk, ptr, pageind, mapelm);
 }
 
+#ifdef JEMALLOC_JET
+#undef arena_dalloc_junk_large
+#define	arena_dalloc_junk_large JEMALLOC_N(arena_dalloc_junk_large_impl)
+#endif
+static void
+arena_dalloc_junk_large(void *ptr, size_t usize)
+{
+
+	if (config_fill && opt_junk)
+		memset(ptr, 0x5a, usize);
+}
+#ifdef JEMALLOC_JET
+#undef arena_dalloc_junk_large
+#define	arena_dalloc_junk_large JEMALLOC_N(arena_dalloc_junk_large)
+arena_dalloc_junk_large_t *arena_dalloc_junk_large =
+    JEMALLOC_N(arena_dalloc_junk_large_impl);
+#endif
+
 void
 arena_dalloc_large_locked(arena_t *arena, arena_chunk_t *chunk, void *ptr)
 {
 
 	if (config_fill || config_stats) {
 		size_t pageind = ((uintptr_t)ptr - (uintptr_t)chunk) >> LG_PAGE;
-		size_t size = arena_mapbits_large_size_get(chunk, pageind);
+		size_t usize = arena_mapbits_large_size_get(chunk, pageind);
 
-		if (config_fill && config_stats && opt_junk)
-			memset(ptr, 0x5a, size);
+		arena_dalloc_junk_large(ptr, usize);
 		if (config_stats) {
 			arena->stats.ndalloc_large++;
-			arena->stats.allocated_large -= size;
-			arena->stats.lstats[(size >> LG_PAGE) - 1].ndalloc++;
-			arena->stats.lstats[(size >> LG_PAGE) - 1].curruns--;
+			arena->stats.allocated_large -= usize;
+			arena->stats.lstats[(usize >> LG_PAGE) - 1].ndalloc++;
+			arena->stats.lstats[(usize >> LG_PAGE) - 1].curruns--;
 		}
 	}
 
@@ -1845,9 +2035,8 @@ arena_ralloc_large_grow(arena_t *arena, arena_chunk_t *chunk, void *ptr,
 		size_t flag_dirty;
 		size_t splitsize = (oldsize + followsize <= size + extra)
 		    ? followsize : size + extra - oldsize;
-		arena_run_split(arena, (arena_run_t *)((uintptr_t)chunk +
-		    ((pageind+npages) << LG_PAGE)), splitsize, true,
-		    BININD_INVALID, zero);
+		arena_run_split_large(arena, (arena_run_t *)((uintptr_t)chunk +
+		    ((pageind+npages) << LG_PAGE)), splitsize, zero);
 
 		size = oldsize + splitsize;
 		npages = size >> LG_PAGE;
@@ -1886,6 +2075,26 @@ arena_ralloc_large_grow(arena_t *arena, arena_chunk_t *chunk, void *ptr,
 	return (true);
 }
 
+#ifdef JEMALLOC_JET
+#undef arena_ralloc_junk_large
+#define	arena_ralloc_junk_large JEMALLOC_N(arena_ralloc_junk_large_impl)
+#endif
+static void
+arena_ralloc_junk_large(void *ptr, size_t old_usize, size_t usize)
+{
+
+	if (config_fill && opt_junk) {
+		memset((void *)((uintptr_t)ptr + usize), 0x5a,
+		    old_usize - usize);
+	}
+}
+#ifdef JEMALLOC_JET
+#undef arena_ralloc_junk_large
+#define	arena_ralloc_junk_large JEMALLOC_N(arena_ralloc_junk_large)
+arena_ralloc_junk_large_t *arena_ralloc_junk_large =
+    JEMALLOC_N(arena_ralloc_junk_large_impl);
+#endif
+
 /*
  * Try to resize a large allocation, in order to avoid copying.  This will
  * always fail if growing an object, and the following run is already in use.
@@ -1899,10 +2108,6 @@ arena_ralloc_large(void *ptr, size_t oldsize, size_t size, size_t extra,
 	psize = PAGE_CEILING(size + extra);
 	if (psize == oldsize) {
 		/* Same size class. */
-		if (config_fill && opt_junk && size < oldsize) {
-			memset((void *)((uintptr_t)ptr + size), 0x5a, oldsize -
-			    size);
-		}
 		return (false);
 	} else {
 		arena_chunk_t *chunk;
@@ -1913,28 +2118,31 @@ arena_ralloc_large(void *ptr, size_t oldsize, size_t size, size_t extra,
 
 		if (psize < oldsize) {
 			/* Fill before shrinking in order avoid a race. */
-			if (config_fill && opt_junk) {
-				memset((void *)((uintptr_t)ptr + size), 0x5a,
-				    oldsize - size);
-			}
+			arena_ralloc_junk_large(ptr, oldsize, psize);
 			arena_ralloc_large_shrink(arena, chunk, ptr, oldsize,
 			    psize);
 			return (false);
 		} else {
 			bool ret = arena_ralloc_large_grow(arena, chunk, ptr,
 			    oldsize, PAGE_CEILING(size),
 			    psize - PAGE_CEILING(size), zero);
-			if (config_fill && ret == false && zero == false &&
-			    opt_zero) {
-				memset((void *)((uintptr_t)ptr + oldsize), 0,
-				    size - oldsize);
+			if (config_fill && ret == false && zero == false) {
+				if (opt_junk) {
+					memset((void *)((uintptr_t)ptr +
+					    oldsize), 0xa5, isalloc(ptr,
+					    config_prof) - oldsize);
+				} else if (opt_zero) {
+					memset((void *)((uintptr_t)ptr +
+					    oldsize), 0, isalloc(ptr,
+					    config_prof) - oldsize);
+				}
 			}
 			return (ret);
 		}
 	}
 }
 
-void *
+bool
 arena_ralloc_no_move(void *ptr, size_t oldsize, size_t size, size_t extra,
     bool zero)
 {
@@ -1949,25 +2157,20 @@ arena_ralloc_no_move(void *ptr, size_t oldsize, size_t size, size_t extra,
 			if ((size + extra <= SMALL_MAXCLASS &&
 			    SMALL_SIZE2BIN(size + extra) ==
 			    SMALL_SIZE2BIN(oldsize)) || (size <= oldsize &&
-			    size + extra >= oldsize)) {
-				if (config_fill && opt_junk && size < oldsize) {
-					memset((void *)((uintptr_t)ptr + size),
-					    0x5a, oldsize - size);
-				}
-				return (ptr);
-			}
+			    size + extra >= oldsize))
+				return (false);
 		} else {
 			assert(size <= arena_maxclass);
 			if (size + extra > SMALL_MAXCLASS) {
 				if (arena_ralloc_large(ptr, oldsize, size,
 				    extra, zero) == false)
-					return (ptr);
+					return (false);
 			}
 		}
 	}
 
 	/* Reallocation would require a move. */
-	return (NULL);
+	return (true);
 }
 
 void *
@@ -1979,9 +2182,8 @@ arena_ralloc(arena_t *arena, void *ptr, size_t oldsize, size_t size,
 	size_t copysize;
 
 	/* Try to avoid moving the allocation. */
-	ret = arena_ralloc_no_move(ptr, oldsize, size, extra, zero);
-	if (ret != NULL)
-		return (ret);
+	if (arena_ralloc_no_move(ptr, oldsize, size, extra, zero) == false)
+		return (ptr);
 
 	/*
 	 * size and oldsize are different enough that we need to move the
@@ -1992,7 +2194,7 @@ arena_ralloc(arena_t *arena, void *ptr, size_t oldsize, size_t size,
 		size_t usize = sa2u(size + extra, alignment);
 		if (usize == 0)
 			return (NULL);
-		ret = ipallocx(usize, alignment, zero, try_tcache_alloc, arena);
+		ret = ipalloct(usize, alignment, zero, try_tcache_alloc, arena);
 	} else
 		ret = arena_malloc(arena, size + extra, zero, try_tcache_alloc);
 
@@ -2004,7 +2206,7 @@ arena_ralloc(arena_t *arena, void *ptr, size_t oldsize, size_t size,
 			size_t usize = sa2u(size, alignment);
 			if (usize == 0)
 				return (NULL);
-			ret = ipallocx(usize, alignment, zero, try_tcache_alloc,
+			ret = ipalloct(usize, alignment, zero, try_tcache_alloc,
 			    arena);
 		} else
 			ret = arena_malloc(arena, size, zero, try_tcache_alloc);
@@ -2022,7 +2224,7 @@ arena_ralloc(arena_t *arena, void *ptr, size_t oldsize, size_t size,
 	copysize = (size < oldsize) ? size : oldsize;
 	VALGRIND_MAKE_MEM_UNDEFINED(ret, copysize);
 	memcpy(ret, ptr, copysize);
-	iqallocx(ptr, try_tcache_dalloc);
+	iqalloct(ptr, try_tcache_dalloc);
 	return (ret);
 }
 
@@ -2277,7 +2479,6 @@ bin_info_run_size_calc(arena_bin_info_t *bin_info, size_t min_run_size)
 			    bin_info->reg_interval) - pad_size;
 		} while (try_hdr_size > try_redzone0_offset);
 	} while (try_run_size <= arena_maxclass
-	    && try_run_size <= arena_maxclass
 	    && RUN_MAX_OVRHD * (bin_info->reg_interval << 3) >
 	    RUN_MAX_OVRHD_RELAX
 	    && (try_redzone0_offset << RUN_BFP) > RUN_MAX_OVRHD * try_run_size