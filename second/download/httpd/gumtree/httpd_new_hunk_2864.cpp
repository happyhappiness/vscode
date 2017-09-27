    char *value, *keylast;
    apr_status_t rv;

    if ((rv = apr_file_open(&fp, file, APR_READ|APR_BUFFERED, APR_OS_DEFAULT,
                            r->pool)) != APR_SUCCESS)
    {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00655)
                      "mod_rewrite: can't open text RewriteMap file %s", file);
        return NULL;
    }

    keylast = key + strlen(key);
    value = NULL;
