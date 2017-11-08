static char *ssl_var_lookup_ssl_cert_san(apr_pool_t *p, X509 *xs, char *var)
{
    int type, numlen;
    apr_array_header_t *entries;

    if (strcEQn(var, "Email_", 6)) {
        type = GEN_EMAIL;
        var += 6;
    }
    else if (strcEQn(var, "DNS_", 4)) {
        type = GEN_DNS;
        var += 4;
    }
    else
        return NULL;

    /* sanity check: number must be between 1 and 4 digits */
    numlen = strspn(var, "0123456789");
    if ((numlen < 1) || (numlen > 4) || (numlen != strlen(var)))
        return NULL;

    if (SSL_X509_getSAN(p, xs, type, atoi(var), &entries))
       /* return the first entry from this 1-element array */
       return APR_ARRAY_IDX(entries, 0, char *);
    else
       return NULL;
}