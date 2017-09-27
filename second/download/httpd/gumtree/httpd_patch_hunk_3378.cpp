         apr_time_t cutoff = 0;
 
         /* Stop listening */
         ap_close_listeners();
 
         /* kill off the idle ones */
-        ap_mpm_pod_killpg(pod, max_daemons_limit);
+        ap_mpm_pod_killpg(pod, retained->max_daemons_limit);
 
         /* Send SIGUSR1 to the active children */
         active_children = 0;
         for (index = 0; index < ap_daemons_limit; ++index) {
             if (ap_scoreboard_image->servers[index][0].status != SERVER_DEAD) {
                 /* Ask each child to close its listeners. */
                 ap_mpm_safe_kill(MPM_CHILD_PID(index), AP_SIG_GRACEFUL);
                 active_children++;
             }
         }
 
         /* Allow each child which actually finished to exit */
-        ap_relieve_child_processes();
+        ap_relieve_child_processes(prefork_note_child_killed);
 
         /* cleanup pid file */
-        {
-            const char *pidfile = NULL;
-            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
-            if ( pidfile != NULL && unlink(pidfile) == 0)
-                ap_log_error(APLOG_MARK, APLOG_INFO,
-                                0, ap_server_conf,
-                                "removed PID file %s (pid=%ld)",
-                                pidfile, (long)getpid());
-        }
-
-        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+        ap_remove_pid(pconf, ap_pid_fname);
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00170)
            "caught " AP_SIG_GRACEFUL_STOP_STRING ", shutting down gracefully");
 
         if (ap_graceful_shutdown_timeout) {
             cutoff = apr_time_now() +
                      apr_time_from_sec(ap_graceful_shutdown_timeout);
         }
