@@ -16,14 +16,14 @@ malloc_mutex_t	huge_mtx;
 static extent_tree_t	huge;
 
 void *
-huge_malloc(size_t size, bool zero)
+huge_malloc(size_t size, bool zero, dss_prec_t dss_prec)
 {
 
-	return (huge_palloc(size, chunksize, zero));
+	return (huge_palloc(size, chunksize, zero, dss_prec));
 }
 
 void *
-huge_palloc(size_t size, size_t alignment, bool zero)
+huge_palloc(size_t size, size_t alignment, bool zero, dss_prec_t dss_prec)
 {
 	void *ret;
 	size_t csize;
@@ -48,8 +48,7 @@ huge_palloc(size_t size, size_t alignment, bool zero)
 	 * it is possible to make correct junk/zero fill decisions below.
 	 */
 	is_zeroed = zero;
-	ret = chunk_alloc(csize, alignment, false, &is_zeroed,
-	    chunk_dss_prec_get());
+	ret = chunk_alloc(csize, alignment, false, &is_zeroed, dss_prec);
 	if (ret == NULL) {
 		base_node_dealloc(node);
 		return (NULL);
@@ -78,7 +77,7 @@ huge_palloc(size_t size, size_t alignment, bool zero)
 	return (ret);
 }
 
-void *
+bool
 huge_ralloc_no_move(void *ptr, size_t oldsize, size_t size, size_t extra)
 {
 
@@ -89,47 +88,42 @@ huge_ralloc_no_move(void *ptr, size_t oldsize, size_t size, size_t extra)
 	    && CHUNK_CEILING(oldsize) >= CHUNK_CEILING(size)
 	    && CHUNK_CEILING(oldsize) <= CHUNK_CEILING(size+extra)) {
 		assert(CHUNK_CEILING(oldsize) == oldsize);
-		if (config_fill && opt_junk && size < oldsize) {
-			memset((void *)((uintptr_t)ptr + size), 0x5a,
-			    oldsize - size);
-		}
-		return (ptr);
+		return (false);
 	}
 
 	/* Reallocation would require a move. */
-	return (NULL);
+	return (true);
 }
 
 void *
 huge_ralloc(void *ptr, size_t oldsize, size_t size, size_t extra,
-    size_t alignment, bool zero, bool try_tcache_dalloc)
+    size_t alignment, bool zero, bool try_tcache_dalloc, dss_prec_t dss_prec)
 {
 	void *ret;
 	size_t copysize;
 
 	/* Try to avoid moving the allocation. */
-	ret = huge_ralloc_no_move(ptr, oldsize, size, extra);
-	if (ret != NULL)
-		return (ret);
+	if (huge_ralloc_no_move(ptr, oldsize, size, extra) == false)
+		return (ptr);
 
 	/*
 	 * size and oldsize are different enough that we need to use a
 	 * different size class.  In that case, fall back to allocating new
 	 * space and copying.
 	 */
 	if (alignment > chunksize)
-		ret = huge_palloc(size + extra, alignment, zero);
+		ret = huge_palloc(size + extra, alignment, zero, dss_prec);
 	else
-		ret = huge_malloc(size + extra, zero);
+		ret = huge_malloc(size + extra, zero, dss_prec);
 
 	if (ret == NULL) {
 		if (extra == 0)
 			return (NULL);
 		/* Try again, this time without extra. */
 		if (alignment > chunksize)
-			ret = huge_palloc(size, alignment, zero);
+			ret = huge_palloc(size, alignment, zero, dss_prec);
 		else
-			ret = huge_malloc(size, zero);
+			ret = huge_malloc(size, zero, dss_prec);
 
 		if (ret == NULL)
 			return (NULL);
@@ -169,23 +163,56 @@ huge_ralloc(void *ptr, size_t oldsize, size_t size, size_t extra,
 			 */
 			char buf[BUFERROR_BUF];
 
-			buferror(buf, sizeof(buf));
+			buferror(get_errno(), buf, sizeof(buf));
 			malloc_printf("<jemalloc>: Error in mremap(): %s\n",
 			    buf);
 			if (opt_abort)
 				abort();
 			memcpy(ret, ptr, copysize);
 			chunk_dealloc_mmap(ptr, oldsize);
+		} else if (config_fill && zero == false && opt_junk && oldsize
+		    < newsize) {
+			/*
+			 * mremap(2) clobbers the original mapping, so
+			 * junk/zero filling is not preserved.  There is no
+			 * need to zero fill here, since any trailing
+			 * uninititialized memory is demand-zeroed by the
+			 * kernel, but junk filling must be redone.
+			 */
+			memset(ret + oldsize, 0xa5, newsize - oldsize);
 		}
 	} else
 #endif
 	{
 		memcpy(ret, ptr, copysize);
-		iqallocx(ptr, try_tcache_dalloc);
+		iqalloct(ptr, try_tcache_dalloc);
 	}
 	return (ret);
 }
 
+#ifdef JEMALLOC_JET
+#undef huge_dalloc_junk
+#define	huge_dalloc_junk JEMALLOC_N(huge_dalloc_junk_impl)
+#endif
+static void
+huge_dalloc_junk(void *ptr, size_t usize)
+{
+
+	if (config_fill && config_dss && opt_junk) {
+		/*
+		 * Only bother junk filling if the chunk isn't about to be
+		 * unmapped.
+		 */
+		if (config_munmap == false || (config_dss && chunk_in_dss(ptr)))
+			memset(ptr, 0x5a, usize);
+	}
+}
+#ifdef JEMALLOC_JET
+#undef huge_dalloc_junk
+#define	huge_dalloc_junk JEMALLOC_N(huge_dalloc_junk)
+huge_dalloc_junk_t *huge_dalloc_junk = JEMALLOC_N(huge_dalloc_junk_impl);
+#endif
+
 void
 huge_dalloc(void *ptr, bool unmap)
 {
@@ -208,8 +235,8 @@ huge_dalloc(void *ptr, bool unmap)
 
 	malloc_mutex_unlock(&huge_mtx);
 
-	if (unmap && config_fill && config_dss && opt_junk)
-		memset(node->addr, 0x5a, node->size);
+	if (unmap)
+		huge_dalloc_junk(node->addr, node->size);
 
 	chunk_dealloc(node->addr, node->size, unmap);
 
@@ -236,6 +263,13 @@ huge_salloc(const void *ptr)
 	return (ret);
 }
 
+dss_prec_t
+huge_dss_prec_get(arena_t *arena)
+{
+
+	return (arena_dss_prec_get(choose_arena(arena)));
+}
+
 prof_ctx_t *
 huge_prof_ctx_get(const void *ptr)
 {