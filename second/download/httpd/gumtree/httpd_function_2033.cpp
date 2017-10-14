static void ssl_init_ctx_verify(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = mctx->ssl_ctx;

    int verify = SSL_VERIFY_NONE;
    STACK_OF(X509_NAME) *ca_list;

    if (mctx->auth.verify_mode == SSL_CVERIFY_UNSET) {
        mctx->auth.verify_mode = SSL_CVERIFY_NONE;
    }

    if (mctx->auth.verify_depth == UNSET) {
        mctx->auth.verify_depth = 1;
    }

    /*
     *  Configure callbacks for SSL context
     */
    if (mctx->auth.verify_mode == SSL_CVERIFY_REQUIRE) {
        verify |= SSL_VERIFY_PEER_STRICT;
    }

    if ((mctx->auth.verify_mode == SSL_CVERIFY_OPTIONAL) ||
        (mctx->auth.verify_mode == SSL_CVERIFY_OPTIONAL_NO_CA))
    {
        verify |= SSL_VERIFY_PEER;
    }

    SSL_CTX_set_verify(ctx, verify, ssl_callback_SSLVerify);

    /*
     * Configure Client Authentication details
     */
    if (mctx->auth.ca_cert_file || mctx->auth.ca_cert_path) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Configuring client authentication");

        if (!SSL_CTX_load_verify_locations(ctx,
                         MODSSL_PCHAR_CAST mctx->auth.ca_cert_file,
                         MODSSL_PCHAR_CAST mctx->auth.ca_cert_path))
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to configure verify locations "
                    "for client authentication");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
            ssl_die();
        }

        if (mctx->pks && (mctx->pks->ca_name_file || mctx->pks->ca_name_path)) {
            ca_list = ssl_init_FindCAList(s, ptemp,
                                          mctx->pks->ca_name_file,
                                          mctx->pks->ca_name_path);
        } else
            ca_list = ssl_init_FindCAList(s, ptemp,
                                          mctx->auth.ca_cert_file,
                                          mctx->auth.ca_cert_path);
        if (!ca_list) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Unable to determine list of acceptable "
                    "CA certificates for client authentication");
            ssl_die();
        }

        SSL_CTX_set_client_CA_list(ctx, ca_list);
    }

    /*
     * Give a warning when no CAs were configured but client authentication
     * should take place. This cannot work.
     */
    if (mctx->auth.verify_mode == SSL_CVERIFY_REQUIRE) {
        ca_list = SSL_CTX_get_client_CA_list(ctx);

        if (sk_X509_NAME_num(ca_list) == 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "Init: Oops, you want to request client "
                         "authentication, but no CAs are known for "
                         "verification!?  [Hint: SSLCACertificate*]");
        }
    }
}