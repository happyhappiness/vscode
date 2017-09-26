    apr_int32_t autoindex_opts = autoindex_conf->opts;
    char keyid;
    char direction;
    char *colargs;
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
    }
    if (autoindex_conf->charset) {
        charset = autoindex_conf->charset;
    }
    else {
#if APR_HAS_UNICODE_FS
        charset = "UTF-8";
#else
        charset = "ISO-8859-1";
#endif
    }
    if (*charset) {
        ap_set_content_type(r, apr_pstrcat(r->pool, ctype, ";charset=",
                            charset, NULL));
    }
    else {
        ap_set_content_type(r, ctype);
    }

    if (autoindex_opts & TRACK_MODIFIED) {
        ap_update_mtime(r, r->finfo.mtime);
        ap_set_last_modified(r);
        ap_set_etag(r);
    }
    if (r->header_only) {
