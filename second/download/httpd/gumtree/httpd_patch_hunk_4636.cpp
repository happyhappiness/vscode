                           "Awaiting re-negotiation handshake");
 
             /* XXX: Should replace setting state with SSL_renegotiate(ssl);
              * However, this causes failures in perl-framework currently,
              * perhaps pre-test if we have already negotiated?
              */
-#ifdef OPENSSL_NO_SSL_INTERN
-            SSL_set_state(ssl, SSL_ST_ACCEPT);
-#else
-            ssl->state = SSL_ST_ACCEPT;
-#endif
-            SSL_do_handshake(ssl);
+            /* Need to trigger renegotiation handshake by reading.
+             * Peeking 0 bytes actually works.
+             * See: http://marc.info/?t=145493359200002&r=1&w=2
+             */
+            SSL_peek(ssl, peekbuf, 0);
 
             sslconn->reneg_state = RENEG_REJECT;
 
-            if (SSL_get_state(ssl) != SSL_ST_OK) {
+            if (!SSL_is_init_finished(ssl)) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02261)
                               "Re-negotiation handshake failed");
                 ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);
 
                 r->connection->keepalive = AP_CONN_CLOSE;
                 return HTTP_FORBIDDEN;
