     int errdepth = X509_STORE_CTX_get_error_depth(ctx);
     int depth, verify;
 
     /*
      * Log verification information
      */
-    if (s->loglevel >= APLOG_DEBUG) {
-        X509 *cert  = X509_STORE_CTX_get_current_cert(ctx);
-        char *sname = X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);
-        char *iname = X509_NAME_oneline(X509_get_issuer_name(cert),  NULL, 0);
-
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, conn,
-                      "Certificate Verification: "
-                      "depth: %d, subject: %s, issuer: %s",
-                      errdepth,
-                      sname ? sname : "-unknown-",
-                      iname ? iname : "-unknown-");
-
-        if (sname) {
-            modssl_free(sname);
-        }
-
-        if (iname) {
-            modssl_free(iname);
-        }
-    }
+    ssl_log_cxerror(SSLLOG_MARK, APLOG_DEBUG, 0, conn,
+                    X509_STORE_CTX_get_current_cert(ctx),
+                    "Certificate Verification, depth %d",
+                    errdepth);
 
     /*
      * Check for optionally acceptable non-verifiable issuer situation
      */
     if (dc && (dc->nVerifyClient != SSL_CVERIFY_UNSET)) {
         verify = dc->nVerifyClient;
