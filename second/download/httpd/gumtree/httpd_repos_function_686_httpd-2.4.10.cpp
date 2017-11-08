static apr_status_t ssl_init_proxy_ctx(server_rec *s,
                                       apr_pool_t *p,
                                       apr_pool_t *ptemp,
                                       SSLSrvConfigRec *sc)
{
    apr_status_t rv;

    if ((rv = ssl_init_ctx(s, p, ptemp, sc->proxy)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_proxy_certs(s, p, ptemp, sc->proxy)) != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}