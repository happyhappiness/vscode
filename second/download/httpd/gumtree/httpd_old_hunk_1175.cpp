                "Illegal attempt to re-initialise SSL for server "
                "(theoretically shouldn't happen!)");
        ssl_die();
    }
}

static void ssl_init_ctx_protocol(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
                                  modssl_ctx_t *mctx)
{
    SSL_CTX *ctx = NULL;
