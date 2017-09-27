                 ap_get_server_description());
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00207)
                 "Server built: %s", ap_get_server_built());
     if (one_process) {
         ap_scoreboard_image->parent[0].pid = getpid();
         ap_mpm_child_main(pconf);
-        return FALSE;
+        return DONE;
     }
 
     while (!restart_pending && !shutdown_pending) {
         RESULTCODES proc_rc;
         PID child_pid;
         int active_children = 0;
