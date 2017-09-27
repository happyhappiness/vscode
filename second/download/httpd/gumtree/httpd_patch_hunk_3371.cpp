          * while we were processing the connection or we are the lucky
          * idle server process that gets to die.
          */
         if (ap_mpm_pod_check(pod) == APR_SUCCESS) { /* selected as idle? */
             die_now = 1;
         }
-        else if (my_generation !=
+        else if (retained->my_generation !=
                  ap_scoreboard_image->global->running_generation) { /* restart? */
             /* yeah, this could be non-graceful restart, in which case the
              * parent will kill us soon enough, but why bother checking?
              */
             die_now = 1;
         }
     }
-    apr_pool_clear(ptrans);
+    apr_pool_clear(ptrans); /* kludge to avoid crash in APR reslist cleanup code */
     clean_child_exit(0);
 }
 
 
 static int make_child(server_rec *s, int slot)
 {
     int pid;
 
-    if (slot + 1 > max_daemons_limit) {
-        max_daemons_limit = slot + 1;
+    if (slot + 1 > retained->max_daemons_limit) {
+        retained->max_daemons_limit = slot + 1;
     }
 
     if (one_process) {
         apr_signal(SIGHUP, sig_term);
         /* Don't catch AP_SIG_GRACEFUL in ONE_PROCESS mode :) */
         apr_signal(SIGINT, sig_term);
 #ifdef SIGQUIT
         apr_signal(SIGQUIT, SIG_DFL);
 #endif
         apr_signal(SIGTERM, sig_term);
+        prefork_note_child_started(slot, getpid());
         child_main(slot);
-        return 0;
+        /* NOTREACHED */
     }
 
     (void) ap_update_child_status_from_indexes(slot, 0, SERVER_STARTING,
                                                (request_rec *) NULL);
 
 
 #ifdef _OSD_POSIX
     /* BS2000 requires a "special" version of fork() before a setuid() call */
     if ((pid = os_fork(ap_unixd_config.user_name)) == -1) {
 #else
     if ((pid = fork()) == -1) {
 #endif
-        ap_log_error(APLOG_MARK, APLOG_ERR, errno, s, "fork: Unable to fork new process");
+        ap_log_error(APLOG_MARK, APLOG_ERR, errno, s, APLOGNO(00159) "fork: Unable to fork new process");
 
         /* fork didn't succeed. Fix the scoreboard or else
          * it will say SERVER_STARTING forever and ever
          */
         (void) ap_update_child_status_from_indexes(slot, 0, SERVER_DEAD,
                                                    (request_rec *) NULL);
