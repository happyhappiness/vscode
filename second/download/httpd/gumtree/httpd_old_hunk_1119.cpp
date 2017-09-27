    if (sslconn) {
        return sslconn;
    }

    sslconn = apr_pcalloc(c->pool, sizeof(*sslconn));

    myConnConfigSet(c, sslconn);

    return sslconn;
}

int ssl_proxy_enable(conn_rec *c)
{
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);

    SSLConnRec *sslconn = ssl_init_connection_ctx(c);

    if (!sc->proxy_enabled) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "SSL Proxy requested for %s but not enabled "
                      "[Hint: SSLProxyEngine]", sc->vhost_id);

