
        /* get ready for next X509_STORE_CTX_init */
        X509_STORE_CTX_cleanup(sctx);
    }

    X509_STORE_CTX_free(sctx);

    return APR_SUCCESS;
}

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

static apr_status_t ssl_init_server_ctx(server_rec *s,
                                        apr_pool_t *p,
                                        apr_pool_t *ptemp,
                                        SSLSrvConfigRec *sc,
                                        apr_array_header_t *pphrases)
{
    apr_status_t rv;
#ifdef HAVE_SSL_CONF_CMD
    ssl_ctx_param_t *param = (ssl_ctx_param_t *)sc->server->ssl_ctx_param->elts;
    SSL_CONF_CTX *cctx = sc->server->ssl_ctx_config;
    int i;
#endif

    /*
     *  Check for problematic re-initializations
     */
    if (sc->server->ssl_ctx) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02569)
                     "Illegal attempt to re-initialise SSL for server "
                     "(SSLEngine On should go in the VirtualHost, not in global scope.)");
        return APR_EGENERAL;
    }

    if ((rv = ssl_init_ctx(s, p, ptemp, sc->server)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_server_certs(s, p, ptemp, sc->server, pphrases))
        != APR_SUCCESS) {
        return rv;
    }

#ifdef HAVE_SSL_CONF_CMD
    SSL_CONF_CTX_set_ssl_ctx(cctx, sc->server->ssl_ctx);
    for (i = 0; i < sc->server->ssl_ctx_param->nelts; i++, param++) {
        ERR_clear_error();
        if (SSL_CONF_cmd(cctx, param->name, param->value) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02407)
                         "\"SSLOpenSSLConfCmd %s %s\" failed for %s",
                         param->name, param->value, sc->vhost_id);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02556)
                         "\"SSLOpenSSLConfCmd %s %s\" applied to %s",
                         param->name, param->value, sc->vhost_id);
        }
    }

    if (SSL_CONF_CTX_finish(cctx) == 0) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02547)
                         "SSL_CONF_CTX_finish() failed");
            SSL_CONF_CTX_free(cctx);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
    }
    SSL_CONF_CTX_free(cctx);
#endif

    if (SSL_CTX_check_private_key(sc->server->ssl_ctx) != 1) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02572)
                     "Failed to configure at least one certificate and key "
                     "for %s", sc->vhost_id);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        return ssl_die(s);
    }

#if defined(HAVE_OCSP_STAPLING) && defined(SSL_CTRL_SET_CURRENT_CERT)
    /*
     * OpenSSL 1.0.2 and later allows iterating over all SSL_CTX certs
     * by means of SSL_CTX_set_current_cert. Enabling stapling at this
     * (late) point makes sure that we catch both certificates loaded
     * via SSLCertificateFile and SSLOpenSSLConfCmd Certificate.
     */
    if (sc->server->stapling_enabled == TRUE) {
        X509 *cert;
        int i = 0;
        int ret = SSL_CTX_set_current_cert(sc->server->ssl_ctx,
                                           SSL_CERT_SET_FIRST);
        while (ret) {
            cert = SSL_CTX_get0_certificate(sc->server->ssl_ctx);
            if (!cert || !ssl_stapling_init_cert(s, sc->server, cert)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02604)
                             "Unable to configure certificate %s:%d "
                             "for stapling", sc->vhost_id, i);
            }
            ret = SSL_CTX_set_current_cert(sc->server->ssl_ctx,
                                           SSL_CERT_SET_NEXT);
            i++;
        }
    }
#endif

#ifdef HAVE_TLS_SESSION_TICKETS
    if ((rv = ssl_init_ticket_key(s, p, ptemp, sc->server)) != APR_SUCCESS) {
        return rv;
    }
#endif

    return APR_SUCCESS;
}

/*
 * Configure a particular server
 */
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

apr_status_t ssl_init_CheckServers(server_rec *base_server, apr_pool_t *p)
{
    server_rec *s, *ps;
    SSLSrvConfigRec *sc;
    apr_hash_t *table;
    const char *key;
    apr_ssize_t klen;
