     /* Build the env array */
     for (envc = 0; _environ[envc]; ++envc) {
         ;
     }
     env = apr_palloc(ptemp, (envc + 2) * sizeof (char*));  
     memcpy(env, _environ, envc * sizeof (char*));
-    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%lu", parent_pid);
+    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%i", parent_pid);
     env[envc] = pidbuf;
     env[envc + 1] = NULL;
 
-    rv = apr_proc_create(&new_child, cmd, (const char * const *)args, 
-                         (const char * const *)env, attr, ptemp);
+    rv = apr_proc_create(&new_child, cmd, args, env, attr, ptemp);
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                      "Parent: Failed to create the child process.");
         apr_pool_destroy(ptemp);
         CloseHandle(hExitEvent);
         CloseHandle(waitlist[waitlist_ready]);
         CloseHandle(new_child.hproc);
         return -1;
     }
-    apr_file_close(child_out);
+
     ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                  "Parent: Created child process %d", new_child.pid);
 
     if (send_handles_to_child(ptemp, waitlist[waitlist_ready], hExitEvent,
                               start_mutex, ap_scoreboard_shm,
                               new_child.hproc, new_child.in)) {
