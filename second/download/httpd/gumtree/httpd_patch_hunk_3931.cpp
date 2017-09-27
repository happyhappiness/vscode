             }
             else {
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01937)
                              "stapling_check_response: cached response expired");
             }
 
-            OCSP_BASICRESP_free(bs);
-            return SSL_TLSEXT_ERR_NOACK;
+            rv = SSL_TLSEXT_ERR_NOACK;
+        }
+
+        if (status != V_OCSP_CERTSTATUS_GOOD) {
+            char snum[MAX_STRING_LEN] = { '\0' };
+            BIO *bio = BIO_new(BIO_s_mem());
+
+            if (bio) {
+                int n;
+                if ((i2a_ASN1_INTEGER(bio, cinf->cid->serialNumber) != -1) &&
+                    ((n = BIO_read(bio, snum, sizeof snum - 1)) > 0))
+                    snum[n] = '\0';
+                BIO_free(bio);
+            }
+
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02969)
+                         "stapling_check_response: response has certificate "
+                         "status %s (reason: %s) for serial number %s",
+                         OCSP_cert_status_str(status),
+                         (reason != OCSP_REVOKED_STATUS_NOSTATUS) ?
+                         OCSP_crl_reason_str(reason) : "n/a",
+                         snum[0] ? snum : "[n/a]");
+
+            if (mctx->stapling_return_errors == FALSE) {
+                if (pok)
+                    *pok = FALSE;
+                rv = SSL_TLSEXT_ERR_NOACK;
+            }
         }
     }
 
     OCSP_BASICRESP_free(bs);
 
-    return SSL_TLSEXT_ERR_OK;
+    return rv;
 }
 
 static BOOL stapling_renew_response(server_rec *s, modssl_ctx_t *mctx, SSL *ssl,
                                     certinfo *cinf, OCSP_RESPONSE **prsp,
-                                    apr_pool_t *pool)
+                                    BOOL *pok, apr_pool_t *pool)
 {
     conn_rec *conn      = (conn_rec *)SSL_get_app_data(ssl);
     apr_pool_t *vpool;
     OCSP_REQUEST *req = NULL;
     OCSP_CERTID *id = NULL;
     STACK_OF(X509_EXTENSION) *exts;
     int i;
-    BOOL ok = FALSE;
     BOOL rv = TRUE;
     const char *ocspuri;
     apr_uri_t uri;
 
     *prsp = NULL;
     /* Build up OCSP query from server certificate info */
