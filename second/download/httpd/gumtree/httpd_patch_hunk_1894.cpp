 }
 
 static int make_child(server_rec *s, int slot)
 {
     int pid;
 
-    if (slot + 1 > ap_max_daemons_limit) {
-        ap_max_daemons_limit = slot + 1;
+    if (slot + 1 > max_daemons_limit) {
+        max_daemons_limit = slot + 1;
     }
 
     if (one_process) {
         set_signals();
         ap_scoreboard_image->parent[slot].pid = getpid();
         child_main(slot);
     }
 
     if ((pid = fork()) == -1) {
         ap_log_error(APLOG_MARK, APLOG_ERR, errno, s,
                      "fork: Unable to fork new process");
-
-        /* fork didn't succeed. Fix the scoreboard or else
-         * it will say SERVER_STARTING forever and ever
+        /* fork didn't succeed.  There's no need to touch the scoreboard;
+         * if we were trying to replace a failed child process, then
+         * server_main_loop() marked its workers SERVER_DEAD, and if
+         * we were trying to replace a child process that exited normally,
+         * its worker_thread()s left SERVER_DEAD or SERVER_GRACEFUL behind.
          */
-        ap_update_child_status_from_indexes(slot, 0, SERVER_DEAD, NULL);
 
         /* In case system resources are maxxed out, we don't want
            Apache running away with the CPU trying to fork over and
            over and over again. */
         apr_sleep(apr_time_from_sec(10));
 
