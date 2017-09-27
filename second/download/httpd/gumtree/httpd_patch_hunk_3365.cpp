     chdir(use_dir);
 }
 #else
 #define chdir_for_gprof()
 #endif
 
+static void prefork_note_child_killed(int childnum, pid_t pid,
+                                      ap_generation_t gen)
+{
+    AP_DEBUG_ASSERT(childnum != -1); /* no scoreboard squatting with this MPM */
+    ap_run_child_status(ap_server_conf,
+                        ap_scoreboard_image->parent[childnum].pid,
+                        ap_scoreboard_image->parent[childnum].generation,
+                        childnum, MPM_CHILD_EXITED);
+    ap_scoreboard_image->parent[childnum].pid = 0;
+}
+
+static void prefork_note_child_started(int slot, pid_t pid)
+{
+    ap_scoreboard_image->parent[slot].pid = pid;
+    ap_run_child_status(ap_server_conf,
+                        ap_scoreboard_image->parent[slot].pid,
+                        retained->my_generation, slot, MPM_CHILD_STARTED);
+}
+
 /* a clean exit from a child with proper cleanup */
 static void clean_child_exit(int code) __attribute__ ((noreturn));
 static void clean_child_exit(int code)
 {
     mpm_state = AP_MPMQ_STOPPING;
 
     if (pchild) {
         apr_pool_destroy(pchild);
     }
+
+    if (one_process) {
+        prefork_note_child_killed(/* slot */ 0, 0, 0);
+    }
+
     ap_mpm_pod_close(pod);
     chdir_for_gprof();
     exit(code);
 }
 
 static void accept_mutex_on(void)
 {
     apr_status_t rv = apr_proc_mutex_lock(accept_mutex);
     if (rv != APR_SUCCESS) {
         const char *msg = "couldn't grab the accept mutex";
 
-        if (my_generation !=
+        if (retained->my_generation !=
             ap_scoreboard_image->global->running_generation) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, NULL, "%s", msg);
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf, APLOGNO(00143) "%s", msg);
             clean_child_exit(0);
         }
         else {
-            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, NULL, "%s", msg);
+            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf, APLOGNO(00144) "%s", msg);
             exit(APEXIT_CHILDFATAL);
         }
     }
 }
 
 static void accept_mutex_off(void)
 {
     apr_status_t rv = apr_proc_mutex_unlock(accept_mutex);
     if (rv != APR_SUCCESS) {
         const char *msg = "couldn't release the accept mutex";
 
-        if (my_generation !=
+        if (retained->my_generation !=
             ap_scoreboard_image->global->running_generation) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, NULL, "%s", msg);
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf, APLOGNO(00145) "%s", msg);
             /* don't exit here... we have a connection to
              * process, after which point we'll see that the
              * generation changed and we'll exit cleanly
              */
         }
         else {
-            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, NULL, "%s", msg);
+            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf, APLOGNO(00146) "%s", msg);
             exit(APEXIT_CHILDFATAL);
         }
     }
 }
 
 /* On some architectures it's safe to do unserialized accept()s in the single
