     /* Setup worker threads */
 
     /* clear the storage; we may not create all our threads immediately,
      * and we want a 0 entry to indicate a thread which was not created
      */
     threads = (apr_thread_t **)calloc(1,
-                                sizeof(apr_thread_t *) * ap_threads_per_child);
+                                sizeof(apr_thread_t *) * threads_per_child);
     if (threads == NULL) {
         ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
                      "malloc: out of memory");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
