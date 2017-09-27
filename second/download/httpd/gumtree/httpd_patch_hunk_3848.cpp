     ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00163)
                 "%s configured -- resuming normal operations",
                 ap_get_server_description());
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00164)
                 "Server built: %s", ap_get_server_built());
     ap_log_command_line(plog, s);
+    ap_log_mpm_common(s);
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00165)
                 "Accept mutex: %s (default: %s)",
-                apr_proc_mutex_name(accept_mutex),
+                (all_buckets[0].mutex)
+                    ? apr_proc_mutex_name(all_buckets[0].mutex)
+                    : "none",
                 apr_proc_mutex_defname());
 
     mpm_state = AP_MPMQ_RUNNING;
 
     while (!restart_pending && !shutdown_pending) {
         int child_slot;
