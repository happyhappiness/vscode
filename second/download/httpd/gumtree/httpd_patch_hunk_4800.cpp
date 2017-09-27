 
         rv = mc->stapling_cache->init(mc->stapling_cache_context,
                                      "mod_ssl-stapling", &hints, s, p);
         if (rv) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01872)
                          "Could not initialize stapling cache. Exiting.");
-            ssl_die();
+            ssl_die(s);
         }
     }
 #endif
 
     /*
      * Warn the user that he should use the session cache.
