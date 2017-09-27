         ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                      "Couldn't listen on unix domain socket");
         return errno;
     }
 
     if (!geteuid()) {
-        if (chown(sockname, unixd_config.user_id, -1) < 0) {
+        if (chown(sockname, ap_unixd_config.user_id, -1) < 0) {
             ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                          "Couldn't change owner of unix domain socket %s",
                          sockname);
             return errno;
         }
     }
 
-    unixd_setup_child(); /* if running as root, switch to configured user/group */
+    apr_pool_cleanup_register(pcgi, (void *)((long)sd),
+                              close_unix_socket, close_unix_socket);
+
+    /* if running as root, switch to configured user/group */
+    if ((rc = ap_run_drop_privileges(pcgi, ap_server_conf)) != 0) {
+        return rc;
+    }
 
     while (!daemon_should_exit) {
         int errfileno = STDERR_FILENO;
-        char *argv0;
-        char **env;
+        char *argv0 = NULL;
+        char **env = NULL;
         const char * const *argv;
         apr_int32_t in_pipe;
         apr_int32_t out_pipe;
         apr_int32_t err_pipe;
         apr_cmdtype_e cmd_type;
         request_rec *r;
         apr_procattr_t *procattr = NULL;
         apr_proc_t *procnew = NULL;
         apr_file_t *inout;
         cgid_req_t cgid_req;
         apr_status_t stat;
+        void *key;
+        apr_socklen_t len;
+        struct sockaddr_un unix_addr;
 
         apr_pool_clear(ptrans);
 
         len = sizeof(unix_addr);
         sd2 = accept(sd, (struct sockaddr *)&unix_addr, &len);
         if (sd2 < 0) {
