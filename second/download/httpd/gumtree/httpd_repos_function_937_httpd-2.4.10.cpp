static char *ssl_var_lookup_ssl_version(apr_pool_t *p, char *var)
{
    if (strEQ(var, "INTERFACE")) {
        return apr_pstrdup(p, var_interface);
    }
    else if (strEQ(var, "LIBRARY_INTERFACE")) {
        return apr_pstrdup(p, var_library_interface);
    }
    else if (strEQ(var, "LIBRARY")) {
        return apr_pstrdup(p, var_library);
    }
    return NULL;
}