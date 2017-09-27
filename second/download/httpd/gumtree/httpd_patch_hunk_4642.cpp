     apr_socket_close(sd);
     BIO_free(bio);
 
     return response;
 }
 
+/*  _________________________________________________________________
+**
+**  OCSP other certificate support
+**  _________________________________________________________________
+*/
+
+/*
+ * Read a file that contains certificates in PEM format and
+ * return as a STACK.
+ */
+
+static STACK_OF(X509) *modssl_read_ocsp_certificates(const char *file)
+{
+    BIO *bio;
+    X509 *x509;
+    unsigned long err;
+    STACK_OF(X509) *other_certs = NULL;
+
+    if ((bio = BIO_new(BIO_s_file())) == NULL)
+        return NULL;
+    if (BIO_read_filename(bio, file) <= 0) {
+        BIO_free(bio);
+        return NULL;
+    }
+    /* create new extra chain by loading the certs */
+    while ((x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL)) != NULL) {
+        if (!other_certs) {
+                other_certs = sk_X509_new_null();
+                if (!other_certs)
+                        return NULL;
+        }
+                
+        if (!sk_X509_push(other_certs, x509)) {
+            X509_free(x509);
+            sk_X509_pop_free(other_certs, X509_free);
+            BIO_free(bio);
+            return NULL;
+        }
+    }
+    /* Make sure that only the error is just an EOF */
+    if ((err = ERR_peek_error()) > 0) {
+        if (!(   ERR_GET_LIB(err) == ERR_LIB_PEM
+              && ERR_GET_REASON(err) == PEM_R_NO_START_LINE)) {
+            BIO_free(bio);
+            sk_X509_pop_free(other_certs, X509_free);
+            return NULL;
+        }
+        while (ERR_get_error() > 0) ;
+    }
+    BIO_free(bio);
+    return other_certs;
+}
+
+void ssl_init_ocsp_certificates(server_rec *s, modssl_ctx_t *mctx)
+{
+    /*
+     * Configure Trusted OCSP certificates.
+     */
+
+    if (!mctx->ocsp_certs_file) {
+        return;
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                 "Configuring Trusted OCSP certificates");
+
+    mctx->ocsp_certs = modssl_read_ocsp_certificates(mctx->ocsp_certs_file);
+
+    if (!mctx->ocsp_certs) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                "Unable to configure OCSP Trusted Certificates");
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+        ssl_die(s);
+    }
+    mctx->ocsp_verify_flags |= OCSP_TRUSTOTHER;
+}
+
 #endif /* HAVE_OCSP */
