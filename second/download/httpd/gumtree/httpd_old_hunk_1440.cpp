                "Oops, no RSA, DSA or ECC server private key found?!");
#else
                "Oops, no RSA or DSA server private key found?!");
#endif
        ssl_die();
    }
}

static void ssl_init_proxy_certs(server_rec *s,
                                 apr_pool_t *p,
                                 apr_pool_t *ptemp,
                                 modssl_ctx_t *mctx)
{
