     PID owner;
 
     rc = DosOpenQueue(&owner, &workq,
                       apr_psprintf(pchild, "/queues/httpd/work.%d", getpid()));
 
     if (rc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00197)
                      "unable to open work queue in maintenance thread");
         return;
     }
 
     do {
         for (num_idle=0, threadnum=0; threadnum < HARD_THREAD_LIMIT; threadnum++) {
