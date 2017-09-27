 }
 
 APR_DECLARE(apr_table_t *) apr_table_copy(apr_pool_t *p, const apr_table_t *t)
 {
     apr_table_t *new = apr_palloc(p, sizeof(apr_table_t));
 
-#ifdef POOL_DEBUG
+#if APR_POOL_DEBUG
     /* we don't copy keys and values, so it's necessary that t->a.pool
      * have a life span at least as long as p
      */
     if (!apr_pool_is_ancestor(t->a.pool, p)) {
-	fprintf(stderr, "copy_table: t's pool is not an ancestor of p\n");
+	fprintf(stderr, "apr_table_copy: t's pool is not an ancestor of p\n");
 	abort();
     }
 #endif
     make_array_core(&new->a, p, t->a.nalloc, sizeof(apr_table_entry_t), 0);
     memcpy(new->a.elts, t->a.elts, t->a.nelts * sizeof(apr_table_entry_t));
     new->a.nelts = t->a.nelts;
