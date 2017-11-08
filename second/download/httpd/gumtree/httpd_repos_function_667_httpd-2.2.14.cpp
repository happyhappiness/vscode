char *SSL_make_ciphersuite(apr_pool_t *p, SSL *ssl)
{
    STACK_OF(SSL_CIPHER) *sk;
    SSL_CIPHER *c;
    int i;
    int l;
    char *cpCipherSuite;
    char *cp;

    if (ssl == NULL)
        return "";
    if ((sk = (STACK_OF(SSL_CIPHER) *)SSL_get_ciphers(ssl)) == NULL)
        return "";
    l = 0;
    for (i = 0; i < sk_SSL_CIPHER_num(sk); i++) {
        c = sk_SSL_CIPHER_value(sk, i);
        l += strlen(SSL_CIPHER_get_name(c))+2+1;
    }
    if (l == 0)
        return "";
    cpCipherSuite = (char *)apr_palloc(p, l+1);
    cp = cpCipherSuite;
    for (i = 0; i < sk_SSL_CIPHER_num(sk); i++) {
        c = sk_SSL_CIPHER_value(sk, i);
        l = strlen(SSL_CIPHER_get_name(c));
        memcpy(cp, SSL_CIPHER_get_name(c), l);
        cp += l;
        *cp++ = '/';
        *cp++ = (SSL_CIPHER_get_valid(c) == 1 ? '1' : '0');
        *cp++ = ':';
    }
    *(cp-1) = NUL;
    return cpCipherSuite;
}