                           "could not retrieve OCSP basic response");
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
             rc = V_OCSP_CERTSTATUS_UNKNOWN;
         }
     }
 
-    if (rc == V_OCSP_CERTSTATUS_GOOD) {
-        if (OCSP_check_nonce(request, basicResponse) != 1) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01924)
-                        "Bad OCSP responder answer (bad nonce)");
-            rc = V_OCSP_CERTSTATUS_UNKNOWN;
-        }
+    if (rc == V_OCSP_CERTSTATUS_GOOD &&
+            sc->server->ocsp_use_request_nonce != FALSE &&
+            OCSP_check_nonce(request, basicResponse) != 1) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01924)
+                    "Bad OCSP responder answer (bad nonce)");
+        rc = V_OCSP_CERTSTATUS_UNKNOWN;
     }
 
     if (rc == V_OCSP_CERTSTATUS_GOOD) {
         /* TODO: allow flags configuration. */
         if (OCSP_basic_verify(basicResponse, NULL, ctx->ctx, 0) != 1) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01925)
