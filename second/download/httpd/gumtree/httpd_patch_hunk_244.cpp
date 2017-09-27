                              "Re-negotiation handshake failed: "
                              "Client verification failed");
 
                 return HTTP_FORBIDDEN;
             }
 
-            if (do_verify &&
-                ((cert = SSL_get_peer_certificate(ssl)) == NULL)) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                             "Re-negotiation handshake failed: "
-                             "Client certificate missing");
+            if (do_verify) {
+                if ((peercert = SSL_get_peer_certificate(ssl)) == NULL) {
+                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                                 "Re-negotiation handshake failed: "
+                                 "Client certificate missing");
 
-                return HTTP_FORBIDDEN;
+                    return HTTP_FORBIDDEN;
+                }
+
+                X509_free(peercert);
             }
         }
     }
 
     /*
      * Check SSLRequire boolean expressions
