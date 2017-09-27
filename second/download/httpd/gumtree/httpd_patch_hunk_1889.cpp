     int loops;
     int prev_threads_created;
 
     /* We must create the fd queues before we start up the listener
      * and worker threads. */
     worker_queue = apr_pcalloc(pchild, sizeof(*worker_queue));
-    rv = ap_queue_init(worker_queue, ap_threads_per_child, pchild);
+    rv = ap_queue_init(worker_queue, threads_per_child, pchild);
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                      "ap_queue_init() failed");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     rv = ap_queue_info_create(&worker_queue_info, pchild,
-                              ap_threads_per_child);
+                              threads_per_child);
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                      "ap_queue_info_create() failed");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
-    worker_sockets = apr_pcalloc(pchild, ap_threads_per_child
+    worker_sockets = apr_pcalloc(pchild, threads_per_child
                                         * sizeof(apr_socket_t *));
 
     loops = prev_threads_created = 0;
     while (1) {
-        /* ap_threads_per_child does not include the listener thread */
-        for (i = 0; i < ap_threads_per_child; i++) {
+        /* threads_per_child does not include the listener thread */
+        for (i = 0; i < threads_per_child; i++) {
             int status = ap_scoreboard_image->servers[child_num_arg][i].status;
 
             if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                 continue;
             }
 
