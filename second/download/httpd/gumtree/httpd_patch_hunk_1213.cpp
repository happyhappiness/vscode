 
     ap_create_sb_handle(&sbh, pchild, my_child_num, 0);
 
     (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);
 
     /* Set up the pollfd array */
-    /* ### check the status */
-    (void) apr_pollset_create(&pollset, num_listensocks, pchild, 0);
+    status = apr_pollset_create(&pollset, num_listensocks, pchild, 0);
+    if (status != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
+                     "Couldn't create pollset in child; check system or user limits");
+        clean_child_exit(APEXIT_CHILDSICK); /* assume temporary resource issue */
+    }
 
     for (lr = ap_listeners, i = num_listensocks; i--; lr = lr->next) {
         apr_pollfd_t pfd = { 0 };
 
         pfd.desc_type = APR_POLL_SOCKET;
         pfd.desc.s = lr->sd;
