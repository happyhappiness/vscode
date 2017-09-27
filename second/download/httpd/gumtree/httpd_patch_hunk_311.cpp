      * child at once.
      */
     ap_scoreboard_image->parent[0].quiescing = 0;
     ap_scoreboard_image->parent[0].pid = child_pid;
 
     /* Wait for shutdown or restart events or for child death */
+    winnt_mpm_state = AP_MPMQ_RUNNING;
     rv = WaitForMultipleObjects(NUM_WAIT_HANDLES, (HANDLE *) event_handles, FALSE, INFINITE);
     cld = rv - WAIT_OBJECT_0;
     if (rv == WAIT_FAILED) {
         /* Something serious is wrong */
         ap_log_error(APLOG_MARK,APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                      "master_main: WaitForMultipeObjects WAIT_FAILED -- doing server shutdown");
