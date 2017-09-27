 
     st->compare_cache_size = atol(size);
     if (st->compare_cache_size < 0) {
         st->compare_cache_size = 0;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01302)
                  "ldap cache: Setting operation cache size to %ld entries.",
                  st->compare_cache_size);
 
     return NULL;
 }
 
