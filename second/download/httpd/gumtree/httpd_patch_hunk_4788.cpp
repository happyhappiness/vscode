     sctx = X509_STORE_CTX_new();
 
     if (!sctx) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02208)
                      "SSL proxy client cert initialization failed");
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-        ssl_die();
+        ssl_die(s);
     }
 
     X509_STORE_load_locations(store, pkp->ca_cert_file, NULL);
 
     for (n = 0; n < ncerts; n++) {
         int i;
