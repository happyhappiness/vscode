                 /* client cert is in the session cache, but there is
                  * no chain, since ssl3_get_client_certificate()
                  * sk_X509_shift-ed the peer cert out of the chain.
                  * we put it back here for the purpose of quick_renegotiation.
                  */
                 cert_stack = sk_new_null();
-                sk_X509_push(cert_stack, cert);
+                sk_X509_push(cert_stack, MODSSL_PCHAR_CAST cert);
             }
 
             if (!cert_stack || (sk_X509_num(cert_stack) == 0)) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                              "Cannot find peer certificate chain");
 
