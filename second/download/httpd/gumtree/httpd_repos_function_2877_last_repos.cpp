static int proxy_http2_canon(request_rec *r, char *url)
{
    char *host, *path, sport[7];
    char *search = NULL;
    const char *err;
    const char *scheme;
    const char *http_scheme;
    apr_port_t port, def_port;

    /* ap_port_of_scheme() */
    if (ap_cstr_casecmpn(url, "h2c:", 4) == 0) {
        url += 4;
        scheme = "h2c";
        http_scheme = "http";
    }
    else if (ap_cstr_casecmpn(url, "h2:", 3) == 0) {
        url += 3;
        scheme = "h2";
        http_scheme = "https";
    }
    else {
        return DECLINED;
    }
    port = def_port = ap_proxy_port_of_scheme(http_scheme);

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "HTTP2: canonicalising URL %s", url);

    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03350)
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }

    /*
     * now parse path/search args, according to rfc1738:
     * process the path.
     *
     * In a reverse proxy, our URL has been processed, so canonicalise
     * unless proxy-nocanon is set to say it's raw
     * In a forward proxy, we have and MUST NOT MANGLE the original.
     */
    switch (r->proxyreq) {
    default: /* wtf are we doing here? */
    case PROXYREQ_REVERSE:
        if (apr_table_get(r->notes, "proxy-nocanon")) {
            path = url;   /* this is the raw path */
        }
        else {
            path = ap_proxy_canonenc(r->pool, url, (int)strlen(url),
                                     enc_path, 0, r->proxyreq);
            search = r->args;
        }
        break;
    case PROXYREQ_PROXY:
        path = url;
        break;
    }

    if (path == NULL) {
        return HTTP_BAD_REQUEST;
    }

    if (port != def_port) {
        apr_snprintf(sport, sizeof(sport), ":%d", port);
    }
    else {
        sport[0] = '\0';
    }

    if (ap_strchr_c(host, ':')) { /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }
    r->filename = apr_pstrcat(r->pool, "proxy:", scheme, "://", host, sport,
            "/", path, (search) ? "?" : "", (search) ? search : "", NULL);
    return OK;
}