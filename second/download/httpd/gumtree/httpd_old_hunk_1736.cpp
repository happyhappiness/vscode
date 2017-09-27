                              (char *)mctx->crl_path);

    if (!mctx->crl) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to configure X.509 CRL storage "
                "for certificate revocation");
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }
}

static void ssl_init_ctx_cert_chain(server_rec *s,
                                    apr_pool_t *p,
                                    apr_pool_t *ptemp,
                                    modssl_ctx_t *mctx)
{
    BOOL skip_first = FALSE;
    int i, n;
    const char *chain = mctx->cert_chain;

    /*
     * Optionally configure extra server certificate chain certificates.
     * This is usually done by OpenSSL automatically when one of the
     * server cert issuers are found under SSLCACertificatePath or in
     * SSLCACertificateFile. But because these are intended for client
     * authentication it can conflict. For instance when you use a
