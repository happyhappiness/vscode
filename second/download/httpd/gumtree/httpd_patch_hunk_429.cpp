 {
     static int requests_this_child = 0;
     PCOMP_CONTEXT context = NULL;
     ap_sb_handle_t *sbh;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
-                 "Child %d: Worker thread %d starting.", my_pid, thread_num);
+                 "Child %d: Worker thread %ld starting.", my_pid, thread_num);
     while (1) {
         conn_rec *c;
         apr_int32_t disconnected;
 
         ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);
 
