    SSLSrvConfigRec *sc;

    SSLConnRec *sslconn = ssl_init_connection_ctx(c);
    sc = mySrvConfig(sslconn->server);

    if (!sc->proxy_enabled) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01961)
                      "SSL Proxy requested for %s but not enabled "
                      "[Hint: SSLProxyEngine]", sc->vhost_id);

        return 0;
    }

