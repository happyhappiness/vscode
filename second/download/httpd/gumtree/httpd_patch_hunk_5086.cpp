 
     /*
      *  Check for problematic re-initializations
      */
     if (mctx->pks->certs[SSL_AIDX_RSA] ||
         mctx->pks->certs[SSL_AIDX_DSA]
-#ifndef OPENSSL_NO_EC
+#ifdef HAVE_ECC
       || mctx->pks->certs[SSL_AIDX_ECC]
 #endif
         )
     {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01892)
                 "Illegal attempt to re-initialise SSL for server "
                 "(SSLEngine On should go in the VirtualHost, not in global scope.)");
         ssl_die(s);
     }
 }
 
-#ifndef OPENSSL_NO_TLSEXT
+#ifdef HAVE_TLSEXT
 static void ssl_init_ctx_tls_extensions(server_rec *s,
                                         apr_pool_t *p,
                                         apr_pool_t *ptemp,
                                         modssl_ctx_t *mctx)
 {
     /*
