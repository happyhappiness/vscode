     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00478)
                      "apr_thread_join: unable to join the start " "thread");
     }
 }
 
-static void child_main(int child_num_arg)
+static void child_main(int child_num_arg, int child_bucket)
 {
     apr_thread_t **threads;
     apr_status_t rv;
     thread_starter *ts;
     apr_threadattr_t *thread_attr;
     apr_thread_t *start_thread_id;
+    int i;
 
     mpm_state = AP_MPMQ_STARTING;       /* for benefit of any hooks that run as this
                                          * child initializes
                                          */
     ap_my_pid = getpid();
     ap_fatal_signal_child_setup(ap_server_conf);
     apr_pool_create(&pchild, pconf);
 
+    /* close unused listeners and pods */
+    for (i = 0; i < retained->num_buckets; i++) {
+        if (i != child_bucket) {
+            ap_close_listeners_ex(all_buckets[i].listeners);
+            ap_mpm_podx_close(all_buckets[i].pod);
+        }
+    }
+
     /*stuff to do before we switch id's, so we have permissions. */
     ap_reopen_scoreboard(pchild, NULL, 0);
 
     if (ap_run_drop_privileges(pchild, ap_server_conf)) {
         clean_child_exit(APEXIT_CHILDFATAL);
     }
