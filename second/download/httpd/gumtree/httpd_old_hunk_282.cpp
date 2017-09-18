{
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);

    SSLConnRec *sslconn = ssl_init_connection_ctx(c);

    if (!sc->proxy_enabled) {
        ssl_log(c->base_server, SSL_LOG_ERROR,
                "SSL Proxy requested for %s but not enabled "
                "[Hint: SSLProxyEngine]", sc->vhost_id);

        return 0;
    }

    sslconn->is_proxy = 1;
    sslconn->disabled = 0;
