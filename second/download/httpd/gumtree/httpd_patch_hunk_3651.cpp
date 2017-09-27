         issuer = NULL;
     X509_STORE_CTX_cleanup(&inctx);
     return issuer;
 
 }
 
-int ssl_stapling_init_cert(server_rec *s, modssl_ctx_t *mctx, X509 *x)
+int ssl_stapling_init_cert(server_rec *s, apr_pool_t *p, apr_pool_t *ptemp,
+                           modssl_ctx_t *mctx, X509 *x)
 {
-    certinfo *cinf;
+    UCHAR idx[SHA_DIGEST_LENGTH];
+    certinfo *cinf = NULL;
     X509 *issuer = NULL;
+    OCSP_CERTID *cid = NULL;
     STACK_OF(OPENSSL_STRING) *aia = NULL;
 
-    if (x == NULL)
+    if ((x == NULL) || (X509_digest(x, EVP_sha1(), idx, NULL) != 1))
         return 0;
-    cinf  = X509_get_ex_data(x, stapling_ex_idx);
+
+    cinf = apr_hash_get(stapling_certinfo, idx, sizeof(idx));
     if (cinf) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02215)
-                     "ssl_stapling_init_cert: certificate already initialized!");
-        return 0;
-    }
-    cinf = OPENSSL_malloc(sizeof(certinfo));
-    if (!cinf) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02216)
-                     "ssl_stapling_init_cert: error allocating memory!");
-        return 0;
+        /* 
+         * We already parsed the certificate, and no OCSP URI was found.
+         * The certificate might be used for multiple vhosts, though,
+         * so we check for a ForceURL for this vhost.
+         */
+        if (!cinf->uri && !mctx->stapling_force_url) {
+            ssl_log_xerror(SSLLOG_MARK, APLOG_ERR, 0, ptemp, s, x,
+                           APLOGNO(02814) "ssl_stapling_init_cert: no OCSP URI "
+                           "in certificate and no SSLStaplingForceURL "
+                           "configured for server %s", mctx->sc->vhost_id);
+            return 0;
+        }
+        return 1;
     }
-    cinf->cid = NULL;
-    cinf->uri = NULL;
-    X509_set_ex_data(x, stapling_ex_idx, cinf);
-
-    issuer = stapling_get_issuer(mctx, x);
-
-    if (issuer == NULL) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02217)
-                     "ssl_stapling_init_cert: Can't retrieve issuer certificate!");
+
+    if (!(issuer = stapling_get_issuer(mctx, x))) {
+        ssl_log_xerror(SSLLOG_MARK, APLOG_ERR, 0, ptemp, s, x, APLOGNO(02217)
+                       "ssl_stapling_init_cert: can't retrieve issuer "
+                       "certificate!");
         return 0;
     }
 
-    cinf->cid = OCSP_cert_to_id(NULL, x, issuer);
+    cid = OCSP_cert_to_id(NULL, x, issuer);
     X509_free(issuer);
-    if (!cinf->cid)
+    if (!cid) {
+        ssl_log_xerror(SSLLOG_MARK, APLOG_ERR, 0, ptemp, s, x, APLOGNO(02815)
+                       "ssl_stapling_init_cert: can't create CertID "
+                       "for OCSP request");
         return 0;
-    X509_digest(x, EVP_sha1(), cinf->idx, NULL);
+    }
 
     aia = X509_get1_ocsp(x);
-    if (aia) {
-        cinf->uri = sk_OPENSSL_STRING_pop(aia);
-        X509_email_free(aia);
-    }
-    if (!cinf->uri && !mctx->stapling_force_url) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02218)
-                     "ssl_stapling_init_cert: no responder URL");
+    if (!aia && !mctx->stapling_force_url) {
+        OCSP_CERTID_free(cid);
+        ssl_log_xerror(SSLLOG_MARK, APLOG_ERR, 0, ptemp, s, x,
+                       APLOGNO(02218) "ssl_stapling_init_cert: no OCSP URI "
+                       "in certificate and no SSLStaplingForceURL set");
         return 0;
     }
+
+    /* At this point, we have determined that there's something to store */
+    cinf = apr_pcalloc(p, sizeof(certinfo));
+    memcpy (cinf->idx, idx, sizeof(idx));
+    cinf->cid = cid;
+    /* make sure cid is also freed at pool cleanup */
+    apr_pool_cleanup_register(p, cid, ssl_stapling_certid_free,
+                              apr_pool_cleanup_null);
+    if (aia) {
+       /* allocate uri from the pconf pool */
+       cinf->uri = apr_pstrdup(p, sk_OPENSSL_STRING_value(aia, 0));
+       X509_email_free(aia);
+    }
+
+    ssl_log_xerror(SSLLOG_MARK, APLOG_TRACE1, 0, ptemp, s, x,
+                   "ssl_stapling_init_cert: storing certinfo for server %s",
+                   mctx->sc->vhost_id);
+
+    apr_hash_set(stapling_certinfo, cinf->idx, sizeof(cinf->idx), cinf);
+
     return 1;
 }
 
-static certinfo *stapling_get_cert_info(server_rec *s, modssl_ctx_t *mctx,
+static certinfo *stapling_get_certinfo(server_rec *s, modssl_ctx_t *mctx,
                                         SSL *ssl)
 {
     certinfo *cinf;
     X509 *x;
+    UCHAR idx[SHA_DIGEST_LENGTH];
     x = SSL_get_certificate(ssl);
-    if (x == NULL)
+    if ((x == NULL) || (X509_digest(x, EVP_sha1(), idx, NULL) != 1))
         return NULL;
-    cinf = X509_get_ex_data(x, stapling_ex_idx);
+    cinf = apr_hash_get(stapling_certinfo, idx, sizeof(idx));
     if (cinf && cinf->cid)
         return cinf;
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01926)
-                 "stapling_get_cert_info: stapling not supported for certificate");
+                 "stapling_get_certinfo: stapling not supported for certificate");
     return NULL;
 }
 
 /*
  * OCSP response caching code. The response is preceded by a flag value
  * which indicates whether the response was invalid when it was stored.
