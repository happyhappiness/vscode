         ap_rputs("CacheType: DBM\n", r);
         ap_rputs("CacheMaximumSize: unlimited\n", r);
         ap_rprintf(r, "CacheCurrentEntries: %d\n", elts);
         ap_rprintf(r, "CacheCurrentSize: %ld\n", size);
         ap_rprintf(r, "CacheAvgEntrySize: %d\n", avg);
     }
-    return;
 }
 
 static apr_status_t socache_dbm_iterate(ap_socache_instance_t *ctx,
                                         server_rec *s, void *userctx,
                                         ap_socache_iterator_t *iterator,
                                         apr_pool_t *pool)
