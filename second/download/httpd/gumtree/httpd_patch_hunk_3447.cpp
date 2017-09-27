 
     /* Setup worker threads */
 
     /* clear the storage; we may not create all our threads immediately,
      * and we want a 0 entry to indicate a thread which was not created
      */
-    threads = (apr_thread_t **)calloc(1,
-                                sizeof(apr_thread_t *) * threads_per_child);
-    if (threads == NULL) {
-        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
-                     "malloc: out of memory");
-        clean_child_exit(APEXIT_CHILDFATAL);
-    }
-
+    threads = (apr_thread_t **)ap_calloc(1,
+                                  sizeof(apr_thread_t *) * threads_per_child);
     ts = (thread_starter *)apr_palloc(pchild, sizeof(*ts));
 
     apr_threadattr_create(&thread_attr, pchild);
     /* 0 means PTHREAD_CREATE_JOINABLE */
     apr_threadattr_detach_set(thread_attr, 0);
 
