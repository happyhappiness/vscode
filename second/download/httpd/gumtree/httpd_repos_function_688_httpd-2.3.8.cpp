static X509 *stapling_get_issuer(modssl_ctx_t *mctx, X509 *x)
{
    X509 *issuer = NULL;
    int i;
    X509_STORE *st = SSL_CTX_get_cert_store(mctx->ssl_ctx);
    X509_STORE_CTX inctx;

    for (i = 0; i < sk_X509_num(mctx->ssl_ctx->extra_certs); i++) {
        issuer = sk_X509_value(mctx->ssl_ctx->extra_certs, i);
        if (X509_check_issued(issuer, x) == X509_V_OK) {
            CRYPTO_add(&issuer->references, 1, CRYPTO_LOCK_X509);
            return issuer;
        }
    }

    if (!X509_STORE_CTX_init(&inctx, st, NULL, NULL))
        return 0;
    if (X509_STORE_CTX_get1_issuer(&issuer, &inctx, x) <= 0)
        issuer = NULL;
    X509_STORE_CTX_cleanup(&inctx);
    return issuer;

}