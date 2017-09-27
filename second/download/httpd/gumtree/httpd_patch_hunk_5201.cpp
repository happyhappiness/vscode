     } else {
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01902)
                      "Host %s: X.509 CRL storage locations configured, "
                      "but CRL checking (%sCARevocationCheck) is not "
                      "enabled", mctx->sc->vhost_id, cfgp);
     }
-}
 
-static void ssl_init_ctx_pkcs7_cert_chain(server_rec *s, modssl_ctx_t *mctx)
-{
-    STACK_OF(X509) *certs = ssl_read_pkcs7(s, mctx->pkcs7);
-    int n;
-    STACK_OF(X509) *extra_certs = NULL;
-
-#ifdef OPENSSL_NO_SSL_INTERN
-    SSL_CTX_get_extra_chain_certs(mctx->ssl_ctx, &extra_certs);
-#else
-    extra_certs = mctx->ssl_ctx->extra_certs;
-#endif
-
-    if (!extra_certs)
-        for (n = 1; n < sk_X509_num(certs); ++n)
-             SSL_CTX_add_extra_chain_cert(mctx->ssl_ctx, sk_X509_value(certs, n));
+    return APR_SUCCESS;
 }
 
-static void ssl_init_ctx_cert_chain(server_rec *s,
-                                    apr_pool_t *p,
-                                    apr_pool_t *ptemp,
-                                    modssl_ctx_t *mctx)
+static apr_status_t ssl_init_ctx_cert_chain(server_rec *s,
+                                            apr_pool_t *p,
+                                            apr_pool_t *ptemp,
+                                            modssl_ctx_t *mctx)
 {
     BOOL skip_first = FALSE;
     int i, n;
     const char *chain = mctx->cert_chain;
 
-    if (mctx->pkcs7) {
-        ssl_init_ctx_pkcs7_cert_chain(s, mctx);
-        return;
-    }
-
     /*
      * Optionally configure extra server certificate chain certificates.
      * This is usually done by OpenSSL automatically when one of the
      * server cert issuers are found under SSLCACertificatePath or in
      * SSLCACertificateFile. But because these are intended for client
      * authentication it can conflict. For instance when you use a
