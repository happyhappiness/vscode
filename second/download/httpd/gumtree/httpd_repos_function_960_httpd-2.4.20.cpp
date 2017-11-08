static char *ssl_var_lookup_ssl_cert_san(apr_pool_t *p, X509 *xs, char *var)
{
    int type, numlen;
    const char *onf = NULL;
    apr_array_header_t *entries;

    if (strcEQn(var, "Email_", 6)) {
        type = GEN_EMAIL;
        var += 6;
    }
    else if (strcEQn(var, "DNS_", 4)) {
        type = GEN_DNS;
        var += 4;
    }
    else if (strcEQn(var, "OTHER_", 6)) {
        type = GEN_OTHERNAME;
        var += 6;
        if (strEQn(var, "msUPN_", 6)) {
            var += 6;
            onf = "msUPN";
        }
        else if (strEQn(var, "dnsSRV_", 7)) {
            var += 7;
            onf = "id-on-dnsSRV";
        }
        else
           return NULL;
    }
    else
        return NULL;

    /* sanity check: number must be between 1 and 4 digits */
    numlen = strspn(var, "0123456789");
    if ((numlen < 1) || (numlen > 4) || (numlen != strlen(var)))
        return NULL;

    if (modssl_X509_getSAN(p, xs, type, onf, atoi(var), &entries))
        /* return the first entry from this 1-element array */
        return APR_ARRAY_IDX(entries, 0, char *);
    else
        return NULL;
}