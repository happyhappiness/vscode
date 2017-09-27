         client_list->table[bucket] = entry;
     }
 
     apr_global_mutex_unlock(client_lock);
 
     if (entry) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01764)
                       "get_client(): client %lu found", key);
     }
     else {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01765)
                       "get_client(): client %lu not found", key);
     }
 
     return entry;
 }
 
