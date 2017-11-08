static apr_status_t ssl_init_ctx_cert_chain(server_rec *s,
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
     * Global ID server certificate you've to send out the intermediate
     * CA certificate, too. When you would just configure this with
     * SSLCACertificateFile and also use client authentication mod_ssl
     * would accept all clients also issued by this CA. Obviously this
     * isn't what we want in this situation. So this feature here exists
     * to allow one to explicity configure CA certificates which are
     * used only for the server certificate chain.
     */
    if (!chain) {
        return APR_SUCCESS;
    }

    for (i = 0; (i < mctx->pks->cert_files->nelts) &&
         APR_ARRAY_IDX(mctx->pks->cert_files, i, const char *); i++) {
        if (strEQ(APR_ARRAY_IDX(mctx->pks->cert_files, i, const char *), chain)) {
            skip_first = TRUE;
            break;
        }
    }

    n = use_certificate_chain(mctx->ssl_ctx, (char *)chain, skip_first, NULL);
    if (n < 0) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01903)
                "Failed to configure CA certificate chain!");
        return ssl_die(s);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01904)
                 "Configuring server certificate chain "
                 "(%d CA certificate%s)",
                 n, n == 1 ? "" : "s");

    return APR_SUCCESS;
}