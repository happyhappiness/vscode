                     ((peercert = SSL_get_peer_certificate(ssl)) != NULL))
                 {
                     renegotiate_quick = TRUE;
                     X509_free(peercert);
                 }
 
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
-                             r->server,
-                             "Changed client verification type will force "
-                             "%srenegotiation",
-                             renegotiate_quick ? "quick " : "");
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                              "Changed client verification type will force "
+                              "%srenegotiation",
+                              renegotiate_quick ? "quick " : "");
              }
         }
+        /* If we're handling a request for a vhost other than the default one,
+         * then we need to make sure that client authentication is properly
+         * enforced. For clients supplying an SNI extension, the peer
+         * certificate verification has happened in the handshake already
+         * (and r->server == handshakeserver). For non-SNI requests,
+         * an additional check is needed here. If client authentication
+         * is configured as mandatory, then we can only proceed if the
+         * CA list doesn't have to be changed (OpenSSL doesn't provide
+         * an option to change the list for an existing session).
+         */
+        if ((r->server != handshakeserver)
+            && renegotiate
+            && ((verify & SSL_VERIFY_PEER) ||
+                (verify & SSL_VERIFY_FAIL_IF_NO_PEER_CERT))) {
+            SSLSrvConfigRec *hssc = mySrvConfig(handshakeserver);
+
+#define MODSSL_CFG_CA_NE(f, sc1, sc2) \
+            (sc1->server->auth.f && \
+             (!sc2->server->auth.f || \
+              strNE(sc1->server->auth.f, sc2->server->auth.f)))
+
+            if (MODSSL_CFG_CA_NE(ca_cert_file, sc, hssc) ||
+                MODSSL_CFG_CA_NE(ca_cert_path, sc, hssc)) {
+                if (verify & SSL_VERIFY_FAIL_IF_NO_PEER_CERT) {
+                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                         "Non-default virtual host with SSLVerify set to "
+                         "'require' and VirtualHost-specific CA certificate "
+                         "list is only available to clients with TLS server "
+                         "name indication (SNI) support");
+                    modssl_set_verify(ssl, verify_old, NULL);
+                    return HTTP_FORBIDDEN;
+                } else
+                    /* let it pass, possibly with an "incorrect" peer cert,
+                     * so make sure the SSL_CLIENT_VERIFY environment variable
+                     * will indicate partial success only, later on.
+                     */
+                    sslconn->verify_info = "GENEROUS";
+            }
+        }
     }
 
     /*
      * override SSLCACertificateFile & SSLCACertificatePath
      * This is only enabled if the SSL_set_cert_store() function
      * is available in the ssl library.  the 1.x based mod_ssl
