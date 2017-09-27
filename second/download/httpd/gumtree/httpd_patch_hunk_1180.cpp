     switch (status) {
       case HTTP_BAD_REQUEST:
             /* log the situation */
             ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                          "SSL handshake failed: HTTP spoken on HTTPS port; "
                          "trying to send HTML error page");
-            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, f->c->base_server);
+            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, sslconn->server);
 
             sslconn->non_ssl_request = 1;
             ssl_io_filter_disable(sslconn, f);
 
             /* fake the request line */
             bucket = HTTP_ON_HTTPS_PORT_BUCKET(f->c->bucket_alloc);
