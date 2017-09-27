        return ap_construct_url(r->pool, "/", r);
    }

    /* must be a relative URL to be combined with base */
    if (ap_strchr_c(base, '/') == NULL && (!strncmp(value, "../", 3)
        || !strcmp(value, ".."))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "invalid base directive in map file: %s", r->uri);
        return NULL;
    }
    my_base = apr_pstrdup(r->pool, base);
    string_pos = my_base;
    while (*string_pos) {
