 {
     apr_table_entry_t *next_elt;
     apr_table_entry_t *end_elt;
     apr_uint32_t checksum;
     int hash;
 
-#ifdef POOL_DEBUG
+#if APR_POOL_DEBUG
     {
 	if (!apr_pool_is_ancestor(apr_pool_find(key), t->a.pool)) {
-	    fprintf(stderr, "table_set: key not in ancestor pool of t\n");
+	    fprintf(stderr, "apr_table_mergen: key not in ancestor pool of t\n");
 	    abort();
 	}
 	if (!apr_pool_is_ancestor(apr_pool_find(val), t->a.pool)) {
-	    fprintf(stderr, "table_set: val not in ancestor pool of t\n");
+	    fprintf(stderr, "apr_table_mergen: key not in ancestor pool of t\n");
 	    abort();
 	}
     }
 #endif
 
     COMPUTE_KEY_CHECKSUM(key, checksum);
