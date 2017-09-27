     }
 
     /* advance to the next generation */
     /* XXX: we really need to make sure this new generation number isn't in
      * use by any of the children.
      */
-    ++my_generation;
-    ap_scoreboard_image->global->running_generation = my_generation;
+    ++retained->my_generation;
+    ap_scoreboard_image->global->running_generation = retained->my_generation;
 
-    if (is_graceful) {
-        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+    if (retained->is_graceful) {
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00171)
                     "Graceful restart requested, doing restart");
 
         /* kill off the idle ones */
-        ap_mpm_pod_killpg(pod, max_daemons_limit);
+        ap_mpm_pod_killpg(pod, retained->max_daemons_limit);
 
         /* This is mostly for debugging... so that we know what is still
          * gracefully dealing with existing request.  This will break
          * in a very nasty way if we ever have the scoreboard totally
          * file-based (no shared memory)
          */
