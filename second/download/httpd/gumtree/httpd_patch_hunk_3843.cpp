     }
 
     if (one_process) {
         prefork_note_child_killed(/* slot */ 0, 0, 0);
     }
 
-    ap_mpm_pod_close(pod);
+    ap_mpm_pod_close(my_bucket->pod);
     chdir_for_gprof();
     exit(code);
 }
 
-static void accept_mutex_on(void)
+static apr_status_t accept_mutex_on(void)
 {
-    apr_status_t rv = apr_proc_mutex_lock(accept_mutex);
+    apr_status_t rv = apr_proc_mutex_lock(my_bucket->mutex);
     if (rv != APR_SUCCESS) {
         const char *msg = "couldn't grab the accept mutex";
 
         if (retained->my_generation !=
             ap_scoreboard_image->global->running_generation) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf, APLOGNO(00143) "%s", msg);
