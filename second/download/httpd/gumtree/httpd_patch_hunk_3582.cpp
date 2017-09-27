         return APR_EGENERAL;
     }
 
     rv = apr_thread_mutex_create(&loaded.lock, APR_THREAD_MUTEX_DEFAULT,
                                  loaded.pool);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, APLOGNO(02682)
                      "Failed to create module cache lock");
         return rv;
     }
     return OK;
 }
 
