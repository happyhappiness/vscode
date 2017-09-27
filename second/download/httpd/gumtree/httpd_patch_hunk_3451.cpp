         if (!any_dying_threads) {
             last_non_dead = i;
             ++total_non_dead;
         }
     }
 
-    if (sick_child_detected) {
+    if (retained->sick_child_detected) {
         if (active_thread_count > 0) {
             /* some child processes appear to be working.  don't kill the
              * whole server.
              */
-            sick_child_detected = 0;
+            retained->sick_child_detected = 0;
         }
         else {
             /* looks like a basket case.  give up.
              */
             shutdown_pending = 1;
             child_fatal = 1;
             ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
-                         ap_server_conf,
+                         ap_server_conf, APLOGNO(00285)
                          "No active workers found..."
                          " Apache is exiting!");
             /* the child already logged the failure details */
             return;
         }
     }
 
-    max_daemons_limit = last_non_dead + 1;
+    retained->max_daemons_limit = last_non_dead + 1;
 
     if (idle_thread_count > max_spare_threads) {
         /* Kill off one child */
         ap_worker_pod_signal(pod, TRUE);
-        idle_spawn_rate = 1;
+        retained->idle_spawn_rate = 1;
     }
     else if (idle_thread_count < min_spare_threads) {
         /* terminate the free list */
         if (free_length == 0) { /* scoreboard is full, can't fork */
 
-            if (active_thread_count >= ap_daemons_limit * threads_per_child) { 
+            if (active_thread_count >= ap_daemons_limit * threads_per_child) {
                 /* no threads are "inactive" - starting, stopping, etc. */
-                /* have we reached MaxClients, or just getting close? */
+                /* have we reached MaxRequestWorkers, or just getting close? */
                 if (0 == idle_thread_count) {
-                    static int reported = 0;
-                    if (!reported) {
+                    if (!retained->maxclients_reported) {
                         /* only report this condition once */
-                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
-                                     ap_server_conf,
-                                     "server reached MaxClients setting, consider"
-                                     " raising the MaxClients setting");
-                        reported = 1;
+                        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00286)
+                                     "server reached MaxRequestWorkers "
+                                     "setting, consider raising the "
+                                     "MaxRequestWorkers setting");
+                        retained->maxclients_reported = 1;
                     }
                 } else {
-                    static int reported = 0;
-                    if (!reported) {
-                        ap_log_error(APLOG_MARK, APLOG_ERR, 0,
-                                     ap_server_conf,
-                                     "server is within MinSpareThreads of MaxClients, "
-                                     "consider raising the MaxClients setting");
-                        reported = 1;
+                    if (!retained->near_maxclients_reported) {
+                        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00287)
+                                     "server is within MinSpareThreads of "
+                                     "MaxRequestWorkers, consider raising the "
+                                     "MaxRequestWorkers setting");
+                        retained->near_maxclients_reported = 1;
                     }
                 }
             }
             else {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0,
-                             ap_server_conf,
-                             "scoreboard is full, not at MaxClients");
+                             ap_server_conf, APLOGNO(00288)
+                             "scoreboard is full, not at MaxRequestWorkers");
             }
-            idle_spawn_rate = 1;
+            retained->idle_spawn_rate = 1;
         }
         else {
-            if (free_length > idle_spawn_rate) {
-                free_length = idle_spawn_rate;
+            if (free_length > retained->idle_spawn_rate) {
+                free_length = retained->idle_spawn_rate;
             }
-            if (idle_spawn_rate >= 8) {
+            if (retained->idle_spawn_rate >= 8) {
                 ap_log_error(APLOG_MARK, APLOG_INFO, 0,
-                             ap_server_conf,
+                             ap_server_conf, APLOGNO(00289)
                              "server seems busy, (you may need "
                              "to increase StartServers, ThreadsPerChild "
                              "or Min/MaxSpareThreads), "
                              "spawning %d children, there are around %d idle "
                              "threads, and %d total children", free_length,
                              idle_thread_count, total_non_dead);
