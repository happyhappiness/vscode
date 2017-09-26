int ssl_engine_disable(conn_rec *c)
{
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);

    SSLConnRec *sslconn;

    if (sc->enabled == SSL_ENABLED_FALSE) {
        return 0;
    }

    sslconn = ssl_init_connection_ctx(c);

    sslconn->disabled = 1;

    return 1;
}

int ssl_init_ssl_connection(conn_rec *c)
{
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
    SSL *ssl;
    SSLConnRec *sslconn = myConnConfig(c);
    char *vhost_md5;
    modssl_ctx_t *mctx;

    /*
     * Seed the Pseudo Random Number Generator (PRNG)
     */
    ssl_rand_seed(c->base_server, c->pool, SSL_RSCTX_CONNECT, "");

    if (!sslconn) {
        sslconn = ssl_init_connection_ctx(c);
    }

    mctx = sslconn->is_proxy ? sc->proxy : sc->server;

    /*
     * Create a new SSL connection with the configured server SSL context and
     * attach this to the socket. Additionally we register this attachment
     * so we can detach later.
     */
    if (!(ssl = SSL_new(mctx->ssl_ctx))) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "Unable to create a new SSL connection from the SSL "
                      "context");
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    vhost_md5 = ap_md5_binary(c->pool, (unsigned char *)sc->vhost_id,
                              sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    APR_MD5_DIGESTSIZE*2))
    {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "Unable to set session id context to `%s'", vhost_md5);
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }
