static int ssl_is_https(conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);
    return sslconn && sslconn->ssl;
}