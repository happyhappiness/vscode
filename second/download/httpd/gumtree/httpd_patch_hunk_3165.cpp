          * We are using a name based configuration here, but no hostname was
          * provided via SNI. Don't allow that if are requested to do strict
          * checking. Check wether this strict checking was setup either in the
          * server config we used for handshaking or in our current server.
          * This should avoid insecure configuration by accident.
          */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02033)
                      "No hostname was provided via SNI for a name based"
                      " virtual host");
         return HTTP_FORBIDDEN;
     }
 #endif
     SSL_set_app_data2(ssl, r);
 
     /*
      * Log information about incoming HTTPS requests
      */
     if (APLOGrinfo(r) && ap_is_initial_req(r)) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02034)
                      "%s HTTPS request received for child %ld (server %s)",
                      (r->connection->keepalives <= 0 ?
                      "Initial (No.1)" :
                      apr_psprintf(r->pool, "Subsequent (No.%d)",
                                   r->connection->keepalives+1)),
                      r->connection->id,
