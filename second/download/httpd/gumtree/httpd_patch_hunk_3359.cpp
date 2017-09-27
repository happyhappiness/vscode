         has not been explicitly forced to close on exit(). (ie. the -E flag
         was specified at startup) */
     if (hold_screen_on_exit > 0) {
         hold_screen_on_exit = 0;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00224)
             "%s configured -- resuming normal operations",
             ap_get_server_description());
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00225)
             "Server built: %s", ap_get_server_built());
     ap_log_command_line(plog, s);
     show_server_data();
 
     mpm_state = AP_MPMQ_RUNNING;
     while (!restart_pending && !shutdown_pending) {
