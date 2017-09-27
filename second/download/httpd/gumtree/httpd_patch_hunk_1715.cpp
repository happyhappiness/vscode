     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "proxy: %s: has acquired connection for (%s)",
                  proxy_function, worker->hostname);
 
     (*conn)->worker = worker;
     (*conn)->close  = 0;
-    (*conn)->close_on_recycle = 0;
 #if APR_HAS_THREADS
     (*conn)->inreslist = 0;
 #endif
 
     return OK;
 }
