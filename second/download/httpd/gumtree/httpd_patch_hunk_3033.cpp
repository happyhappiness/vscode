                                     r->connection->sbh, c->bucket_alloc);
     if (!data) {
         /*
          * the peer reset the connection already; ap_run_create_connection() closed
          * the socket
          */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-          "proxy: FTP: an error occurred creating the transfer connection");
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01054)
+                      "an error occurred creating the transfer connection");
         proxy_ftp_cleanup(r, backend);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     /*
      * We do not do SSL over the data connection, even if the virtual host we
      * are in might have SSL enabled
      */
     ap_proxy_ssl_disable(data);
     /* set up the connection filters */
     rc = ap_run_pre_connection(data, data_sock);
     if (rc != OK && rc != DONE) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "proxy: FTP: pre_connection setup failed (%d)",
-                     rc);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01055)
+                      "pre_connection setup failed (%d)", rc);
         data->aborted = 1;
         proxy_ftp_cleanup(r, backend);
         return rc;
     }
 
     /*
