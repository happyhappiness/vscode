                "Oops, no RSA, DSA or ECC server private key found?!");
#else
                "Oops, no RSA or DSA server private key found?!");
#endif
        ssl_die();
    }
}

static void ssl_init_proxy_certs(server_rec *s,
                                 apr_pool_t *p,
                                 apr_pool_t *ptemp,
                                 modssl_ctx_t *mctx)
{
    int n, ncerts = 0;
    STACK_OF(X509_INFO) *sk;
    modssl_pk_proxy_t *pkp = mctx->pkp;

    SSL_CTX_set_client_cert_cb(mctx->ssl_ctx,
                               ssl_callback_proxy_cert);

    if (!(pkp->cert_file || pkp->cert_path)) {
