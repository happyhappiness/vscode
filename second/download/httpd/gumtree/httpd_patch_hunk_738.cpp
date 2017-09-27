 
     SSL_set_shutdown(ssl, shutdown_type);
     SSL_smart_shutdown(ssl);
 
     /* and finally log the fact that we've closed the connection */
     if (c->base_server->loglevel >= APLOG_INFO) {
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
-                     "Connection to child %ld closed with %s shutdown"
-                     "(server %s, client %s)",
-                     c->id, type,
-                     ssl_util_vhostid(c->pool, c->base_server),
-                     c->remote_ip ? c->remote_ip : "unknown");
+        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+                      "Connection closed to child %ld with %s shutdown "
+                      "(server %s)",
+                      c->id, type, ssl_util_vhostid(c->pool, c->base_server));
     }
 
     /* deallocate the SSL connection */
     if (sslconn->client_cert) {
         X509_free(sslconn->client_cert);
         sslconn->client_cert = NULL;
