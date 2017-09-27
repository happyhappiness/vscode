 {
     SSL_CTX *ctx = NULL;
     MODSSL_SSL_METHOD_CONST SSL_METHOD *method = NULL;
     char *cp;
     int protocol = mctx->protocol;
     SSLSrvConfigRec *sc = mySrvConfig(s);
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+    int prot;
+#endif
 
     /*
      *  Create the new per-server SSL context
      */
     if (protocol == SSL_PROTOCOL_NONE) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02231)
