 
     ptr = asn1->cpData;
     if (!(pkey = d2i_PrivateKey(pkey_type, NULL, &ptr, asn1->nData)))
     {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                 "Unable to import %s server private key", type);
-        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
         ssl_die();
     }
 
     if (SSL_CTX_use_PrivateKey(mctx->ssl_ctx, pkey) <= 0) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                 "Unable to configure %s server private key", type);
-        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
         ssl_die();
     }
 
     /*
      * XXX: wonder if this is still needed, this is old todo doc.
      * (see http://www.psy.uq.edu.au/~ftp/Crypto/ssleay/TODO.html)
