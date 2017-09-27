 
     if (servername) {
         conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
         if (c) {
             if (ap_vhost_iterate_given_conn(c, ssl_find_vhost,
                                             (void *)servername)) {
-                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02043)
                               "SSL virtual host for servername %s found",
                               servername);
                 return SSL_TLSEXT_ERR_OK;
             }
             else {
-                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02044)
                               "No matching SSL virtual host for servername "
                               "%s found (using default/first virtual host)",
                               servername);
                 return SSL_TLSEXT_ERR_ALERT_WARNING;
             }
         }
