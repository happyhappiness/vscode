static char *ssl_var_lookup_ssl_version(apr_pool_t *p, char *var)
{
    char *result;
    char *cp, *cp2;

    result = NULL;

    if (strEQ(var, "PRODUCT")) {
#if defined(SSL_PRODUCT_NAME) && defined(SSL_PRODUCT_VERSION)
        result = apr_psprintf(p, "%s/%s", SSL_PRODUCT_NAME, SSL_PRODUCT_VERSION);
#else
        result = NULL;
#endif
    }
    else if (strEQ(var, "INTERFACE")) {
        result = apr_psprintf(p, "mod_ssl/%s", MOD_SSL_VERSION);
    }
    else if (strEQ(var, "LIBRARY")) {
        result = apr_pstrdup(p, SSLeay_version(SSLEAY_VERSION));
        if ((cp = strchr(result, ' ')) != NULL) {
            *cp = '/';
            if ((cp2 = strchr(cp, ' ')) != NULL)
                *cp2 = NUL;
        }
    }
    return result;
}