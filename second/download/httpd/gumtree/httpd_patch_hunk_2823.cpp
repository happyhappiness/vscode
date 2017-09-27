             cache->marktime = apr_time_now();
         }
         util_ald_cache_purge(cache);
         node = (util_cache_node_t *)util_ald_alloc(cache,
                                                    sizeof(util_cache_node_t));
         if (node == NULL) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01325)
                          "Could not allocate memory for LDAP cache entry");
             return NULL;
         }
     }
 
     /* Take a copy of the payload before proceeeding. */
     tmp_payload = (*cache->copy)(cache, payload);
     if (tmp_payload == NULL) {
         /*
          * XXX: The cache management should be rewritten to work
          * properly when LDAPSharedCacheSize is too small.
          */
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(01326)
                      "LDAPSharedCacheSize is too small. Increase it or "
                      "reduce LDAPCacheEntries/LDAPOpCacheEntries!");
         if (cache->numentries < cache->fullmark) {
             /*
              * We have not even reached fullmark, trigger a complete purge.
              * This is still better than not being able to add new entries
