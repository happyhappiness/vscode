     return NULL;
 }
 
 static const char *set_max_clients (cmd_parms *cmd, void *dummy,
                                      const char *arg)
 {
-    int max_clients;
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
-    /* It is ok to use ap_threads_per_child here because we are
-     * sure that it gets set before MaxClients in the pre_config stage. */
     max_clients = atoi(arg);
-    if (max_clients < ap_threads_per_child) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: MaxClients (%d) must be at least as large",
-                    max_clients);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " as ThreadsPerChild (%d). Automatically",
-                    ap_threads_per_child);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " increasing MaxClients to %d.",
-                    ap_threads_per_child);
-       max_clients = ap_threads_per_child;
-    }
-    ap_daemons_limit = max_clients / ap_threads_per_child;
-    if ((max_clients > 0) && (max_clients % ap_threads_per_child)) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: MaxClients (%d) is not an integer multiple",
-                    max_clients);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " of ThreadsPerChild (%d), lowering MaxClients to %d",
-                    ap_threads_per_child,
-                    ap_daemons_limit * ap_threads_per_child);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " for a maximum of %d child processes,",
-                    ap_daemons_limit);
-       max_clients = ap_daemons_limit * ap_threads_per_child;
-    }
-    if (ap_daemons_limit > server_limit) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: MaxClients of %d would require %d servers,",
-                    max_clients, ap_daemons_limit);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " and would exceed the ServerLimit value of %d.",
-                    server_limit);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " Automatically lowering MaxClients to %d.  To increase,",
-                    server_limit * ap_threads_per_child);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " please see the ServerLimit directive.");
-       ap_daemons_limit = server_limit;
-    }
-    else if (ap_daemons_limit < 1) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "WARNING: Require MaxClients > 0, setting to 1");
-        ap_daemons_limit = 1;
-    }
     return NULL;
 }
 
 static const char *set_threads_per_child (cmd_parms *cmd, void *dummy,
                                           const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
-    ap_threads_per_child = atoi(arg);
-    if (ap_threads_per_child > thread_limit) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
-                     "value of %d", ap_threads_per_child,
-                     thread_limit);
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "threads, lowering ThreadsPerChild to %d. To increase, please"
-                     " see the", thread_limit);
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     " ThreadLimit directive.");
-        ap_threads_per_child = thread_limit;
-    }
-    else if (ap_threads_per_child < 1) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "WARNING: Require ThreadsPerChild > 0, setting to 1");
-        ap_threads_per_child = 1;
-    }
+    threads_per_child = atoi(arg);
     return NULL;
 }
 
 static const char *set_server_limit (cmd_parms *cmd, void *dummy, const char *arg)
 {
-    int tmp_server_limit;
-
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
-    tmp_server_limit = atoi(arg);
-    /* you cannot change ServerLimit across a restart; ignore
-     * any such attempts
-     */
-    if (first_server_limit &&
-        tmp_server_limit != server_limit) {
-        /* how do we log a message?  the error log is a bit bucket at this
-         * point; we'll just have to set a flag so that ap_mpm_run()
-         * logs a warning later
-         */
-        changed_limit_at_restart = 1;
-        return NULL;
-    }
-    server_limit = tmp_server_limit;
-
-    if (server_limit > MAX_SERVER_LIMIT) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: ServerLimit of %d exceeds compile time limit "
-                    "of %d servers,", server_limit, MAX_SERVER_LIMIT);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " lowering ServerLimit to %d.", MAX_SERVER_LIMIT);
-       server_limit = MAX_SERVER_LIMIT;
-    }
-    else if (server_limit < 1) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "WARNING: Require ServerLimit > 0, setting to 1");
-        server_limit = 1;
-    }
+    server_limit = atoi(arg);
     return NULL;
 }
 
 static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg)
 {
-    int tmp_thread_limit;
-
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
-    tmp_thread_limit = atoi(arg);
-    /* you cannot change ThreadLimit across a restart; ignore
-     * any such attempts
-     */
-    if (first_thread_limit &&
-        tmp_thread_limit != thread_limit) {
-        /* how do we log a message?  the error log is a bit bucket at this
-         * point; we'll just have to set a flag so that ap_mpm_run()
-         * logs a warning later
-         */
-        changed_limit_at_restart = 1;
-        return NULL;
-    }
-    thread_limit = tmp_thread_limit;
-
-    if (thread_limit > MAX_THREAD_LIMIT) {
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    "WARNING: ThreadLimit of %d exceeds compile time limit "
-                    "of %d servers,", thread_limit, MAX_THREAD_LIMIT);
-       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                    " lowering ThreadLimit to %d.", MAX_THREAD_LIMIT);
-       thread_limit = MAX_THREAD_LIMIT;
-    }
-    else if (thread_limit < 1) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "WARNING: Require ThreadLimit > 0, setting to 1");
-        thread_limit = 1;
-    }
+    thread_limit = atoi(arg);
     return NULL;
 }
 
 static const command_rec worker_cmds[] = {
-UNIX_DAEMON_COMMANDS,
 LISTEN_COMMANDS,
 AP_INIT_TAKE1("StartServers", set_daemons_to_start, NULL, RSRC_CONF,
   "Number of child processes launched at server startup"),
 AP_INIT_TAKE1("MinSpareThreads", set_min_spare_threads, NULL, RSRC_CONF,
   "Minimum number of idle threads, to handle request spikes"),
 AP_INIT_TAKE1("MaxSpareThreads", set_max_spare_threads, NULL, RSRC_CONF,
