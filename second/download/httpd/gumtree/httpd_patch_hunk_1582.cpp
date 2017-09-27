             close(sd2);
             continue;
         }
 
         if (cgid_req.req_type == GETPID_REQ) {
             pid_t pid;
+            apr_status_t rv;
 
             pid = (pid_t)((long)apr_hash_get(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id)));
-            if (write(sd2, &pid, sizeof(pid)) != sizeof(pid)) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
+            rv = sock_write(sd2, &pid, sizeof(pid));
+            if (rv != APR_SUCCESS) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                              main_server,
                              "Error writing pid %" APR_PID_T_FMT " to handler", pid);
             }
             close(sd2);
             continue;
         }
