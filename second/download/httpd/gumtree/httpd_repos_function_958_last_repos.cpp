static int ssl_is_https(conn_rec *c)
{
    SSLConnRec *sslconn = ssl_get_effective_config(c);
    return sslconn && sslconn->ssl;
}