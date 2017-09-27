                                     apr_pool_t *ptemp,
                                     modssl_ctx_t *mctx)
{
    X509_STORE *store = SSL_CTX_get_cert_store(mctx->ssl_ctx);
    unsigned long crlflags = 0;
    char *cfgp = mctx->pkp ? "SSLProxy" : "SSL";
    int crl_check_mode;

    if (mctx->crl_check_mask == UNSET) {
        mctx->crl_check_mask = SSL_CRLCHECK_NONE;
    }
    crl_check_mode = mctx->crl_check_mask & ~SSL_CRLCHECK_FLAGS;

    /*
     * Configure Certificate Revocation List (CRL) Details
     */

    if (!(mctx->crl_file || mctx->crl_path)) {
        if (crl_check_mode == SSL_CRLCHECK_LEAF ||
            crl_check_mode == SSL_CRLCHECK_CHAIN) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01899)
                         "Host %s: CRL checking has been enabled, but "
                         "neither %sCARevocationFile nor %sCARevocationPath "
                         "is configured", mctx->sc->vhost_id, cfgp, cfgp);
            return ssl_die(s);
        }
