static void modssl_ctx_init_server(SSLSrvConfigRec *sc,
                                   apr_pool_t *p)
{
    modssl_ctx_t *mctx;

    mctx = sc->server = apr_palloc(p, sizeof(*sc->server));

    modssl_ctx_init(mctx);

    mctx->pks = apr_pcalloc(p, sizeof(*mctx->pks));

    /* mctx->pks->... certs/keys are set during module init */

#ifdef HAVE_TLS_SESSION_TICKETS
    mctx->ticket_key = apr_pcalloc(p, sizeof(*mctx->ticket_key));
#endif
}