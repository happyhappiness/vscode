static void modssl_ctx_init_server(SSLSrvConfigRec *sc,
                                   apr_pool_t *p)
{
    modssl_ctx_t *mctx;

    mctx = sc->server = apr_palloc(p, sizeof(*sc->server));

    modssl_ctx_init(mctx, p);

    mctx->pks = apr_pcalloc(p, sizeof(*mctx->pks));

    mctx->pks->cert_files = apr_array_make(p, 3, sizeof(char *));
    mctx->pks->key_files  = apr_array_make(p, 3, sizeof(char *));

#ifdef HAVE_TLS_SESSION_TICKETS
    mctx->ticket_key = apr_pcalloc(p, sizeof(*mctx->ticket_key));
#endif
}