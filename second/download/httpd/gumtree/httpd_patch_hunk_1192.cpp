         const char *ca_file = MODSSL_CFG_CA(szCACertificateFile);
         const char *ca_path = MODSSL_CFG_CA(szCACertificatePath);
 
         cert_store = X509_STORE_new();
 
         if (!X509_STORE_load_locations(cert_store, ca_file, ca_path)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                         "Unable to reconfigure verify locations "
-                         "for client authentication");
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                          "Unable to reconfigure verify locations "
+                          "for client authentication");
             ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);
 
             X509_STORE_free(cert_store);
 
             return HTTP_FORBIDDEN;
         }
