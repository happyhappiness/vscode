         if (!strcasecmp(signal_arg, "runservice")) {
             mpm_service_stopping();
         }
         /* Signal the child processes to exit */
         if (SetEvent(child_exit_event) == 0) {
                 ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(00429)
-                             "Parent: SetEvent for child process %pp failed",
+                             "Parent: SetEvent for child process event %pp failed",
                              event_handles[CHILD_HANDLE]);
         }
         if (event_handles[CHILD_HANDLE]) {
             rv = WaitForSingleObject(event_handles[CHILD_HANDLE], timeout);
             if (rv == WAIT_OBJECT_0) {
                 ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00430)
-                             "Parent: Child process exited successfully.");
+                             "Parent: Child process %lu exited successfully.", child_pid);
                 CloseHandle(event_handles[CHILD_HANDLE]);
                 event_handles[CHILD_HANDLE] = NULL;
             }
             else {
                 ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00431)
-                             "Parent: Forcing termination of child process %pp",
-                             event_handles[CHILD_HANDLE]);
+                             "Parent: Forcing termination of child process %lu",
+                             child_pid);
                 TerminateProcess(event_handles[CHILD_HANDLE], 1);
                 CloseHandle(event_handles[CHILD_HANDLE]);
                 event_handles[CHILD_HANDLE] = NULL;
             }
         }
         CloseHandle(child_exit_event);
