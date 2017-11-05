static void ssl_init_ctx_pkcs7_cert_chain(server_rec *s, modssl_ctx_t *mctx)
{
    STACK_OF(X509) *certs = ssl_read_pkcs7(s, mctx->pkcs7);
    int n;

    if (!mctx->ssl_ctx->extra_certs)
        for (n = 1; n < sk_X509_num(certs); ++n)
             SSL_CTX_add_extra_chain_cert(mctx->ssl_ctx, sk_X509_value(certs, n));
}