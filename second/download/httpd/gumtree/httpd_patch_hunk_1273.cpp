                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_USEKEYSIZE"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_ALGKEYSIZE"));
     }
 }
 
+/*
+ * This callback function is executed while OpenSSL processes the SSL
+ * handshake and does SSL record layer stuff.  It's used to trap
+ * client-initiated renegotiations, and for dumping everything to the
+ * log.
+ */
+void ssl_callback_Info(MODSSL_INFO_CB_ARG_TYPE ssl, int where, int rc)
+{
+    conn_rec *c;
+    server_rec *s;
+    SSLConnRec *scr;
+
+    /* Retrieve the conn_rec and the associated SSLConnRec. */
+    if ((c = (conn_rec *)SSL_get_app_data((SSL *)ssl)) == NULL) {
+        return;
+    }
+
+    if ((scr = myConnConfig(c)) == NULL) {
+        return;
+    }
+
+    /* If the reneg state is to reject renegotiations, check the SSL
+     * state machine and move to ABORT if a Client Hello is being
+     * read. */
+    if ((where & SSL_CB_ACCEPT_LOOP) && scr->reneg_state == RENEG_REJECT) {
+        int state = SSL_get_state(ssl);
+        
+        if (state == SSL3_ST_SR_CLNT_HELLO_A 
+            || state == SSL23_ST_SR_CLNT_HELLO_A) {
+            scr->reneg_state = RENEG_ABORT;
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
+                          "rejecting client initiated renegotiation");
+        }
+    }
+    /* If the first handshake is complete, change state to reject any
+     * subsequent client-initated renegotiation. */
+    else if ((where & SSL_CB_HANDSHAKE_DONE) && scr->reneg_state == RENEG_INIT) {
+        scr->reneg_state = RENEG_REJECT;
+    }
+
+    s = mySrvFromConn(c);
+    if (s && s->loglevel >= APLOG_DEBUG) {
+        log_tracing_state(ssl, c, s, where, rc);
+    }
+}
+
 #ifndef OPENSSL_NO_TLSEXT
 /*
  * This callback function is executed when OpenSSL encounters an extended
  * client hello with a server name indication extension ("SNI", cf. RFC 4366).
  */
 int ssl_callback_ServerNameIndication(SSL *ssl, int *al, modssl_ctx_t *mctx)
