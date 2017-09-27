             if (cipher_list_old) {
                 cipher_list_old = sk_SSL_CIPHER_dup(cipher_list_old);
             }
         }
 
         /* configure new state */
-        if ((dc->szCipherSuite || sc->server->auth.cipher_suite) &&
-            !SSL_set_cipher_list(ssl, dc->szCipherSuite ?
-                                      dc->szCipherSuite :
-                                      sc->server->auth.cipher_suite)) {
+        if (is_slave) {
+            /* TODO: this categorically fails changed cipher suite settings
+             * on slave connections. We could do better by
+             * - create a new SSL* from our SSL_CTX and set cipher suite there,
+             *   and retrieve ciphers, free afterwards
+             * Modifying the SSL on a slave connection is no good.
+             */
+            apr_table_setn(r->notes, "ssl-renegotiate-forbidden", "cipher-suite");
+            return HTTP_FORBIDDEN;
+        }
+
+        if (!SSL_set_cipher_list(ssl, ncipher_suite)) {
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02253)
                           "Unable to reconfigure (per-directory) "
                           "permitted SSL ciphers");
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);
 
             if (cipher_list_old) {
