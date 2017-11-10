static int scgi_canon(request_rec *r, char *url)
{
    char *host, sport[sizeof(":65535")];
    const char *err, *path;
    apr_port_t port = SCGI_DEFAULT_PORT;

    if (strncasecmp(url, SCHEME "://", sizeof(SCHEME) + 2)) {
        return DECLINED;
    }
    url += sizeof(SCHEME); /* Keep slashes */

    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }
        
    apr_snprintf(sport, sizeof(sport), ":%u", port);
        
    if (ap_strchr(host, ':')) { /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }

    path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
                             r->proxyreq);
    if (!path) {
        return HTTP_BAD_REQUEST;
    }

    r->filename = apr_pstrcat(r->pool, "proxy:" SCHEME "://", host, sport, "/",
                              path, NULL);
    r->path_info = apr_pstrcat(r->pool, "/", path, NULL);
    return OK;
}