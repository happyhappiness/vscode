     */

    if (!(mctx->crl_file || mctx->crl_path)) {
        return;
    }

    ssl_log(s, SSL_LOG_TRACE|SSL_INIT,
            "Configuring certificate revocation facility");

    mctx->crl =
        SSL_X509_STORE_create((char *)mctx->crl_file,
                              (char *)mctx->crl_path);

    if (!mctx->crl) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_INIT,
                "Unable to configure X.509 CRL storage "
                "for certificate revocation");
        ssl_die();
    }
}

static void ssl_init_ctx_cert_chain(server_rec *s,
                                    apr_pool_t *p,
