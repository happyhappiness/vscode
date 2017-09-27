     STACK_OF(X509) *certs = NULL;
     FILE *f;
 
     f = fopen(pkcs7, "r");
     if (!f) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02212) "Can't open %s", pkcs7);
-        ssl_die();
+        ssl_die(s);
     }
 
     p7 = PEM_read_PKCS7(f, NULL, NULL, NULL);
     if (!p7) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02274)
                      "Can't read PKCS7 object %s", pkcs7);
