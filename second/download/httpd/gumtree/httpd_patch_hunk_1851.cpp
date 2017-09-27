             }
         }
 
         parent_pid = ap_my_pid = getpid();
     }
 
-    unixd_pre_config(ptemp);
     ap_listen_pre_config();
     ap_daemons_to_start = DEFAULT_START_DAEMON;
     ap_daemons_min_free = DEFAULT_MIN_FREE_DAEMON;
     ap_daemons_max_free = DEFAULT_MAX_FREE_DAEMON;
+    server_limit = DEFAULT_SERVER_LIMIT;
     ap_daemons_limit = server_limit;
     ap_pid_fname = DEFAULT_PIDLOG;
-    ap_lock_fname = DEFAULT_LOCKFILE;
     ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
     ap_extended_status = 0;
-#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
     ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
-#endif
 
     apr_cpystrn(ap_coredump_dir, ap_server_root, sizeof(ap_coredump_dir));
 
     return OK;
 }
 
+static int prefork_check_config(apr_pool_t *p, apr_pool_t *plog,
+                                apr_pool_t *ptemp, server_rec *s)
+{
+    int startup = 0;
+
+    /* the reverse of pre_config, we want this only the first time around */
+    if (retained->module_loads == 1) {
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
+    if (ap_daemons_limit > server_limit) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MaxClients of %d exceeds ServerLimit "
+                         "value of", ap_daemons_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " %d servers, decreasing MaxClients to %d.",
+                         server_limit, server_limit);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " To increase, please see the ServerLimit "
+                         "directive.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MaxClients of %d exceeds ServerLimit value "
+                         "of %d, decreasing to match",
+                         ap_daemons_limit, server_limit);
+        }
+        ap_daemons_limit = server_limit;
+    }
+    else if (ap_daemons_limit < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MaxClients of %d not allowed, "
+                         "increasing to 1.", ap_daemons_limit);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MaxClients of %d not allowed, increasing to 1",
+                         ap_daemons_limit);
+        }
+        ap_daemons_limit = 1;
+    }
+
+    /* ap_daemons_to_start > ap_daemons_limit checked in prefork_run() */
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
+    if (ap_daemons_min_free < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MinSpareServers of %d not allowed, "
+                         "increasing to 1", ap_daemons_min_free);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " to avoid almost certain server failure.");
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " Please read the documentation.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MinSpareServers of %d not allowed, increasing to 1",
+                         ap_daemons_min_free);
+        }
+        ap_daemons_min_free = 1;
+    }
+
+    /* ap_daemons_max_free < ap_daemons_min_free + 1 checked in prefork_run() */
+
+    return OK;
+}
+
 static void prefork_hooks(apr_pool_t *p)
 {
-    /* The prefork open_logs phase must run before the core's, or stderr
+    /* Our open_logs hook function must run before the core's, or stderr
      * will be redirected to a file, and the messages won't print to the
      * console.
      */
     static const char *const aszSucc[] = {"core.c", NULL};
 
-#ifdef AUX3
-    (void) set42sig();
-#endif
-
-    ap_hook_open_logs(prefork_open_logs, NULL, aszSucc, APR_HOOK_MIDDLE);
+    ap_hook_open_logs(prefork_open_logs, NULL, aszSucc, APR_HOOK_REALLY_FIRST);
     /* we need to set the MPM state before other pre-config hooks use MPM query
      * to retrieve it, so register as REALLY_FIRST
      */
     ap_hook_pre_config(prefork_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
+    ap_hook_check_config(prefork_check_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm(prefork_run, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_query(prefork_query, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_note_child_killed(prefork_note_child_killed, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_get_name(prefork_get_name, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 static const char *set_daemons_to_start(cmd_parms *cmd, void *dummy, const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
