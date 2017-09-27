         ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf, APLOGNO(00479)
                      "Couldn't initialize signal thread");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     if (ap_max_requests_per_child) {
-        requests_this_child = ap_max_requests_per_child;
+        conns_this_child = ap_max_requests_per_child;
     }
     else {
         /* coding a value of zero means infinity */
-        requests_this_child = INT_MAX;
+        conns_this_child = APR_INT32_MAX;
     }
 
     /* Setup worker threads */
 
     /* clear the storage; we may not create all our threads immediately,
      * and we want a 0 entry to indicate a thread which was not created
