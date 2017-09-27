    if (!SSL_CTX_set_tlsext_servername_callback(mctx->ssl_ctx,
                          ssl_callback_ServerNameIndication) ||
        !SSL_CTX_set_tlsext_servername_arg(mctx->ssl_ctx, mctx)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Unable to initialize TLS servername extension "
                     "callback (incompatible OpenSSL version?)");
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }
}
#endif

static void ssl_init_ctx_protocol(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
