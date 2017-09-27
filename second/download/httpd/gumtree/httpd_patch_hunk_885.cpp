 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                  "Child %d: Retrieved our scoreboard from the parent.", my_pid);
 }
 
 
-static int send_handles_to_child(apr_pool_t *p, 
+static int send_handles_to_child(apr_pool_t *p,
                                  HANDLE child_ready_event,
-                                 HANDLE child_exit_event, 
+                                 HANDLE child_exit_event,
                                  apr_proc_mutex_t *child_start_mutex,
                                  apr_shm_t *scoreboard_shm,
-                                 HANDLE hProcess, 
+                                 HANDLE hProcess,
                                  apr_file_t *child_in)
 {
     apr_status_t rv;
     HANDLE hCurrentProcess = GetCurrentProcess();
     HANDLE hDup;
     HANDLE os_start;
     HANDLE hScore;
-    DWORD BytesWritten;
+    apr_size_t BytesWritten;
 
     if (!DuplicateHandle(hCurrentProcess, child_ready_event, hProcess, &hDup,
         EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                      "Parent: Unable to duplicate the ready event handle for the child");
         return -1;
