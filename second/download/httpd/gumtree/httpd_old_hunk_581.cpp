    apr_int32_t autoindex_opts = autoindex_conf->opts;
    char keyid;
    char direction;
    char *colargs;
    char *fullpath;
    apr_size_t dirpathlen;

    if ((status = apr_dir_open(&thedir, name, r->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Can't open directory for index: %s", r->filename);
        return HTTP_FORBIDDEN;
    }

#if APR_HAS_UNICODE_FS
    ap_set_content_type(r, "text/html;charset=utf-8");
#else
    ap_set_content_type(r, "text/html");
#endif
    if (autoindex_opts & TRACK_MODIFIED) {
        ap_update_mtime(r, r->finfo.mtime);
        ap_set_last_modified(r);
        ap_set_etag(r);
    }
    if (r->header_only) {
