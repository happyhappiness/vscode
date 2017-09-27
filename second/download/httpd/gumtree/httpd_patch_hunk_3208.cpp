     PKCS7 *p7;
     STACK_OF(X509) *certs = NULL;
     FILE *f;
 
     f = fopen(pkcs7, "r");
     if (!f) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "Can't open %s", pkcs7);
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02212) "Can't open %s", pkcs7);
         ssl_die();
     }
 
     p7 = PEM_read_PKCS7(f, NULL, NULL, NULL);
     if (!p7) {
-        ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02274)
                      "Can't read PKCS7 object %s", pkcs7);
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_CRIT, s);
         exit(1);
     }
 
     switch (OBJ_obj2nid(p7->type)) {
