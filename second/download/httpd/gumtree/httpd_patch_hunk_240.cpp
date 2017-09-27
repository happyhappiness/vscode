             {
                 renegotiate = TRUE;
                 /* optimization */
 
                 if ((dc->nOptions & SSL_OPT_OPTRENEGOTIATE) &&
                     (verify_old == SSL_VERIFY_NONE) &&
-                    ((cert = SSL_get_peer_certificate(ssl)) != NULL))
+                    ((peercert = SSL_get_peer_certificate(ssl)) != NULL))
                 {
                     renegotiate_quick = TRUE;
-                    X509_free(cert);
+                    X509_free(peercert);
                 }
 
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                              r->server,
                              "Changed client verification type will force "
                              "%srenegotiation",
