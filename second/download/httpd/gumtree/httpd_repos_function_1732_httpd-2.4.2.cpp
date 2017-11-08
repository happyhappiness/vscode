static int proxy_balancer_canon(request_rec *r, char *url)
{
    char *host, *path;
    char *search = NULL;
    const char *err;
    apr_port_t port = 0;

    /* TODO: offset of BALANCER_PREFIX ?? */
    if (strncasecmp(url, "balancer:", 9) == 0) {
        url += 9;
    }
    else {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);

    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01157)
                      "error parsing URL %s: %s",
                      url, err);
        return HTTP_BAD_REQUEST;
    }
    /*
     * now parse path/search args, according to rfc1738:
     * process the path. With proxy-noncanon set (by
     * mod_proxy) we use the raw, unparsed uri
     */
    if (apr_table_get(r->notes, "proxy-nocanon")) {
        path = url;   /* this is the raw path */
    }
    else {
        path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
                                 r->proxyreq);
        search = r->args;
    }
    if (path == NULL)
        return HTTP_BAD_REQUEST;

    r->filename = apr_pstrcat(r->pool, "proxy:", BALANCER_PREFIX, host,
            "/", path, (search) ? "?" : "", (search) ? search : "", NULL);

    r->path_info = apr_pstrcat(r->pool, "/", path, NULL);

    return OK;
}