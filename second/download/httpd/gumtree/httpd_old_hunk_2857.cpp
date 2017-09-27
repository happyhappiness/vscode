    }
    ++filp;
    prefix_len = strlen(filp);

    if ((status = apr_dir_open(&dirp, neg->dir_name,
                               neg->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                    "cannot read directory for multi: %s", neg->dir_name);
        return HTTP_FORBIDDEN;
    }

    while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp) == APR_SUCCESS) {
        apr_array_header_t *exception_list;
