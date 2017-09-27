 * def_port is the default port for this scheme.
 */
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

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                 "canonicalising URL %s", url);

    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01059)
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }
