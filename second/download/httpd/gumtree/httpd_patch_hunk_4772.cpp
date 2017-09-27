      * check for important parameters and the
      * possibility that the user forgot to set them.
      */
     if (!mctx->pks->cert_files[0] && !mctx->pkcs7) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01891)
                 "No SSL Certificate set [hint: SSLCertificateFile]");
-        ssl_die();
+        ssl_die(s);
     }
 
     /*
      *  Check for problematic re-initializations
      */
     if (mctx->pks->certs[SSL_AIDX_RSA] ||
