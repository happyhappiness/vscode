     ap_extended_status = 0;
     ap_min_spare_threads = DEFAULT_MIN_SPARE_THREAD;
     ap_max_spare_threads = DEFAULT_MAX_SPARE_THREAD;
 #ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
         ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
 #endif
+    ap_sys_privileges_handlers(1);
+
+    return OK;
+}
+
+
+
+static int mpmt_os2_check_config(apr_pool_t *p, apr_pool_t *plog,
+                                 apr_pool_t *ptemp, server_rec *s)
+{
+    static int restart_num = 0;
+    int startup = 0;
+
+    /* we want this only the first time around */
+    if (restart_num++ == 0) {
+        startup = 1;
+    }
+
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
+    if (ap_min_spare_threads < 1) {
+        if (startup) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         "WARNING: MinSpareThreads of %d not allowed, "
+                         "increasing to 1", ap_min_spare_threads);
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " to avoid almost certain server failure.");
+            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL,
+                         " Please read the documentation.");
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "MinSpareThreads of %d not allowed, increasing to 1",
+                         ap_min_spare_threads);
+        }
+        ap_min_spare_threads = 1;
+    }
 
     return OK;
 }
 
 
 
 static void mpmt_os2_hooks(apr_pool_t *p)
 {
     ap_hook_pre_config(mpmt_os2_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_check_config(mpmt_os2_check_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm(mpmt_os2_run, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_query(mpmt_os2_query, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_get_name(mpmt_os2_get_name, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_mpm_note_child_killed(mpmt_os2_note_child_killed, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 
 
 static const char *set_daemons_to_start(cmd_parms *cmd, void *dummy, const char *arg)
 {
