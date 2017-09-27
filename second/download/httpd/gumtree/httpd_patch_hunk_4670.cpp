     char id[16];
     int i;
 
     pconf = p;
 
     /* the reverse of pre_config, we want this only the first time around */
-    if (retained->module_loads == 1) {
+    if (retained->mpm->module_loads == 1) {
         startup = 1;
         level_flags |= APLOG_STARTUP;
     }
 
     if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
         ap_log_error(APLOG_MARK, APLOG_ALERT | level_flags, 0,
                      (startup ? NULL : s),
                      "no listening sockets available, shutting down");
         return !OK;
     }
 
     if (one_process) {
-        num_buckets = 1;
+        retained->mpm->num_buckets = 1;
     }
-    else if (!retained->is_graceful) { /* Preserve the number of buckets
-                                          on graceful restarts. */
-        num_buckets = 0;
+    else if (!retained->mpm->was_graceful) {
+        /* Preserve the number of buckets on graceful restarts. */
+        retained->mpm->num_buckets = 0;
     }
     if ((rv = ap_duplicate_listeners(pconf, ap_server_conf,
-                                     &listen_buckets, &num_buckets))) {
+                                     &listen_buckets, &retained->mpm->num_buckets))) {
         ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                      (startup ? NULL : s),
                      "could not duplicate listeners");
         return !OK;
     }
-    all_buckets = apr_pcalloc(pconf, num_buckets *
+    all_buckets = apr_pcalloc(pconf, retained->mpm->num_buckets *
                                      sizeof(prefork_child_bucket));
-    for (i = 0; i < num_buckets; i++) {
+    for (i = 0; i < retained->mpm->num_buckets; i++) {
         if ((rv = ap_mpm_pod_open(pconf, &all_buckets[i].pod))) {
             ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                          (startup ? NULL : s),
                          "could not open pipe-of-death");
             return !OK;
         }
