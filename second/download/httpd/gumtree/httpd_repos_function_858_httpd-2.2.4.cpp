static char *ssl_var_lookup_ssl(apr_pool_t *p, conn_rec *c, char *var)
{
    SSLConnRec *sslconn = myConnConfig(c);
    char *result;
    X509 *xs;
    STACK_OF(X509) *sk;
    SSL *ssl;

    result = NULL;

    ssl = sslconn->ssl;
    if (strlen(var) > 8 && strcEQn(var, "VERSION_", 8)) {
        result = ssl_var_lookup_ssl_version(p, var+8);
    }
    else if (ssl != NULL && strcEQ(var, "PROTOCOL")) {
        result = (char *)SSL_get_version(ssl);
    }
    else if (ssl != NULL && strcEQ(var, "SESSION_ID")) {
        char buf[SSL_SESSION_ID_STRING_LEN];
        SSL_SESSION *pSession = SSL_get_session(ssl);
        if (pSession) {
            result = apr_pstrdup(p, SSL_SESSION_id2sz(
                                     SSL_SESSION_get_session_id(pSession),
                                     SSL_SESSION_get_session_id_length(pSession),
                                     buf, sizeof(buf)));
        }
    }
    else if (ssl != NULL && strlen(var) >= 6 && strcEQn(var, "CIPHER", 6)) {
        result = ssl_var_lookup_ssl_cipher(p, c, var+6);
    }
    else if (ssl != NULL && strlen(var) > 18 && strcEQn(var, "CLIENT_CERT_CHAIN_", 18)) {
        sk = SSL_get_peer_cert_chain(ssl);
        result = ssl_var_lookup_ssl_cert_chain(p, sk, var+18);
    }
    else if (ssl != NULL && strcEQ(var, "CLIENT_VERIFY")) {
        result = ssl_var_lookup_ssl_cert_verify(p, c);
    }
    else if (ssl != NULL && strlen(var) > 7 && strcEQn(var, "CLIENT_", 7)) {
        if ((xs = SSL_get_peer_certificate(ssl)) != NULL) {
            result = ssl_var_lookup_ssl_cert(p, xs, var+7);
            X509_free(xs);
        }
    }
    else if (ssl != NULL && strlen(var) > 7 && strcEQn(var, "SERVER_", 7)) {
        if ((xs = SSL_get_certificate(ssl)) != NULL)
            result = ssl_var_lookup_ssl_cert(p, xs, var+7);
    }
    else if (ssl != NULL && strcEQ(var, "COMPRESS_METHOD")) {
        result = ssl_var_lookup_ssl_compress_meth(ssl);
    }
    return result;
}