     if (retained->is_graceful) {
         ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00493)
                      AP_SIG_GRACEFUL_STRING
                      " received.  Doing graceful restart");
         /* wake up the children...time to die.  But we'll have more soon */
         for (i = 0; i < num_buckets; i++) {
-            ap_mpm_podx_killpg(all_buckets[i].pod, ap_daemons_limit,
+            ap_mpm_podx_killpg(all_buckets[i].pod, active_daemons_limit,
                                AP_MPM_PODX_GRACEFUL);
         }
 
         /* This is mostly for debugging... so that we know what is still
          * gracefully dealing with existing request.
          */
