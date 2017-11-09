static SSLConnRec *ssl_init_connection_ctx(conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);
    SSLSrvConfigRec *sc;

    if (sslconn) {
        return sslconn;
    }

    sslconn = apr_pcalloc(c->pool, sizeof(*sslconn));

    sslconn->server = c->base_server;
    sslconn->verify_depth = UNSET;
    sc = mySrvConfig(c->base_server);
    sslconn->cipher_suite = sc->server->auth.cipher_suite;

    myConnConfigSet(c, sslconn);

    return sslconn;
}