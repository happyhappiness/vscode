static void modssl_ctx_init_proxy(SSLSrvConfigRec *sc,
                                  apr_pool_t *p)
{
    modssl_ctx_t *mctx;

    mctx = sc->proxy = apr_palloc(p, sizeof(*sc->proxy));

    modssl_ctx_init(mctx);

    mctx->pkp = apr_palloc(p, sizeof(*mctx->pkp));

    mctx->pkp->cert_file = NULL;
    mctx->pkp->cert_path = NULL;
    mctx->pkp->certs     = NULL;
}