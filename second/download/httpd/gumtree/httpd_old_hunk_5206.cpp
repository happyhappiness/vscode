
        /* get ready for next X509_STORE_CTX_init */
        X509_STORE_CTX_cleanup(sctx);
    }

    X509_STORE_CTX_free(sctx);
}

static void ssl_init_proxy_ctx(server_rec *s,
                               apr_pool_t *p,
                               apr_pool_t *ptemp,
                               SSLSrvConfigRec *sc)
{
    ssl_init_ctx(s, p, ptemp, sc->proxy);

    ssl_init_proxy_certs(s, p, ptemp, sc->proxy);
}

static void ssl_init_server_ctx(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                SSLSrvConfigRec *sc)
{
    ssl_init_server_check(s, p, ptemp, sc->server);

    ssl_init_ctx(s, p, ptemp, sc->server);

    ssl_init_server_certs(s, p, ptemp, sc->server);

#ifdef HAVE_TLS_SESSION_TICKETS
    ssl_init_ticket_key(s, p, ptemp, sc->server);
#endif
}

/*
 * Configure a particular server
 */
void ssl_init_ConfigureServer(server_rec *s,
                              apr_pool_t *p,
                              apr_pool_t *ptemp,
                              SSLSrvConfigRec *sc)
{
    /* Initialize the server if SSL is enabled or optional.
     */
    if ((sc->enabled == SSL_ENABLED_TRUE) || (sc->enabled == SSL_ENABLED_OPTIONAL)) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01914)
                     "Configuring server %s for SSL protocol", sc->vhost_id);
        ssl_init_server_ctx(s, p, ptemp, sc);
    }

    if (sc->proxy_enabled) {
        ssl_init_proxy_ctx(s, p, ptemp, sc);
    }
}

void ssl_init_CheckServers(server_rec *base_server, apr_pool_t *p)
{
    server_rec *s, *ps;
    SSLSrvConfigRec *sc;
    apr_hash_t *table;
    const char *key;
    apr_ssize_t klen;
