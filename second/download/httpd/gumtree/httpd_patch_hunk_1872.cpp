     pconf = pconf_;
 
     if (ap_exists_config_define("ONE_PROCESS") ||
         ap_exists_config_define("DEBUG"))
         one_process = -1;
 
+    /* XXX: presume proper privilages; one nice thing would be
+     * a loud emit if running as "LocalSystem"/"SYSTEM" to indicate
+     * they should change to a user with write access to logs/ alone.
+     */
+    ap_sys_privileges_handlers(1);
+
     if (!strcasecmp(signal_arg, "runservice")
-            && (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
             && (service_to_start_success != APR_SUCCESS)) {
         ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL,
                      "%s: Unable to start the service manager.",
                      service_name);
         exit(APEXIT_INIT);
     }
-
-    /* Win9x: disable AcceptEx */
-    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
-        use_acceptex = 0;
+    else if (!one_process && !my_generation) {
+        /* Open a null handle to soak stdout in this process.
+         * We need to emulate apr_proc_detach, unix performs this
+         * same check in the pre_config hook (although it is
+         * arguably premature).  Services already fixed this.
+         */
+        apr_file_t *nullfile;
+        apr_status_t rv;
+        apr_pool_t *pproc = apr_pool_parent_get(pconf);
+
+        if ((rv = apr_file_open(&nullfile, "NUL",
+                                APR_READ | APR_WRITE, APR_OS_DEFAULT,
+                                pproc)) == APR_SUCCESS) {
+            apr_file_t *nullstdout;
+            if (apr_file_open_stdout(&nullstdout, pproc)
+                    == APR_SUCCESS)
+                apr_file_dup2(nullstdout, nullfile, pproc);
+            apr_file_close(nullfile);
+        }
     }
 
     ap_listen_pre_config();
+    thread_limit = DEFAULT_THREAD_LIMIT;
     ap_threads_per_child = DEFAULT_THREADS_PER_CHILD;
     ap_pid_fname = DEFAULT_PIDLOG;
     ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
-#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
-        ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
-#endif
-    /* use_acceptex which is enabled by default is not available on Win9x.
+    ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
+
+    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));
+
+    return OK;
+}
+
+static int winnt_check_config(apr_pool_t *pconf, apr_pool_t *plog,
+                              apr_pool_t *ptemp, server_rec* s)
+{
+    int is_parent;
+    static int restart_num = 0;
+    int startup = 0;
+
+    /* We want this only in the parent and only the first time around */
+    is_parent = (parent_pid == my_pid);
+    if (is_parent && restart_num++ == 0) {
+        startup = 1;
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
+        } else if (is_parent) {
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
+        } else if (is_parent) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadLimit of %d not allowed, increasing to 1",
+                         thread_limit);
+        }
+        thread_limit = 1;
+    }
+
+    /* You cannot change ThreadLimit across a restart; ignore
+     * any such attempts.
      */
-    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
-        use_acceptex = 0;
+    if (!first_thread_limit) {
+        first_thread_limit = thread_limit;
+    }
+    else if (thread_limit != first_thread_limit) {
+        /* Don't need a startup console version here */
+        if (is_parent) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "changing ThreadLimit to %d from original value "
+                         "of %d not allowed during restart",
+                         thread_limit, first_thread_limit);
+        }
+        thread_limit = first_thread_limit;
     }
 
-    apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));
+    if (ap_threads_per_child > thread_limit) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
+                         "of", ap_threads_per_child);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " %d threads, decreasing to %d.",
+                         thread_limit, thread_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " To increase, please see the ThreadLimit "
+                         "directive.");
+        } else if (is_parent) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadsPerChild of %d exceeds ThreadLimit "
+                         "of %d, decreasing to match",
+                         ap_threads_per_child, thread_limit);
+        }
+        ap_threads_per_child = thread_limit;
+    }
+    else if (ap_threads_per_child < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: ThreadsPerChild of %d not allowed, "
+                         "increasing to 1.", ap_threads_per_child);
+        } else if (is_parent) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "ThreadsPerChild of %d not allowed, increasing to 1",
+                         ap_threads_per_child);
+        }
+        ap_threads_per_child = 1;
+    }
 
     return OK;
 }
 
 static int winnt_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec* s)
 {
