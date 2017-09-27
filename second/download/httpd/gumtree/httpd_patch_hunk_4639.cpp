                                     OCSP_CERTID **certid,
                                     server_rec *s, apr_pool_t *p,
                                     SSLSrvConfigRec *sc)
 {
     OCSP_REQUEST *req = OCSP_REQUEST_new();
 
-    *certid = OCSP_cert_to_id(NULL, cert, ctx->current_issuer);
+    *certid = OCSP_cert_to_id(NULL, cert, X509_STORE_CTX_get0_current_issuer(ctx));
     if (!*certid || !OCSP_request_add0_id(req, *certid)) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01921)
                      "could not retrieve certificate id");
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
         return NULL;
     }
