    }

    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                 "Configuring permitted SSL ciphers [%s]",
                 suite);

    if (!SSL_CTX_set_cipher_list(ctx, MODSSL_PCHAR_CAST suite)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to configure permitted SSL ciphers");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }
}

static void ssl_init_ctx_crl(server_rec *s,
                             apr_pool_t *p,
                             apr_pool_t *ptemp,
                             modssl_ctx_t *mctx)
{
    /*
     * Configure Certificate Revocation List (CRL) Details
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
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }
}

static void ssl_init_ctx_pkcs7_cert_chain(server_rec *s, modssl_ctx_t *mctx)
{
    STACK_OF(X509) *certs = ssl_read_pkcs7(s, mctx->pkcs7);
    int n;

    if (!mctx->ssl_ctx->extra_certs)
        for (n = 1; n < sk_X509_num(certs); ++n)
             SSL_CTX_add_extra_chain_cert(mctx->ssl_ctx, sk_X509_value(certs, n));
}

static void ssl_init_ctx_cert_chain(server_rec *s,
                                    apr_pool_t *p,
