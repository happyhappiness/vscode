 
         rv = conf->provider->socache_provider->init(
                 conf->provider->socache_instance, cache_socache_id,
                 &socache_hints, s, pconf);
         if (rv != APR_SUCCESS) {
             ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02393)
-            "failed to initialise %s cache", cache_socache_id);
+                    "failed to initialise %s cache", cache_socache_id);
             return 500; /* An HTTP status would be a misnomer! */
         }
         apr_pool_cleanup_register(pconf, (void *) s, destroy_cache,
                 apr_pool_cleanup_null);
 
     }
