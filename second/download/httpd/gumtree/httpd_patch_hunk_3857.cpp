             }
             else {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                              ap_server_conf, APLOGNO(00288)
                              "scoreboard is full, not at MaxRequestWorkers");
             }
-            retained->idle_spawn_rate = 1;
+            retained->idle_spawn_rate[child_bucket] = 1;
         }
         else {
-            if (free_length > retained->idle_spawn_rate) {
-                free_length = retained->idle_spawn_rate;
+            if (free_length > retained->idle_spawn_rate[child_bucket]) {
+                free_length = retained->idle_spawn_rate[child_bucket];
             }
-            if (retained->idle_spawn_rate >= 8) {
+            if (retained->idle_spawn_rate[child_bucket] >= 8) {
                 ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                              ap_server_conf, APLOGNO(00289)
                              "server seems busy, (you may need "
                              "to increase StartServers, ThreadsPerChild "
                              "or Min/MaxSpareThreads), "
                              "spawning %d children, there are around %d idle "
                              "threads, and %d total children", free_length,
                              idle_thread_count, total_non_dead);
             }
             for (i = 0; i < free_length; ++i) {
-                make_child(ap_server_conf, free_slots[i]);
+                make_child(ap_server_conf, free_slots[i], child_bucket);
             }
             /* the next time around we want to spawn twice as many if this
              * wasn't good enough, but not if we've just done a graceful
              */
             if (retained->hold_off_on_exponential_spawning) {
                 --retained->hold_off_on_exponential_spawning;
             }
-            else if (retained->idle_spawn_rate < MAX_SPAWN_RATE) {
-                retained->idle_spawn_rate *= 2;
+            else if (retained->idle_spawn_rate[child_bucket]
+                     < MAX_SPAWN_RATE / num_buckets) {
+                retained->idle_spawn_rate[child_bucket] *= 2;
             }
         }
     }
     else {
-      retained->idle_spawn_rate = 1;
+        retained->idle_spawn_rate[child_bucket] = 1;
     }
 }
 
-static void server_main_loop(int remaining_children_to_start)
+static void server_main_loop(int remaining_children_to_start, int num_buckets)
 {
     ap_generation_t old_gen;
     int child_slot;
     apr_exit_why_e exitwhy;
     int status, processed_status;
     apr_proc_t pid;
