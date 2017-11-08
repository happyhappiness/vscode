static SSLConnRec *ssl_get_effective_config(conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);
    if (!(sslconn && sslconn->ssl) && c->master) {
        /* use master connection if no SSL defined here */
        sslconn = myConnConfig(c->master);
    }
    return sslconn;
}