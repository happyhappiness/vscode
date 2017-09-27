 
     st->search_cache_size = atol(size);
     if (st->search_cache_size < 0) {
         st->search_cache_size = 0;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01300)
                  "ldap cache: Setting search cache size to %ld entries.",
                  st->search_cache_size);
 
     return NULL;
 }
 
