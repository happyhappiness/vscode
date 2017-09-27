                  ap_get_server_description());
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00490)
                  "Server built: %s", ap_get_server_built());
     ap_log_command_line(plog, s);
     ap_log_mpm_common(s);
 
-    mpm_state = AP_MPMQ_RUNNING;
+    retained->mpm->mpm_state = AP_MPMQ_RUNNING;
 
     server_main_loop(remaining_children_to_start, num_buckets);
-    mpm_state = AP_MPMQ_STOPPING;
+    retained->mpm->mpm_state = AP_MPMQ_STOPPING;
 
-    if (shutdown_pending && !retained->is_graceful) {
+    if (retained->mpm->shutdown_pending && retained->mpm->is_ungraceful) {
         /* Time to shut down:
          * Kill child processes, tell them to call child_exit, etc...
          */
         for (i = 0; i < num_buckets; i++) {
             ap_mpm_podx_killpg(all_buckets[i].pod, active_daemons_limit,
                                AP_MPM_PODX_RESTART);
