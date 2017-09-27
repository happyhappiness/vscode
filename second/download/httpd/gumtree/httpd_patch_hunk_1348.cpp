 die_now:
     if (shutdown_pending)
     {
         int timeout = 30000;  /* Timeout is milliseconds */
         winnt_mpm_state = AP_MPMQ_STOPPING;
 
+        if (!child_created) {
+            return 0;  /* Tell the caller we do not want to restart */
+        }
+
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
-                             "Parent: SetEvent for child process %d failed", event_handles[CHILD_HANDLE]);
+                             "Parent: SetEvent for child process %pp failed",
+                             event_handles[CHILD_HANDLE]);
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
-                             "Parent: Forcing termination of child process %d ", event_handles[CHILD_HANDLE]);
+                             "Parent: Forcing termination of child process %pp",
+                             event_handles[CHILD_HANDLE]);
                 TerminateProcess(event_handles[CHILD_HANDLE], 1);
                 CloseHandle(event_handles[CHILD_HANDLE]);
                 event_handles[CHILD_HANDLE] = NULL;
             }
         }
         CloseHandle(child_exit_event);
