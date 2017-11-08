static void modssl_ctx_init_server(SSLSrvConfigRec *sc,
                                   apr_pool_t *p)
{
    modssl_ctx_t *mctx;

    mctx = sc->server = apr_palloc(p, sizeof(*sc->server));

    modssl_ctx_init(mctx);

    mctx->pks = apr_palloc(p, sizeof(*mctx->pks));

    memset((void*)mctx->pks->cert_files, 0, sizeof(mctx->pks->cert_files));

    memset((void*)mctx->pks->key_files, 0, sizeof(mctx->pks->key_files));

    /* certs/keys are set during module init */

    memset(mctx->pks->certs, 0, sizeof(mctx->pks->certs));

    memset(mctx->pks->keys, 0, sizeof(mctx->pks->keys));
}