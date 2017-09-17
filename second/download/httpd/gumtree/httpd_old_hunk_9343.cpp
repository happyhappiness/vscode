	return ap_construct_url(r->pool, "/", r);
    }

    /* must be a relative URL to be combined with base */
    if (strchr(base, '/') == NULL && (!strncmp(value, "../", 3)
        || !strcmp(value, ".."))) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "invalid base directive in map file: %s", r->uri);
        return NULL;
    }
    my_base = ap_pstrdup(r->pool, base);
    string_pos = my_base;
    while (*string_pos) {
