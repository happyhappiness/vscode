static char *ssl_var_lookup_ssl_cipher(apr_pool_t *p, conn_rec *c, char *var)
{
    SSLConnRec *sslconn = myConnConfig(c);
    char *result;
    BOOL resdup;
    int usekeysize, algkeysize;
    SSL *ssl;

    result = NULL;
    resdup = TRUE;

    ssl = sslconn->ssl;
    ssl_var_lookup_ssl_cipher_bits(ssl, &usekeysize, &algkeysize);

    if (ssl && strEQ(var, "")) {
        MODSSL_SSL_CIPHER_CONST SSL_CIPHER *cipher = SSL_get_current_cipher(ssl);
        result = (cipher != NULL ? (char *)SSL_CIPHER_get_name(cipher) : NULL);
    }
    else if (strcEQ(var, "_EXPORT"))
        result = (usekeysize < 56 ? "true" : "false");
    else if (strcEQ(var, "_USEKEYSIZE")) {
        result = apr_itoa(p, usekeysize);
        resdup = FALSE;
    }
    else if (strcEQ(var, "_ALGKEYSIZE")) {
        result = apr_itoa(p, algkeysize);
        resdup = FALSE;
    }

    if (result != NULL && resdup)
        result = apr_pstrdup(p, result);
    return result;
}