     }
 
     /*
      * If we already know it's not ok, log the real reason
      */
     if (!ok) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                     "Certificate Verification: Error (%d): %s",
-                     errnum, X509_verify_cert_error_string(errnum));
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
+                      "Certificate Verification: Error (%d): %s",
+                      errnum, X509_verify_cert_error_string(errnum));
 
         if (sslconn->client_cert) {
             X509_free(sslconn->client_cert);
             sslconn->client_cert = NULL;
         }
         sslconn->client_dn = NULL;
