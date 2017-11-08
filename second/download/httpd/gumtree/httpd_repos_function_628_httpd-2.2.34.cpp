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

    SSL_CTX_set_timeout(sc->server->ssl_ctx,
                        sc->session_cache_timeout == UNSET ?
                        SSL_SESSION_CACHE_TIMEOUT : sc->session_cache_timeout);
}