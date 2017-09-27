             exitcode = APEXIT_CHILDFATAL;
         }
         if (   exitcode == APEXIT_CHILDFATAL
             || exitcode == APEXIT_CHILDINIT
             || exitcode == APEXIT_INIT) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
-                         "Parent: child process exited with status %lu -- Aborting.", exitcode);
+                         "Parent: child process exited with status %u -- Aborting.", exitcode);
             shutdown_pending = 1;
         }
         else {
             int i;
             restart_pending = 1;
             ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                         "Parent: child process exited with status %lu -- Restarting.", exitcode);
+                         "Parent: child process exited with status %u -- Restarting.", exitcode);
             for (i = 0; i < ap_threads_per_child; i++) {
                 ap_update_child_status_from_indexes(0, i, SERVER_DEAD, NULL);
             }
         }
         CloseHandle(event_handles[CHILD_HANDLE]);
         event_handles[CHILD_HANDLE] = NULL;
     }
     if (restart_pending) {
-        ++ap_my_generation;
-        ap_scoreboard_image->global->running_generation = ap_my_generation;
+        ++my_generation;
+        ap_scoreboard_image->global->running_generation = my_generation;
     }
 die_now:
     if (shutdown_pending)
     {
         int timeout = 30000;  /* Timeout is milliseconds */
         winnt_mpm_state = AP_MPMQ_STOPPING;
 
-        if (!child_created) {
-            return 0;  /* Tell the caller we do not want to restart */
-        }
-
         /* This shutdown is only marginally graceful. We will give the
          * child a bit of time to exit gracefully. If the time expires,
          * the child will be wacked.
          */
         if (!strcasecmp(signal_arg, "runservice")) {
             mpm_service_stopping();
         }
         /* Signal the child processes to exit */
         if (SetEvent(child_exit_event) == 0) {
                 ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_os_error(), ap_server_conf,
-                             "Parent: SetEvent for child process %pp failed",
-                             event_handles[CHILD_HANDLE]);
+                             "Parent: SetEvent for child process %d failed", event_handles[CHILD_HANDLE]);
         }
         if (event_handles[CHILD_HANDLE]) {
             rv = WaitForSingleObject(event_handles[CHILD_HANDLE], timeout);
             if (rv == WAIT_OBJECT_0) {
                 ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                              "Parent: Child process exited successfully.");
                 CloseHandle(event_handles[CHILD_HANDLE]);
                 event_handles[CHILD_HANDLE] = NULL;
             }
             else {
                 ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                             "Parent: Forcing termination of child process %pp",
-                             event_handles[CHILD_HANDLE]);
+                             "Parent: Forcing termination of child process %d ", event_handles[CHILD_HANDLE]);
                 TerminateProcess(event_handles[CHILD_HANDLE], 1);
                 CloseHandle(event_handles[CHILD_HANDLE]);
                 event_handles[CHILD_HANDLE] = NULL;
             }
         }
         CloseHandle(child_exit_event);
