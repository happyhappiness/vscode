static void ssl_init_ctx_cleanup_proxy(modssl_ctx_t *mctx)
{
    ssl_init_ctx_cleanup(mctx);

    if (mctx->pkp->certs) {
        int i = 0;
        int ncerts = sk_X509_INFO_num(mctx->pkp->certs);

        if (mctx->pkp->ca_certs) {
            for (i = 0; i < ncerts; i++) {
                if (mctx->pkp->ca_certs[i] != NULL) {
                    sk_X509_pop_free(mctx->pkp->ca_certs[i], X509_free);
                }
            }
        }

        sk_X509_INFO_pop_free(mctx->pkp->certs, X509_INFO_free);
        mctx->pkp->certs = NULL;
    }
}