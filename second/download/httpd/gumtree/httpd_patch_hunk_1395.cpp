         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                 "No SSL protocols available [hint: SSLProtocol]");
         ssl_die();
     }
 
     cp = apr_pstrcat(p,
+#ifndef OPENSSL_NO_SSL2
                      (protocol & SSL_PROTOCOL_SSLV2 ? "SSLv2, " : ""),
+#endif
                      (protocol & SSL_PROTOCOL_SSLV3 ? "SSLv3, " : ""),
                      (protocol & SSL_PROTOCOL_TLSV1 ? "TLSv1, " : ""),
+#ifdef HAVE_TLSV1_X
+                     (protocol & SSL_PROTOCOL_TLSV1_1 ? "TLSv1.1, " : ""),
+                     (protocol & SSL_PROTOCOL_TLSV1_2 ? "TLSv1.2, " : ""),
+#endif
                      NULL);
     cp[strlen(cp)-2] = NUL;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "Creating new SSL context (protocols: %s)", cp);
 
 #ifndef OPENSSL_NO_SSL2
     if (protocol == SSL_PROTOCOL_SSLV2) {
         method = mctx->pkp ?
             SSLv2_client_method() : /* proxy */
             SSLv2_server_method();  /* server */
-        ctx = SSL_CTX_new(method);  /* only SSLv2 is left */
+    }
+    else
+#endif
+#ifdef HAVE_TLSV1_X
+    if (protocol == SSL_PROTOCOL_TLSV1_1) {
+        method = mctx->pkp ?
+            TLSv1_1_client_method() : /* proxy */
+            TLSv1_1_server_method();  /* server */
+    }
+    else if (protocol == SSL_PROTOCOL_TLSV1_2) {
+        method = mctx->pkp ?
+            TLSv1_2_client_method() : /* proxy */
+            TLSv1_2_server_method();  /* server */
     }
     else
 #endif
     {
         method = mctx->pkp ?
             SSLv23_client_method() : /* proxy */
             SSLv23_server_method();  /* server */
-        ctx = SSL_CTX_new(method); /* be more flexible */
     }
+    ctx = SSL_CTX_new(method);
 
     mctx->ssl_ctx = ctx;
 
     SSL_CTX_set_options(ctx, SSL_OP_ALL);
 
+#ifndef OPENSSL_NO_SSL2
     if (!(protocol & SSL_PROTOCOL_SSLV2)) {
         SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
     }
+#endif
 
     if (!(protocol & SSL_PROTOCOL_SSLV3)) {
         SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3);
     }
 
     if (!(protocol & SSL_PROTOCOL_TLSV1)) {
         SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1);
     }
 
+#ifdef HAVE_TLSV1_X
+    if (!(protocol & SSL_PROTOCOL_TLSV1_1)) {
+        SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_1);
+    }
+
+    if (!(protocol & SSL_PROTOCOL_TLSV1_2)) {
+        SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_2);
+    }
+#endif
+
 #ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
     if (sc->cipher_server_pref == TRUE) {
         SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);
     }
 #endif
 
