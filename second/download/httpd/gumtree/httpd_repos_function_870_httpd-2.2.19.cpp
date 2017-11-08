void ssl_var_register(apr_pool_t *p)
{
    char *cp, *cp2;

    APR_REGISTER_OPTIONAL_FN(ssl_is_https);
    APR_REGISTER_OPTIONAL_FN(ssl_var_lookup);
    APR_REGISTER_OPTIONAL_FN(ssl_ext_lookup);

    /* Perform once-per-process library version determination: */
    var_library = apr_pstrdup(p, SSL_LIBRARY_DYNTEXT);

    if ((cp = strchr(var_library, ' ')) != NULL) {
        *cp = '/';
        if ((cp2 = strchr(cp, ' ')) != NULL)
            *cp2 = NUL;
    }

    if ((cp = strchr(var_library_interface, ' ')) != NULL) {
        *cp = '/';
        if ((cp2 = strchr(cp, ' ')) != NULL)
            *cp2 = NUL;
    }
}