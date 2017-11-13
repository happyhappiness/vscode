static int proxy_fcgi_canon(request_rec *r, char *url)
{
    char *host, sport[7];
    const char *err, *path;
    apr_port_t port = 8000;

    if (strncasecmp(url, "fcgi:", 5) == 0) {
        url += 5;
    }
    else {
        return DECLINED;
    }
    
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: FCGI: canonicalising URL %s", url);

    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }
        
    apr_snprintf(sport, sizeof(sport), ":%d", port);
        
    if (ap_strchr_c(host, ':')) {
        /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }

    if (apr_table_get(r->notes, "proxy-nocanon")) {
        path = url;   /* this is the raw path */
    }
    else {
        path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
                             r->proxyreq);
    }
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