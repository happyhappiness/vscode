         cmd = args[0];
     }
 
     /* Create a pipe to send handles to the child */
     if ((rv = apr_procattr_io_set(attr, APR_FULL_BLOCK,
                                   APR_NO_PIPE, APR_NO_PIPE)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00414)
                         "Parent: Unable to create child stdin pipe.");
         apr_pool_destroy(ptemp);
         return -1;
     }
 
     /* Create the child_ready_event */
     waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
     if (!waitlist[waitlist_ready]) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00415)
                      "Parent: Could not create ready event for child process");
         apr_pool_destroy (ptemp);
         return -1;
     }
 
     /* Create the child_exit_event */
     hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
     if (!hExitEvent) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00416)
                      "Parent: Could not create exit event for child process");
         apr_pool_destroy(ptemp);
         CloseHandle(waitlist[waitlist_ready]);
         return -1;
     }
 
     /* Build the env array */
     for (envc = 0; _environ[envc]; ++envc) {
         ;
     }
-    env = apr_palloc(ptemp, (envc + 2) * sizeof (char*));  
+    env = apr_palloc(ptemp, (envc + 2) * sizeof (char*));
     memcpy(env, _environ, envc * sizeof (char*));
-    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%i", parent_pid);
+    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%lu", parent_pid);
     env[envc] = pidbuf;
     env[envc + 1] = NULL;
 
-    rv = apr_proc_create(&new_child, cmd, args, env, attr, ptemp);
+    rv = apr_proc_create(&new_child, cmd, (const char * const *)args,
+                         (const char * const *)env, attr, ptemp);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00417)
                      "Parent: Failed to create the child process.");
         apr_pool_destroy(ptemp);
         CloseHandle(hExitEvent);
         CloseHandle(waitlist[waitlist_ready]);
         CloseHandle(new_child.hproc);
         return -1;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00418)
                  "Parent: Created child process %d", new_child.pid);
 
     if (send_handles_to_child(ptemp, waitlist[waitlist_ready], hExitEvent,
                               start_mutex, ap_scoreboard_shm,
                               new_child.hproc, new_child.in)) {
         /*
