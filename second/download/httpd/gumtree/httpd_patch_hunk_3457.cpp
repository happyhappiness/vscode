     ap_mutex_register(pconf, AP_ACCEPT_MUTEX_TYPE, NULL, APR_LOCK_DEFAULT, 0);
 
     /* sigh, want this only the second time around */
     retained = ap_retained_data_get(userdata_key);
     if (!retained) {
         retained = ap_retained_data_create(userdata_key, sizeof(*retained));
+        retained->max_daemons_limit = -1;
+        retained->idle_spawn_rate = 1;
     }
     ++retained->module_loads;
     if (retained->module_loads == 2) {
-        is_graceful = 0;
-
         if (!one_process && !foreground) {
+            /* before we detach, setup crash handlers to log to errorlog */
+            ap_fatal_signal_setup(ap_server_conf, pconf);
             rv = apr_proc_detach(no_detach ? APR_PROC_DETACH_FOREGROUND
                                            : APR_PROC_DETACH_DAEMONIZE);
             if (rv != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
+                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00299)
                              "apr_proc_detach failed");
                 return HTTP_INTERNAL_SERVER_ERROR;
             }
         }
-        parent_pid = ap_my_pid = getpid();
     }
 
+    parent_pid = ap_my_pid = getpid();
+
     ap_listen_pre_config();
     ap_daemons_to_start = DEFAULT_START_DAEMON;
     min_spare_threads = DEFAULT_MIN_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
     max_spare_threads = DEFAULT_MAX_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
     server_limit = DEFAULT_SERVER_LIMIT;
     thread_limit = DEFAULT_THREAD_LIMIT;
     ap_daemons_limit = server_limit;
     threads_per_child = DEFAULT_THREADS_PER_CHILD;
-    max_clients = ap_daemons_limit * threads_per_child;
-    ap_pid_fname = DEFAULT_PIDLOG;
-    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
+    max_workers = ap_daemons_limit * threads_per_child;
     ap_extended_status = 0;
-    ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
-
-    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));
 
     return OK;
 }
 
 static int worker_check_config(apr_pool_t *p, apr_pool_t *plog,
                                apr_pool_t *ptemp, server_rec *s)
 {
-    static int restart_num = 0;
     int startup = 0;
 
     /* the reverse of pre_config, we want this only the first time around */
-    if (restart_num++ == 0) {
+    if (retained->module_loads == 1) {
         startup = 1;
     }
 
     if (server_limit > MAX_SERVER_LIMIT) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00300)
                          "WARNING: ServerLimit of %d exceeds compile-time "
                          "limit of", server_limit);
             ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
                          " %d servers, decreasing to %d.",
                          MAX_SERVER_LIMIT, MAX_SERVER_LIMIT);
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00301)
                          "ServerLimit of %d exceeds compile-time limit "
                          "of %d, decreasing to match",
                          server_limit, MAX_SERVER_LIMIT);
         }
         server_limit = MAX_SERVER_LIMIT;
     }
     else if (server_limit < 1) {
         if (startup) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00302)
                          "WARNING: ServerLimit of %d not allowed, "
                          "increasing to 1.", server_limit);
         } else {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00303)
                          "ServerLimit of %d not allowed, increasing to 1",
                          server_limit);
         }
         server_limit = 1;
     }
 
