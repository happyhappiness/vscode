    if (!store || !X509_STORE_load_locations(store, mctx->crl_file,
                                             mctx->crl_path)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01901)
                     "Host %s: unable to configure X.509 CRL storage "
                     "for certificate revocation", mctx->sc->vhost_id);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die();
    }

    switch (mctx->crl_check_mode) {
       case SSL_CRLCHECK_LEAF:
           crlflags = X509_V_FLAG_CRL_CHECK;
           break;
