         int active_children;
         int index;
         apr_time_t cutoff = 0;
 
         /* Close our listeners, and then ask our children to do same */
         ap_close_listeners();
-        ap_mpm_podx_killpg(pod, ap_daemons_limit, AP_MPM_PODX_GRACEFUL);
+        for (i = 0; i < num_buckets; i++) {
+            ap_mpm_podx_killpg(all_buckets[i].pod, ap_daemons_limit,
+                               AP_MPM_PODX_GRACEFUL);
+        }
         ap_relieve_child_processes(event_note_child_killed);
 
         if (!child_fatal) {
             /* cleanup pid file on normal shutdown */
             ap_remove_pid(pconf, ap_pid_fname);
             ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00492)
