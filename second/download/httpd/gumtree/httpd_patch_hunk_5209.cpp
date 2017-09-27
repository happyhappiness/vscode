      */
     ssl = sslconn->ssl;
     if (!ssl) {
         return DECLINED;
     }
 #ifdef HAVE_TLSEXT
-    if ((servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))) {
-        char *host, *scope_id;
-        apr_port_t port;
-        apr_status_t rv;
+    if (r->proxyreq != PROXYREQ_PROXY) {
+        if ((servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))) {
+            char *host, *scope_id;
+            apr_port_t port;
+            apr_status_t rv;
 
-        /*
-         * The SNI extension supplied a hostname. So don't accept requests
-         * with either no hostname or a different hostname.
-         */
-        if (!r->hostname) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02031)
-                        "Hostname %s provided via SNI, but no hostname"
-                        " provided in HTTP request", servername);
-            return HTTP_BAD_REQUEST;
+            /*
+             * The SNI extension supplied a hostname. So don't accept requests
+             * with either no hostname or a different hostname as this could
+             * cause us to end up in a different virtual host as the one that
+             * was used for the handshake causing different SSL parameters to
+             * be applied as SSLProtocol, SSLCACertificateFile/Path and
+             * SSLCADNRequestFile/Path cannot be renegotioated (SSLCA* due
+             * to current limitiations in Openssl, see
+             * http://mail-archives.apache.org/mod_mbox/httpd-dev/200806.mbox/%3C48592955.2090303@velox.ch%3E
+             * and
+             * http://mail-archives.apache.org/mod_mbox/httpd-dev/201312.mbox/%3CCAKQ1sVNpOrdiBm-UPw1hEdSN7YQXRRjeaT-MCWbW_7mN%3DuFiOw%40mail.gmail.com%3E
+             * )
+             */
+            if (!r->hostname) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02031)
+                            "Hostname %s provided via SNI, but no hostname"
+                            " provided in HTTP request", servername);
+                return HTTP_BAD_REQUEST;
+            }
+            rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
+            if (rv != APR_SUCCESS || scope_id) {
+                return HTTP_BAD_REQUEST;
+            }
+            if (strcasecmp(host, servername)) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
+                            "Hostname %s provided via SNI and hostname %s provided"
+                            " via HTTP are different", servername, host);
+                return HTTP_BAD_REQUEST;
+            }
         }
-        rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
-        if (rv != APR_SUCCESS || scope_id) {
-            return HTTP_BAD_REQUEST;
+        else if (((sc->strict_sni_vhost_check == SSL_ENABLED_TRUE)
+                 || (mySrvConfig(sslconn->server))->strict_sni_vhost_check
+                    == SSL_ENABLED_TRUE)
+                 && r->connection->vhost_lookup_data) {
+            /*
+             * We are using a name based configuration here, but no hostname was
+             * provided via SNI. Don't allow that if are requested to do strict
+             * checking. Check wether this strict checking was setup either in the
+             * server config we used for handshaking or in our current server.
+             * This should avoid insecure configuration by accident.
+             */
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02033)
+                         "No hostname was provided via SNI for a name based"
+                         " virtual host");
+            return HTTP_FORBIDDEN;
         }
-        if (strcasecmp(host, servername)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
-                        "Hostname %s provided via SNI and hostname %s provided"
-                        " via HTTP are different", servername, host);
-            return HTTP_BAD_REQUEST;
-        }
-    }
-    else if (((sc->strict_sni_vhost_check == SSL_ENABLED_TRUE)
-             || (mySrvConfig(sslconn->server))->strict_sni_vhost_check
-                == SSL_ENABLED_TRUE)
-             && r->connection->vhost_lookup_data) {
-        /*
-         * We are using a name based configuration here, but no hostname was
-         * provided via SNI. Don't allow that if are requested to do strict
-         * checking. Check wether this strict checking was setup either in the
-         * server config we used for handshaking or in our current server.
-         * This should avoid insecure configuration by accident.
-         */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02033)
-                     "No hostname was provided via SNI for a name based"
-                     " virtual host");
-        return HTTP_FORBIDDEN;
     }
 #endif
     SSL_set_app_data2(ssl, r);
 
     /*
      * Log information about incoming HTTPS requests
