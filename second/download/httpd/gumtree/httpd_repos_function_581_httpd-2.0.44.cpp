static void ssl_init_ctx_cleanup_proxy(modssl_ctx_t *mctx)
{
    ssl_init_ctx_cleanup(mctx);

    if (mctx->pkp->certs) {
        sk_X509_INFO_pop_free(mctx->pkp->certs, X509_INFO_free);
    }
}