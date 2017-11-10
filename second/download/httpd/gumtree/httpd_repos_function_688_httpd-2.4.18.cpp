static apr_status_t ssl_init_ctx(server_rec *s,
                                 apr_pool_t *p,
                                 apr_pool_t *ptemp,
                                 modssl_ctx_t *mctx)
{
    apr_status_t rv;

    if ((rv = ssl_init_ctx_protocol(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    ssl_init_ctx_session_cache(s, p, ptemp, mctx);

    ssl_init_ctx_callbacks(s, p, ptemp, mctx);

    if ((rv = ssl_init_ctx_verify(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_ctx_cipher_suite(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_ctx_crl(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    if (mctx->pks) {
        /* XXX: proxy support? */
        if ((rv = ssl_init_ctx_cert_chain(s, p, ptemp, mctx)) != APR_SUCCESS) {
            return rv;
        }
#ifdef HAVE_TLSEXT
        if ((rv = ssl_init_ctx_tls_extensions(s, p, ptemp, mctx)) !=
            APR_SUCCESS) {
            return rv;
        }
#endif
    }

    return APR_SUCCESS;
}