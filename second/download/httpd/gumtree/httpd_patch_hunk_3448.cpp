     ts->child_num_arg = child_num_arg;
     ts->threadattr = thread_attr;
 
     rv = apr_thread_create(&start_thread_id, thread_attr, start_threads,
                            ts, pchild);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf, APLOGNO(00282)
                      "apr_thread_create: unable to create worker thread");
         /* let the parent decide how bad this really is */
         clean_child_exit(APEXIT_CHILDSICK);
     }
 
     mpm_state = AP_MPMQ_RUNNING;
