 
     ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
             "%s configured -- resuming normal operations",
             ap_get_server_description());
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
             "Server built: %s", ap_get_server_built());
-#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
-            "AcceptMutex: %s (default: %s)",
-            apr_proc_mutex_name(accept_mutex),
-            apr_proc_mutex_defname());
-#endif
+    ap_log_command_line(plog, s);
     show_server_data();
 
     mpm_state = AP_MPMQ_RUNNING;
     while (!restart_pending && !shutdown_pending) {
         perform_idle_server_maintenance(pconf);
         if (show_settings)
