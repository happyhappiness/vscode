    if (path == NULL)
        return HTTP_BAD_REQUEST;

    r->filename = apr_pstrcat(r->pool, "proxy:fcgi://", host, sport, "/",
                              path, NULL);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "proxy: FCGI: set r->filename to %s", r->filename);

    r->path_info = apr_pstrcat(r->pool, "/", path, NULL);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "proxy: FCGI: set r->path_info to %s", r->path_info);

    return OK;
}

/*
 * Fill in a fastcgi request header with the following type, request id,
