static void ssl_init_ctx(server_rec *s,
                         apr_pool_t *p,
                         apr_pool_t *ptemp,
                         modssl_ctx_t *mctx)
{
    ssl_init_ctx_protocol(s, p, ptemp, mctx);

    ssl_init_ctx_session_cache(s, p, ptemp, mctx);

    ssl_init_ctx_callbacks(s, p, ptemp, mctx);

    ssl_init_ctx_verify(s, p, ptemp, mctx);

    ssl_init_ctx_cipher_suite(s, p, ptemp, mctx);

    ssl_init_ctx_crl(s, p, ptemp, mctx);

    if (mctx->pks) {
        /* XXX: proxy support? */
        ssl_init_ctx_cert_chain(s, p, ptemp, mctx);
#ifdef HAVE_TLSEXT
        ssl_init_ctx_tls_extensions(s, p, ptemp, mctx);
#endif
    }
}