 static int cgid_start(apr_pool_t *p, server_rec *main_server,
                       apr_proc_t *procnew)
 {
 
     daemon_should_exit = 0; /* clear setting from previous generation */
     if ((daemon_pid = fork()) < 0) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
+        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, APLOGNO(01253)
                      "mod_cgid: Couldn't spawn cgid daemon process");
         return DECLINED;
     }
     else if (daemon_pid == 0) {
         if (pcgi == NULL) {
             apr_pool_create(&pcgi, p);
