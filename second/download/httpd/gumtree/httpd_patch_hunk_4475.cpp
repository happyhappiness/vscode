             return;
         }
     }
 
     retained->max_daemons_limit = last_non_dead + 1;
 
-    if (idle_thread_count > max_spare_threads / num_buckets) {
-        /* Kill off one child */
-        ap_mpm_podx_signal(all_buckets[child_bucket].pod,
-                           AP_MPM_PODX_GRACEFUL);
-        retained->idle_spawn_rate[child_bucket] = 1;
+    if (idle_thread_count > max_spare_threads / num_buckets)
+    {
+        /*
+         * Child processes that we ask to shut down won't die immediately
+         * but may stay around for a long time when they finish their
+         * requests. If the server load changes many times, many such
+         * gracefully finishing processes may accumulate, filling up the
+         * scoreboard. To avoid running out of scoreboard entries, we
+         * don't shut down more processes when the total number of processes
+         * is high.
+         *
+         * XXX It would be nice if we could
+         * XXX - kill processes without keepalive connections first
+         * XXX - tell children to stop accepting new connections, and
+         * XXX   depending on server load, later be able to resurrect them
+         *       or kill them
+         */
+        if (retained->total_daemons <= active_daemons_limit &&
+            retained->total_daemons < server_limit) {
+            /* Kill off one child */
+            ap_mpm_podx_signal(all_buckets[child_bucket].pod,
+                               AP_MPM_PODX_GRACEFUL);
+            retained->idle_spawn_rate[child_bucket] = 1;
+            active_daemons--;
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_TRACE5, 0, ap_server_conf,
+                         "Not shutting down child: total daemons %d / "
+                         "active limit %d / ServerLimit %d",
+                         retained->total_daemons, active_daemons_limit,
+                         server_limit);
+        }
     }
     else if (idle_thread_count < min_spare_threads / num_buckets) {
-        /* terminate the free list */
-        if (free_length == 0) { /* scoreboard is full, can't fork */
-
-            if (active_thread_count >= ap_daemons_limit * threads_per_child) {
-                if (!retained->maxclients_reported) {
-                    /* only report this condition once */
-                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00484)
-                                 "server reached MaxRequestWorkers setting, "
-                                 "consider raising the MaxRequestWorkers "
-                                 "setting");
-                    retained->maxclients_reported = 1;
-                }
-            }
-            else {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00485)
-                             "scoreboard is full, not at MaxRequestWorkers");
+        if (active_thread_count >= max_workers) {
+            if (!retained->maxclients_reported) {
+                /* only report this condition once */
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00484)
+                             "server reached MaxRequestWorkers setting, "
+                             "consider raising the MaxRequestWorkers "
+                             "setting");
+                retained->maxclients_reported = 1;
             }
             retained->idle_spawn_rate[child_bucket] = 1;
         }
+        else if (free_length == 0) { /* scoreboard is full, can't fork */
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO()
+                         "scoreboard is full, not at MaxRequestWorkers."
+                         "Increase ServerLimit.");
+            retained->idle_spawn_rate[child_bucket] = 1;
+        }
         else {
             if (free_length > retained->idle_spawn_rate[child_bucket]) {
                 free_length = retained->idle_spawn_rate[child_bucket];
             }
             if (retained->idle_spawn_rate[child_bucket] >= 8) {
                 ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00486)
                              "server seems busy, (you may need "
                              "to increase StartServers, ThreadsPerChild "
                              "or Min/MaxSpareThreads), "
                              "spawning %d children, there are around %d idle "
-                             "threads, and %d total children", free_length,
-                             idle_thread_count, total_non_dead);
+                             "threads, %d active children, and %d children "
+                             "that are shutting down", free_length,
+                             idle_thread_count, active_daemons,
+                             retained->total_daemons);
             }
             for (i = 0; i < free_length; ++i) {
+                ap_log_error(APLOG_MARK, APLOG_TRACE5, 0, ap_server_conf,
+                             "Spawning new child: slot %d active / "
+                             "total daemons: %d/%d",
+                             free_slots[i], active_daemons,
+                             retained->total_daemons);
                 make_child(ap_server_conf, free_slots[i], child_bucket);
             }
             /* the next time around we want to spawn twice as many if this
              * wasn't good enough, but not if we've just done a graceful
              */
             if (retained->hold_off_on_exponential_spawning) {
