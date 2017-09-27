     * OCSP Stapling support, status_request extension
     */
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        modssl_init_stapling(s, p, ptemp, mctx);
    }
#endif
}
#endif

static void ssl_init_ctx_protocol(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
