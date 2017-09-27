         if (mctx->crl_check_mode == SSL_CRLCHECK_LEAF ||
             mctx->crl_check_mode == SSL_CRLCHECK_CHAIN) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01899)
                          "Host %s: CRL checking has been enabled, but "
                          "neither %sCARevocationFile nor %sCARevocationPath "
                          "is configured", mctx->sc->vhost_id, cfgp, cfgp);
-            ssl_die(s);
+            return ssl_die(s);
         }
-        return;
+        return APR_SUCCESS;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01900)
                  "Configuring certificate revocation facility");
 
     if (!store || !X509_STORE_load_locations(store, mctx->crl_file,
                                              mctx->crl_path)) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01901)
                      "Host %s: unable to configure X.509 CRL storage "
                      "for certificate revocation", mctx->sc->vhost_id);
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-        ssl_die(s);
+        return ssl_die(s);
     }
 
     switch (mctx->crl_check_mode) {
        case SSL_CRLCHECK_LEAF:
            crlflags = X509_V_FLAG_CRL_CHECK;
            break;
