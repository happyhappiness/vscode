      */
     if ((certfile = APR_ARRAY_IDX(mctx->pks->cert_files, 0, const char *)) &&
         (dhparams = ssl_dh_GetParamFromFile(certfile))) {
         SSL_CTX_set_tmp_dh(mctx->ssl_ctx, dhparams);
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02540)
                      "Custom DH parameters (%d bits) for %s loaded from %s",
-                     BN_num_bits(dhparams->p), vhost_id, certfile);
+                     DH_bits(dhparams), vhost_id, certfile);
         DH_free(dhparams);
     }
 
 #ifdef HAVE_ECC
     /*
      * Similarly, try to read the ECDH curve name from SSLCertificateFile...
