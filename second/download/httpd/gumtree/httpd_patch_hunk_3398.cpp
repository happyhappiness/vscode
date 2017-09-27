     HANDLE *child_handles;
     int listener_started = 0;
     int threads_created = 0;
     int watch_thread;
     int time_remains;
     int cld;
-    int tid;
+    DWORD tid;
     int rv;
     int i;
 
     apr_pool_create(&pchild, pconf);
     apr_pool_tag(pchild, "pchild");
 
     ap_run_child_init(pchild, ap_server_conf);
     ht = apr_hash_make(pchild);
 
     /* Initialize the child_events */
     max_requests_per_child_event = CreateEvent(NULL, TRUE, FALSE, NULL);
     if (!max_requests_per_child_event) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
-                     "Child %d: Failed to create a max_requests event.", 
-                     my_pid);
+        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00350)
+                     "Child: Failed to create a max_requests event.");
         exit(APEXIT_CHILDINIT);
     }
     child_events[0] = exit_event;
     child_events[1] = max_requests_per_child_event;
 
     /*
      * Wait until we have permission to start accepting connections.
      * start_mutex is used to ensure that only one child ever
      * goes into the listen/accept loop at once.
      */
     status = apr_proc_mutex_lock(start_mutex);
     if (status != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
-                     "Child %d: Failed to acquire the start_mutex. "
-                     "Process will exit.", my_pid);
+        ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf, APLOGNO(00351)
+                     "Child: Failed to acquire the start_mutex. "
+                     "Process will exit.");
         exit(APEXIT_CHILDINIT);
     }
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                 "Child %d: Acquired the start mutex.", my_pid);
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00352)
+                 "Child: Acquired the start mutex.");
 
     /*
      * Create the worker thread dispatch IOCompletionPort
      */
     /* Create the worker thread dispatch IOCP */
     ThreadDispatchIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
-                                                NULL, 0, 0); 
+                                                NULL, 0, 0);
     apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
     qwait_event = CreateEvent(NULL, TRUE, FALSE, NULL);
     if (!qwait_event) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), 
-                     ap_server_conf,
-                     "Child %d: Failed to create a qwait event.", my_pid);
+        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
+                     ap_server_conf, APLOGNO(00353)
+                     "Child: Failed to create a qwait event.");
         exit(APEXIT_CHILDINIT);
     }
 
     /*
      * Create the pool of worker threads
      */
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                 "Child %d: Starting %d worker threads.",
-                 my_pid, ap_threads_per_child);
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00354)
+                 "Child: Starting %d worker threads.", ap_threads_per_child);
     child_handles = (HANDLE) apr_pcalloc(pchild, ap_threads_per_child
                                                   * sizeof(HANDLE));
     apr_thread_mutex_create(&child_lock, APR_THREAD_MUTEX_DEFAULT, pchild);
 
     while (1) {
         for (i = 0; i < ap_threads_per_child; i++) {
             int *score_idx;
             int status = ap_scoreboard_image->servers[0][i].status;
             if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                 continue;
             }
             ap_update_child_status_from_indexes(0, i, SERVER_STARTING, NULL);
-        
+
             child_handles[i] = CreateThread(NULL, ap_thread_stacksize,
                                             worker_main, (void *) i,
                                             stack_res_flag, &tid);
             if (child_handles[i] == 0) {
                 ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
-                             ap_server_conf,
-                             "Child %d: CreateThread failed. Unable to "
+                             ap_server_conf, APLOGNO(00355)
+                             "Child: CreateThread failed. Unable to "
                              "create all worker threads. Created %d of the %d "
                              "threads requested with the ThreadsPerChild "
                              "configuration directive.",
-                             my_pid, threads_created, ap_threads_per_child);
+                             threads_created, ap_threads_per_child);
                 ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
                 goto shutdown;
             }
             threads_created++;
-            /* Save the score board index in ht keyed to the thread handle. 
+            /* Save the score board index in ht keyed to the thread handle.
              * We need this when cleaning up threads down below...
              */
             apr_thread_mutex_lock(child_lock);
             score_idx = apr_pcalloc(pchild, sizeof(int));
             *score_idx = i;
             apr_hash_set(ht, &child_handles[i], sizeof(HANDLE), score_idx);
