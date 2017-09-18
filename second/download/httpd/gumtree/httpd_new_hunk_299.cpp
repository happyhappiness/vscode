     */

    if (!(mctx->crl_file || mctx->crl_path)) {
        return;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring certificate revocation facility");

    mctx->crl =
        SSL_X509_STORE_create((char *)mctx->crl_file,
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
