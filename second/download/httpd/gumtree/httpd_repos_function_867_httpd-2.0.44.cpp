static const char *ssl_var_log_handler_x(request_rec *r, char *a)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    char *result;

    result = NULL;
    if (sslconn && sslconn->ssl)
        result = ssl_var_lookup(r->pool, r->server, r->connection, r, a);
    if (result != NULL && result[0] == NUL)
        result = NULL;
    return result;
}