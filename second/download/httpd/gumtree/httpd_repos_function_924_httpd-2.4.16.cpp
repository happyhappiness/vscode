static SSLConnRec *ssl_init_connection_ctx(conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);

    if (sslconn) {
        return sslconn;
    }

    sslconn = apr_pcalloc(c->pool, sizeof(*sslconn));

    sslconn->server = c->base_server;
    sslconn->verify_depth = UNSET;

    myConnConfigSet(c, sslconn);

    return sslconn;
}