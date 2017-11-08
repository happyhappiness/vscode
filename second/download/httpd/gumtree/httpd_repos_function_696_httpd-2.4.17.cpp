apr_status_t ssl_init_ConfigureServer(server_rec *s,
                                      apr_pool_t *p,
                                      apr_pool_t *ptemp,
                                      SSLSrvConfigRec *sc,
                                      apr_array_header_t *pphrases)
{
    apr_status_t rv;

    /* Initialize the server if SSL is enabled or optional.
     */
    if ((sc->enabled == SSL_ENABLED_TRUE) || (sc->enabled == SSL_ENABLED_OPTIONAL)) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01914)
                     "Configuring server %s for SSL protocol", sc->vhost_id);
        if ((rv = ssl_init_server_ctx(s, p, ptemp, sc, pphrases))
            != APR_SUCCESS) {
            return rv;
        }
    }

    if (sc->proxy_enabled) {
        if ((rv = ssl_init_proxy_ctx(s, p, ptemp, sc)) != APR_SUCCESS) {
            return rv;
        }
    }

    return APR_SUCCESS;
}