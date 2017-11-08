int ssl_engine_disable(conn_rec *c)
{
    SSLSrvConfigRec *sc;

    SSLConnRec *sslconn = myConnConfig(c);

    if (sslconn) {
        sc = mySrvConfig(sslconn->server);
    }
    else {
        sc = mySrvConfig(c->base_server);
    }
    if (sc->enabled == SSL_ENABLED_FALSE) {
        return 0;
    }

    sslconn = ssl_init_connection_ctx(c);

    sslconn->disabled = 1;

    return 1;
}