     r->proto_input_filters = c->input_filters;
 
     /* This handler should take care of the entire connection; make it so that
      * nothing else is attempted on the connection after returning. */
     c->keepalive = AP_CONN_CLOSE;
 
-    while (1) { /* Infinite loop until error (one side closes the connection) */
-        if ((rv = apr_pollset_poll(pollset, -1, &pollcnt, &signalled))
-            != APR_SUCCESS) {
+    do { /* Loop until done (one side closes the connection, or an error) */
+        rv = apr_pollset_poll(pollset, -1, &pollcnt, &signalled);
+        if (rv != APR_SUCCESS) {
             if (APR_STATUS_IS_EINTR(rv)) {
                 continue;
             }
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02444) "error apr_poll()");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
