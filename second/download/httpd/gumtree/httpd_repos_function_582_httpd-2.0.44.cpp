static void ssl_init_ctx_cleanup_server(modssl_ctx_t *mctx)
{
    int i;

    ssl_init_ctx_cleanup(mctx);

    for (i=0; i < SSL_AIDX_MAX; i++) {
        MODSSL_CFG_ITEM_FREE(X509_free,
                             mctx->pks->certs[i]);

        MODSSL_CFG_ITEM_FREE(EVP_PKEY_free,
                             mctx->pks->keys[i]);
    }
}