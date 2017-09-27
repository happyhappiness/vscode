                                   modssl_ctx_t *mctx)
 {
     SSL_CTX *ctx = NULL;
     SSL_METHOD *method = NULL;
     char *cp;
     int protocol = mctx->protocol;
-    SSLSrvConfigRec *sc = mySrvConfig(s);
 
     /*
      *  Create the new per-server SSL context
      */
     if (protocol == SSL_PROTOCOL_NONE) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
