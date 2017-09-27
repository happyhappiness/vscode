     }
     if ((rv = ap_duplicate_listeners(pconf, ap_server_conf,
                                      &listen_buckets, &num_buckets))) {
         ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                      (startup ? NULL : s),
                      "could not duplicate listeners");
-        return DONE;
+        return !OK;
     }
 
     all_buckets = apr_pcalloc(pconf, num_buckets * sizeof(*all_buckets));
     for (i = 0; i < num_buckets; i++) {
         if (!one_process && /* no POD in one_process mode */
                 (rv = ap_mpm_podx_open(pconf, &all_buckets[i].pod))) {
             ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                          (startup ? NULL : s),
                          "could not open pipe-of-death");
-            return DONE;
+            return !OK;
         }
         /* Initialize cross-process accept lock (safe accept needed only) */
         if ((rv = SAFE_ACCEPT((apr_snprintf(id, sizeof id, "%i", i),
                                ap_proc_mutex_create(&all_buckets[i].mutex,
                                                     NULL, AP_ACCEPT_MUTEX_TYPE,
                                                     id, s, pconf, 0))))) {
             ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                          (startup ? NULL : s),
                          "could not create accept mutex");
-            return DONE;
+            return !OK;
         }
         all_buckets[i].listeners = listen_buckets[i];
     }
 
     if (retained->max_buckets < num_buckets) {
         int new_max, *new_ptr;
