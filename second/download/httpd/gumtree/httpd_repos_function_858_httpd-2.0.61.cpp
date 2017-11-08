static char *ssl_var_lookup_ssl_version(apr_pool_t *p, char *var)
{
    static char interface[] = "mod_ssl/" MOD_SSL_VERSION;
    static char library_interface[] = SSL_LIBRARY_TEXT;
    static char *library = NULL;
    char *result;
  
    if (!library) {
        char *cp, *cp2;
        library = apr_pstrdup(p, SSL_LIBRARY_DYNTEXT);
        if ((cp = strchr(library, ' ')) != NULL) {
            *cp = '/';
            if ((cp2 = strchr(cp, ' ')) != NULL)
                *cp2 = NUL;
        }
        if ((cp = strchr(library_interface, ' ')) != NULL) {
            *cp = '/';
            if ((cp2 = strchr(cp, ' ')) != NULL)
                *cp2 = NUL;
        }
    }

    if (strEQ(var, "INTERFACE")) {
        result = apr_pstrdup(p, interface);
    }
    else if (strEQ(var, "LIBRARY_INTERFACE")) {
        result = apr_pstrdup(p, library_interface);
    }
    else if (strEQ(var, "LIBRARY")) {
        result = apr_pstrdup(p, library);
    }
    else {
        result = NULL;
    }
    return result;
}