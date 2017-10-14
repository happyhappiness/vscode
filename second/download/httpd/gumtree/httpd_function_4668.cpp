static void ssl_init_ctx_crl(server_rec *s,
                             apr_pool_t *p,
                             apr_pool_t *ptemp,
                             modssl_ctx_t *mctx)
{
    X509_STORE *store = SSL_CTX_get_cert_store(mctx->ssl_ctx);
    unsigned long crlflags = 0;
    char *cfgp = mctx->pkp ? "SSLProxy" : "SSL";

    /*
     * Configure Certificate Revocation List (CRL) Details
     */

    if (!(mctx->crl_file || mctx->crl_path)) {
        if (mctx->crl_check_mode == SSL_CRLCHECK_LEAF ||
            mctx->crl_check_mode == SSL_CRLCHECK_CHAIN) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01899)
                         "Host %s: CRL checking has been enabled, but "
                         "neither %sCARevocationFile nor %sCARevocationPath "
                         "is configured", mctx->sc->vhost_id, cfgp, cfgp);
            ssl_die();
        }
        return;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01900)
                 "Configuring certificate revocation facility");

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
       case SSL_CRLCHECK_CHAIN:
           crlflags = X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL;
           break;
       default:
           crlflags = 0;
    }

    if (crlflags) {
        X509_STORE_set_flags(store, crlflags);
    } else {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01902)
                     "Host %s: X.509 CRL storage locations configured, "
                     "but CRL checking (%sCARevocationCheck) is not "
                     "enabled", mctx->sc->vhost_id, cfgp);
    }
}