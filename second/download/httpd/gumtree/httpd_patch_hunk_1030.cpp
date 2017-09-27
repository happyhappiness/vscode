     t->index_initialized |= s->index_initialized;
 }
 
 APR_DECLARE(void) apr_table_overlap(apr_table_t *a, const apr_table_t *b,
 				    unsigned flags)
 {
-    const int m = a->a.nelts;
-    const int n = b->a.nelts;
-    apr_pool_t *p = b->a.pool;
-
-    if (m + n == 0) {
+    if (a->a.nelts + b->a.nelts == 0) {
         return;
     }
 
-    /* copy (extend) a using b's pool */
-    if (a->a.pool != p) {
-        make_array_core(&a->a, p, m+n, sizeof(apr_table_entry_t), 0);
+#if APR_POOL_DEBUG
+    /* Since the keys and values are not copied, it's required that
+     * b->a.pool has a lifetime at least as long as a->a.pool. */
+    if (!apr_pool_is_ancestor(b->a.pool, a->a.pool)) {
+        fprintf(stderr, "apr_table_overlap: b's pool is not an ancestor of a's\n");
+        abort();
     }
+#endif
 
     apr_table_cat(a, b);
 
     apr_table_compress(a, flags);
 }
