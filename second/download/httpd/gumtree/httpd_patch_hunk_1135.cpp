      * delayed interlinking from SSL back to request_rec
      */
     ssl = sslconn->ssl;
     if (!ssl) {
         return DECLINED;
     }
+#ifndef OPENSSL_NO_TLSEXT
+    if ((servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))) {
+        char *host, *scope_id;
+        apr_port_t port;
+        apr_status_t rv;
+
+        /*
+         * The SNI extension supplied a hostname. So don't accept requests
+         * with either no hostname or a different hostname.
+         */
+        if (!r->hostname) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                        "Hostname %s provided via SNI, but no hostname"
+                        " provided in HTTP request", servername);
+            return HTTP_BAD_REQUEST;
+        }
+        rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
+        if (rv != APR_SUCCESS || scope_id) {
+            return HTTP_BAD_REQUEST;
+        }
+        if (strcmp(host, servername)) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                        "Hostname %s provided via SNI and hostname %s provided"
+                        " via HTTP are different", servername, host);
+            return HTTP_BAD_REQUEST;
+        }
+    }
+    else if ((((mySrvConfig(r->server))->strict_sni_vhost_check
+              == SSL_ENABLED_TRUE)
+             || (mySrvConfig(sslconn->server))->strict_sni_vhost_check
+                == SSL_ENABLED_TRUE)
+             && r->connection->vhost_lookup_data) {
+        /*
+         * We are using a name based configuration here, but no hostname was
+         * provided via SNI. Don't allow that if are requested to do strict
+         * checking. Check wether this strict checking was setup either in the
+         * server config we used for handshaking or in our current server.
+         * This should avoid insecure configuration by accident.
+         */
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                     "No hostname was provided via SNI for a name based"
+                     " virtual host");
+        return HTTP_FORBIDDEN;
+    }
+#endif
     SSL_set_app_data2(ssl, r);
 
     /*
      * Log information about incoming HTTPS requests
      */
     if (r->server->loglevel >= APLOG_INFO && ap_is_initial_req(r)) {
