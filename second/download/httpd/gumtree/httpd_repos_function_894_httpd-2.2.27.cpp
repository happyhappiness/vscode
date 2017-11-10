static const char *ssl_var_log_handler_c(request_rec *r, char *a)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    char *result;

    if (sslconn == NULL || sslconn->ssl == NULL)
        return NULL;
    result = NULL;
    if (strEQ(a, "version"))
        result = ssl_var_lookup(r->pool, r->server, r->connection, r, "SSL_PROTOCOL");
    else if (strEQ(a, "cipher"))
        result = ssl_var_lookup(r->pool, r->server, r->connection, r, "SSL_CIPHER");
    else if (strEQ(a, "subjectdn") || strEQ(a, "clientcert"))
        result = ssl_var_lookup(r->pool, r->server, r->connection, r, "SSL_CLIENT_S_DN");
    else if (strEQ(a, "issuerdn") || strEQ(a, "cacert"))
        result = ssl_var_lookup(r->pool, r->server, r->connection, r, "SSL_CLIENT_I_DN");
    else if (strEQ(a, "errcode"))
        result = "-";
    else if (strEQ(a, "errstr"))
        result = (char *)sslconn->verify_error;
    if (result != NULL && result[0] == NUL)
        result = NULL;
    return result;
}