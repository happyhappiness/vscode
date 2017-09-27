                   &err, &bad_request, &has_responded);
     if (rv != APR_SUCCESS) {
         /* If the client aborted the connection during retrieval or (partially)
          * sending the response, don't return a HTTP_SERVICE_UNAVAILABLE, since
          * this is not a backend problem. */
         if (r->connection->aborted) {
-            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, rv, r, 
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, rv, r,
                           "The client aborted the connection.");
             conn->close = 1;
             return OK;
         }
 
         ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01075)
