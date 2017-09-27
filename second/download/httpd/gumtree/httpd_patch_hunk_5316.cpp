     }
     child_events[0] = exit_event;
     child_events[1] = max_requests_per_child_event;
 
     if (parent_pid != my_pid) {
         child_events[2] = OpenProcess(SYNCHRONIZE, FALSE, parent_pid);
-        num_events = 3;
+        if (child_events[2] == NULL) {
+            num_events = 2;
+            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(02643)
+                         "Child: Failed to open handle to parent process %ld; "
+                         "will not react to abrupt parent termination", parent_pid);
+        }
+        else {
+            num_events = 3;
+        }
     }
     else {
         /* presumably -DONE_PROCESS */
         child_events[2] = NULL;
         num_events = 2;
     }
