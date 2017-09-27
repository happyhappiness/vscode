     client_list->table[bucket] = entry;
     client_list->num_created++;
     client_list->num_entries++;
 
     apr_global_mutex_unlock(client_lock);
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01768)
                  "allocated new client %lu", key);
 
     return entry;
 }
 
 
