 * Canonicalize scgi-like URLs.
 */
static int scgi_canon(request_rec *r, char *url)
{
    char *host, sport[sizeof(":65535")];
    const char *err, *path;
    apr_port_t port, def_port;

    if (strncasecmp(url, SCHEME "://", sizeof(SCHEME) + 2)) {
        return DECLINED;
    }
    url += sizeof(SCHEME); /* Keep slashes */

    port = def_port = SCGI_DEF_PORT;

    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00857)
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }

    if (port != def_port) {
        apr_snprintf(sport, sizeof(sport), ":%u", port);
    }
    else {
        sport[0] = '\0';
    }

    if (ap_strchr(host, ':')) { /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }

    path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
