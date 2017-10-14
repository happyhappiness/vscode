static void ssl_init_ctx_tls_extensions(server_rec *s,
                                        apr_pool_t *p,
                                        apr_pool_t *ptemp,
                                        modssl_ctx_t *mctx)
{
    /*
     * Configure TLS extensions support
     */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01893)
                 "Configuring TLS extension handling");

    /*
     * Server name indication (SNI)
     */
    if (!SSL_CTX_set_tlsext_servername_callback(mctx->ssl_ctx,
                          ssl_callback_ServerNameIndication) ||
        !SSL_CTX_set_tlsext_servername_arg(mctx->ssl_ctx, mctx)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01894)
                     "Unable to initialize TLS servername extension "
                     "callback (incompatible OpenSSL version?)");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

#ifdef HAVE_OCSP_STAPLING
    /*
     * OCSP Stapling support, status_request extension
     */
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        modssl_init_stapling(s, p, ptemp, mctx);
    }
#endif

#ifdef HAVE_SRP
    /*
     * TLS-SRP support
     */
    if (mctx->srp_vfile != NULL) {
        int err;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02308)
                     "Using SRP verifier file [%s]", mctx->srp_vfile);

        if (!(mctx->srp_vbase = SRP_VBASE_new(mctx->srp_unknown_user_seed))) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02309)
                         "Unable to initialize SRP verifier structure "
                         "[%s seed]",
                         mctx->srp_unknown_user_seed ? "with" : "without");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            ssl_die(s);
        }

        err = SRP_VBASE_init(mctx->srp_vbase, mctx->srp_vfile);
        if (err != SRP_NO_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02310)
                         "Unable to load SRP verifier file [error %d]", err);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            ssl_die(s);
        }

        SSL_CTX_set_srp_username_callback(mctx->ssl_ctx,
                                          ssl_callback_SRPServerParams);
        SSL_CTX_set_srp_cb_arg(mctx->ssl_ctx, mctx);
    }
#endif
}