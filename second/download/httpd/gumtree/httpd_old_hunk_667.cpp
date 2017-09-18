    struct accept_rec accept_info;
    void *new_var;
    int anymatch = 0;

    clean_var_rec(&mime_info);

    if (!(filp = strrchr(r->filename, '/'))) {
        return DECLINED;        /* Weird... */
    }

    /* XXX this should be more general, and quit using 'specials' */
    if (strncmp(r->filename, "proxy:", 6) == 0) {
        return DECLINED;
    }

    ++filp;
    prefix_len = strlen(filp);

    if ((status = apr_dir_open(&dirp, neg->dir_name, neg->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                    "cannot read directory for multi: %s", neg->dir_name);
