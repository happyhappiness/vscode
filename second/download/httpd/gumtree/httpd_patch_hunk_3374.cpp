      * supposed to start up without the 1 second penalty between each fork.
      */
     remaining_children_to_start = ap_daemons_to_start;
     if (remaining_children_to_start > ap_daemons_limit) {
         remaining_children_to_start = ap_daemons_limit;
     }
-    if (!is_graceful) {
+    if (!retained->is_graceful) {
         startup_children(remaining_children_to_start);
         remaining_children_to_start = 0;
     }
     else {
         /* give the system some time to recover before kicking into
          * exponential mode
          */
-        hold_off_on_exponential_spawning = 10;
+        retained->hold_off_on_exponential_spawning = 10;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00163)
                 "%s configured -- resuming normal operations",
                 ap_get_server_description());
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00164)
                 "Server built: %s", ap_get_server_built());
     ap_log_command_line(plog, s);
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00165)
                 "Accept mutex: %s (default: %s)",
                 apr_proc_mutex_name(accept_mutex),
                 apr_proc_mutex_defname());
-    restart_pending = shutdown_pending = 0;
 
     mpm_state = AP_MPMQ_RUNNING;
 
     while (!restart_pending && !shutdown_pending) {
         int child_slot;
         apr_exit_why_e exitwhy;
