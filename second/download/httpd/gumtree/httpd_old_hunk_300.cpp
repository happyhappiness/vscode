    }

    n = SSL_CTX_use_certificate_chain(mctx->ssl_ctx,
                                      (char *)chain, 
                                      skip_first, NULL);
    if (n < 0) {
        ssl_log(s, SSL_LOG_ERROR|SSL_INIT,
                "Failed to configure CA certificate chain!");
        ssl_die();
    }

    ssl_log(s, SSL_LOG_TRACE|SSL_INIT,
            "Configuring server certificate chain "
            "(%d CA certificate%s)",
            n, n == 1 ? "" : "s");
}

static void ssl_init_ctx(server_rec *s,
                         apr_pool_t *p,
                         apr_pool_t *ptemp,
                         modssl_ctx_t *mctx)
