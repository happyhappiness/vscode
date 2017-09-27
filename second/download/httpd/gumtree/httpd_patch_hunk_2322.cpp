     st->compare_cache_size = atol(size);
     if (st->compare_cache_size < 0) {
         st->compare_cache_size = 0;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
-                 "[%" APR_PID_T_FMT "] ldap cache: Setting operation cache size"
-                 " to %ld entries.", getpid(), st->compare_cache_size);
+                 "ldap cache: Setting operation cache size to %ld entries.",
+                 st->compare_cache_size);
 
     return NULL;
 }
 
 
 /**
