     else {
         /* Parent process */
         char restart;
         is_parent_process = TRUE;
 
         if (ap_setup_listeners(ap_server_conf) < 1) {
-            ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s, APLOGNO(00200)
                          "no listening sockets available, shutting down");
             return 1;
         }
 
         ap_log_pid(pconf, ap_pid_fname);
 
         restart = master_main();
         ++ap_my_generation;
         ap_scoreboard_image->global->running_generation = ap_my_generation;
 
         if (!restart) {
-            const char *pidfile = ap_server_root_relative(pconf, ap_pid_fname);
-
-            if (pidfile != NULL && remove(pidfile) == 0) {
-                ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
-                             ap_server_conf, "removed PID file %s (pid=%d)",
-                             pidfile, getpid());
-            }
-
-            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+            ap_remove_pid(pconf, ap_pid_fname);
+            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00201)
                          "caught SIGTERM, shutting down");
             return 1;
         }
     }  /* Parent process */
 
     return 0; /* Restart */
