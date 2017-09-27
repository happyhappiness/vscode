                 return HTTP_INTERNAL_SERVER_ERROR;
             }
         }
         parent_pid = ap_my_pid = getpid();
     }
 
-    unixd_pre_config(ptemp);
     ap_listen_pre_config();
     ap_daemons_to_start = DEFAULT_START_DAEMON;
     min_spare_threads = DEFAULT_MIN_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
     max_spare_threads = DEFAULT_MAX_FREE_DAEMON * DEFAULT_THREADS_PER_CHILD;
+    server_limit = DEFAULT_SERVER_LIMIT;
+    thread_limit = DEFAULT_THREAD_LIMIT;
     ap_daemons_limit = server_limit;
-    ap_threads_per_child = DEFAULT_THREADS_PER_CHILD;
+    threads_per_child = DEFAULT_THREADS_PER_CHILD;
+    max_clients = ap_daemons_limit * threads_per_child;
     ap_pid_fname = DEFAULT_PIDLOG;
-    ap_lock_fname = DEFAULT_LOCKFILE;
     ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
-    had_healthy_child = 0;
     ap_extended_status = 0;
-#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
-        ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
-#endif
+    ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
 
     apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));
 
     return OK;
 }
 
+static int worker_check_config(apr_pool_t *p, apr_pool_t *plog,
+                               apr_pool_t *ptemp, server_rec *s)
+{
+    static int restart_num = 0;
+    int startup = 0;
+
+    /* the reverse of pre_config, we want this only the first time around */
+    if (restart_num++ == 0) {
+        startup = 1;
+    }
+
+    if (server_limit > MAX_SERVER_LIMIT) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ServerLimit of %d exceeds compile-time "
+                         "limit of", server_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " %d servers, decreasing to %d.",
+                         MAX_SERVER_LIMIT, MAX_SERVER_LIMIT);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ServerLimit of %d exceeds compile-time limit "
+                         "of %d, decreasing to match",
+                         server_limit, MAX_SERVER_LIMIT);
+        }
+        server_limit = MAX_SERVER_LIMIT;
+    }
+    else if (server_limit < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ServerLimit of %d not allowed, "
+                         "increasing to 1.", server_limit);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ServerLimit of %d not allowed, increasing to 1",
+                         server_limit);
+        }
+        server_limit = 1;
+    }
+
+    /* you cannot change ServerLimit across a restart; ignore
+     * any such attempts
+     */
+    if (!retained->first_server_limit) {
+        retained->first_server_limit = server_limit;
+    }
+    else if (server_limit != retained->first_server_limit) {
+        /* don't need a startup console version here */
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                     "changing ServerLimit to %d from original value of %d "
+                     "not allowed during restart",
+                     server_limit, retained->first_server_limit);
+        server_limit = retained->first_server_limit;
+    }
+
+    if (thread_limit > MAX_THREAD_LIMIT) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ThreadLimit of %d exceeds compile-time "
+                         "limit of", thread_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " %d threads, decreasing to %d.",
+                         MAX_THREAD_LIMIT, MAX_THREAD_LIMIT);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadLimit of %d exceeds compile-time limit "
+                         "of %d, decreasing to match",
+                         thread_limit, MAX_THREAD_LIMIT);
+        }
+        thread_limit = MAX_THREAD_LIMIT;
+    }
+    else if (thread_limit < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ThreadLimit of %d not allowed, "
+                         "increasing to 1.", thread_limit);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadLimit of %d not allowed, increasing to 1",
+                         thread_limit);
+        }
+        thread_limit = 1;
+    }
+
+    /* you cannot change ThreadLimit across a restart; ignore
+     * any such attempts
+     */
+    if (!retained->first_thread_limit) {
+        retained->first_thread_limit = thread_limit;
+    }
+    else if (thread_limit != retained->first_thread_limit) {
+        /* don't need a startup console version here */
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                     "changing ThreadLimit to %d from original value of %d "
+                     "not allowed during restart",
+                     thread_limit, retained->first_thread_limit);
+        thread_limit = retained->first_thread_limit;
+    }
+
+    if (threads_per_child > thread_limit) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
+                         "of", threads_per_child);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " %d threads, decreasing to %d.",
+                         thread_limit, thread_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " To increase, please see the ThreadLimit "
+                         "directive.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadsPerChild of %d exceeds ThreadLimit "
+                         "of %d, decreasing to match",
+                         threads_per_child, thread_limit);
+        }
+        threads_per_child = thread_limit;
+    }
+    else if (threads_per_child < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ThreadsPerChild of %d not allowed, "
+                         "increasing to 1.", threads_per_child);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadsPerChild of %d not allowed, increasing to 1",
+                         threads_per_child);
+        }
+        threads_per_child = 1;
+    }
+
+    if (max_clients < threads_per_child) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MaxClients of %d is less than "
+                         "ThreadsPerChild of", max_clients);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " %d, increasing to %d.  MaxClients must be at "
+                         "least as large",
+                         threads_per_child, threads_per_child);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " as the number of threads in a single server.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MaxClients of %d is less than ThreadsPerChild "
+                         "of %d, increasing to match",
+                         max_clients, threads_per_child);
+        }
+        max_clients = threads_per_child;
+    }
+
+    ap_daemons_limit = max_clients / threads_per_child;
+
+    if (max_clients % threads_per_child) {
+        int tmp_max_clients = ap_daemons_limit * threads_per_child;
+
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MaxClients of %d is not an integer "
+                         "multiple of", max_clients);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " ThreadsPerChild of %d, decreasing to nearest "
+                         "multiple %d,", threads_per_child,
+                         tmp_max_clients);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " for a maximum of %d servers.",
+                         ap_daemons_limit);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MaxClients of %d is not an integer multiple of "
+                         "ThreadsPerChild of %d, decreasing to nearest "
+                         "multiple %d", max_clients, threads_per_child,
+                         tmp_max_clients);
+        }
+        max_clients = tmp_max_clients;
+    }
+
+    if (ap_daemons_limit > server_limit) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MaxClients of %d would require %d "
+                         "servers and ", max_clients, ap_daemons_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " would exceed ServerLimit of %d, decreasing to %d.",
+                         server_limit, server_limit * threads_per_child);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " To increase, please see the ServerLimit "
+                         "directive.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MaxClients of %d would require %d servers and "
+                         "exceed ServerLimit of %d, decreasing to %d",
+                         max_clients, ap_daemons_limit, server_limit,
+                         server_limit * threads_per_child);
+        }
+        ap_daemons_limit = server_limit;
+    }
+
+    /* ap_daemons_to_start > ap_daemons_limit checked in worker_run() */
+    if (ap_daemons_to_start < 0) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: StartServers of %d not allowed, "
+                         "increasing to 1.", ap_daemons_to_start);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "StartServers of %d not allowed, increasing to 1",
+                         ap_daemons_to_start);
+        }
+        ap_daemons_to_start = 1;
+    }
+
+    if (min_spare_threads < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MinSpareThreads of %d not allowed, "
+                         "increasing to 1", min_spare_threads);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " to avoid almost certain server failure.");
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " Please read the documentation.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MinSpareThreads of %d not allowed, increasing to 1",
+                         min_spare_threads);
+        }
+        min_spare_threads = 1;
+    }
+
+    /* max_spare_threads < min_spare_threads + threads_per_child
+     * checked in worker_run()
+     */
+
+    return OK;
+}
+
 static void worker_hooks(apr_pool_t *p)
 {
-    /* The worker open_logs phase must run before the core's, or stderr
+    /* Our open_logs hook function must run before the core's, or stderr
      * will be redirected to a file, and the messages won't print to the
      * console.
      */
     static const char *const aszSucc[] = {"core.c", NULL};
     one_process = 0;
 
-    ap_hook_open_logs(worker_open_logs, NULL, aszSucc, APR_HOOK_MIDDLE);
+    ap_hook_open_logs(worker_open_logs, NULL, aszSucc, APR_HOOK_REALLY_FIRST);
     /* we need to set the MPM state before other pre-config hooks use MPM query
      * to retrieve it, so register as REALLY_FIRST
      */
     ap_hook_pre_config(worker_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
+    ap_hook_check_config(worker_check_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm(worker_run, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_query(worker_query, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_note_child_killed(worker_note_child_killed, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_get_name(worker_get_name, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 static const char *set_daemons_to_start(cmd_parms *cmd, void *dummy,
                                         const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
