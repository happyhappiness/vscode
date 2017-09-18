    struct accept_rec accept_info;
    void *new_var;
    int anymatch = 0;

    clean_var_rec(&mime_info);

    if (r->proxyreq || !r->filename 
                    || !ap_os_is_path_absolute(neg->pool, r->filename)) {
        return DECLINED;
    }

    /* Only absolute paths here */
    if (!(filp = strrchr(r->filename, '/'))) {
        return DECLINED;
    }
    ++filp;
    prefix_len = strlen(filp);

    if ((status = apr_dir_open(&dirp, neg->dir_name, neg->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                    "cannot read directory for multi: %s", neg->dir_name);
