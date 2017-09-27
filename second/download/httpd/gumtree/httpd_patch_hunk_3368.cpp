 
     (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);
 
     /* Set up the pollfd array */
     status = apr_pollset_create(&pollset, num_listensocks, pchild, 0);
     if (status != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf, APLOGNO(00156)
                      "Couldn't create pollset in child; check system or user limits");
         clean_child_exit(APEXIT_CHILDSICK); /* assume temporary resource issue */
     }
 
     for (lr = ap_listeners, i = num_listensocks; i--; lr = lr->next) {
         apr_pollfd_t pfd = { 0 };
