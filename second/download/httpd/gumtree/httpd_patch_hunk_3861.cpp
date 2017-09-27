         ap_log_error(APLOG_MARK, APLOG_ALERT | level_flags, 0,
                      (startup ? NULL : s),
                      "no listening sockets available, shutting down");
         return DONE;
     }
 
-    if (!one_process) {
-        if ((rv = ap_mpm_podx_open(pconf, &pod))) {
+    if (one_process) {
+        num_buckets = 1;
+    }
+    else if (retained->is_graceful) {
+        /* Preserve the number of buckets on graceful restarts. */
+        num_buckets = retained->num_buckets;
+    }
+    if ((rv = ap_duplicate_listeners(pconf, ap_server_conf,
+                                     &listen_buckets, &num_buckets))) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
+                     (startup ? NULL : s),
+                     "could not duplicate listeners");
+        return DONE;
+    }
+
+    all_buckets = apr_pcalloc(pconf, num_buckets * sizeof(*all_buckets));
+    for (i = 0; i < num_buckets; i++) {
+        if (!one_process && /* no POD in one_process mode */
+                (rv = ap_mpm_podx_open(pconf, &all_buckets[i].pod))) {
             ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                          (startup ? NULL : s),
                          "could not open pipe-of-death");
             return DONE;
         }
+        /* Initialize cross-process accept lock (safe accept needed only) */
+        if ((rv = SAFE_ACCEPT((apr_snprintf(id, sizeof id, "%i", i),
+                               ap_proc_mutex_create(&all_buckets[i].mutex,
+                                                    NULL, AP_ACCEPT_MUTEX_TYPE,
+                                                    id, s, pconf, 0))))) {
+            ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
+                         (startup ? NULL : s),
+                         "could not create accept mutex");
+            return DONE;
+        }
+        all_buckets[i].listeners = listen_buckets[i];
     }
+
+    if (retained->max_buckets < num_buckets) {
+        int new_max, *new_ptr;
+        new_max = retained->max_buckets * 2;
+        if (new_max < num_buckets) {
+            new_max = num_buckets;
+        }
+        new_ptr = (int *)apr_palloc(ap_pglobal, new_max * sizeof(int));
+        memcpy(new_ptr, retained->idle_spawn_rate,
+               retained->num_buckets * sizeof(int));
+        retained->idle_spawn_rate = new_ptr;
+        retained->max_buckets = new_max;
+    }
+    if (retained->num_buckets < num_buckets) {
+        int rate_max = 1;
+        /* If new buckets are added, set their idle spawn rate to
+         * the highest so far, so that they get filled as quickly
+         * as the existing ones.
+         */
+        for (i = 0; i < retained->num_buckets; i++) {
+            if (rate_max < retained->idle_spawn_rate[i]) {
+                rate_max = retained->idle_spawn_rate[i];
+            }
+        }
+        for (/* up to date i */; i < num_buckets; i++) {
+            retained->idle_spawn_rate[i] = rate_max;
+        }
+    }
+    retained->num_buckets = num_buckets;
+
     return OK;
 }
 
 static int worker_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp)
 {
