                 /* slot is still in use - back of the bus
                  */
                 free_slots[free_length] = i;
             }
             ++free_length;
         }
-        else if (child_threads_active == ap_threads_per_child) {
-            had_healthy_child = 1;
-        }
         /* XXX if (!ps->quiescing)     is probably more reliable  GLA */
         if (!any_dying_threads) {
             last_non_dead = i;
             ++total_non_dead;
         }
     }
 
     if (sick_child_detected) {
-        if (had_healthy_child) {
-            /* Assume this is a transient error, even though it may not be.  Leave
-             * the server up in case it is able to serve some requests or the
-             * problem will be resolved.
+        if (active_thread_count > 0) {
+            /* some child processes appear to be working.  don't kill the
+             * whole server.
              */
             sick_child_detected = 0;
         }
         else {
-            /* looks like a basket case, as no child ever fully initialized; give up.
+            /* looks like a basket case.  give up.
              */
             shutdown_pending = 1;
             child_fatal = 1;
             ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                          ap_server_conf,
-                         "A resource shortage or other unrecoverable failure "
-                         "was encountered before any child process initialized "
-                         "successfully... httpd is exiting!");
+                         "No active workers found..."
+                         " Apache is exiting!");
             /* the child already logged the failure details */
             return;
         }
     }
 
-    ap_max_daemons_limit = last_non_dead + 1;
+    max_daemons_limit = last_non_dead + 1;
 
     if (idle_thread_count > max_spare_threads) {
         /* Kill off one child */
-        ap_mpm_pod_signal(pod, TRUE);
+        ap_worker_pod_signal(pod, TRUE);
         idle_spawn_rate = 1;
     }
     else if (idle_thread_count < min_spare_threads) {
         /* terminate the free list */
-        if (free_length == 0) {
-            /* No room for more children, might warn about configuration */
-            if (active_thread_count >= ap_daemons_limit * ap_threads_per_child) {
-                /* no threads are "inactive" - starting, stopping, etc. - which would confuse matters */
-                /* Are all threads in use?  Then we're really at MaxClients */
+        if (free_length == 0) { /* scoreboard is full, can't fork */
+
+            if (active_thread_count >= ap_daemons_limit * threads_per_child) { 
+                /* no threads are "inactive" - starting, stopping, etc. */
+                /* have we reached MaxClients, or just getting close? */
                 if (0 == idle_thread_count) {
-                    /* only report this condition once */
                     static int reported = 0;
-
                     if (!reported) {
+                        /* only report this condition once */
                         ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                      ap_server_conf,
                                      "server reached MaxClients setting, consider"
                                      " raising the MaxClients setting");
                         reported = 1;
                     }
