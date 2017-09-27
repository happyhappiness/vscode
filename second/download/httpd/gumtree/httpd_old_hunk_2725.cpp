    char *fullpath;
    apr_size_t dirpathlen;
    char *ctype = "text/html";
    char *charset;

    if ((status = apr_dir_open(&thedir, name, r->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Can't open directory for index: %s", r->filename);
        return HTTP_FORBIDDEN;
    }

    if (autoindex_conf->ctype) {
        ctype = autoindex_conf->ctype;
