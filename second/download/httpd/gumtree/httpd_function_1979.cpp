static int proxy_ftp_canon(request_rec *r, char *url)
{
    char *user, *password, *host, *path, *parms, *strp, sport[7];
    apr_pool_t *p = r->pool;
    const char *err;
    apr_port_t port, def_port;

    /* */
    if (strncasecmp(url, "ftp:", 4) == 0) {
        url += 4;
    }
    else {
        return DECLINED;
    }
    def_port = apr_uri_port_of_scheme("ftp");

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: canonicalising URL %s", url);

    port = def_port;
    err = ap_proxy_canon_netloc(p, &url, &user, &password, &host, &port);
    if (err)
        return HTTP_BAD_REQUEST;
    if (user != NULL && !ftp_check_string(user))
        return HTTP_BAD_REQUEST;
    if (password != NULL && !ftp_check_string(password))
        return HTTP_BAD_REQUEST;

    /* now parse path/parameters args, according to rfc1738 */
    /*
     * N.B. if this isn't a true proxy request, then the URL path (but not
     * query args) has already been decoded. This gives rise to the problem
     * of a ; being decoded into the path.
     */
    strp = strchr(url, ';');
    if (strp != NULL) {
        *(strp++) = '\0';
        parms = ap_proxy_canonenc(p, strp, strlen(strp), enc_parm, 0,
                                  r->proxyreq);
        if (parms == NULL)
            return HTTP_BAD_REQUEST;
    }
    else
        parms = "";

    path = ap_proxy_canonenc(p, url, strlen(url), enc_path, 0, r->proxyreq);
    if (path == NULL)
        return HTTP_BAD_REQUEST;
    if (!ftp_check_string(path))
        return HTTP_BAD_REQUEST;

    if (r->proxyreq && r->args != NULL) {
        if (strp != NULL) {
            strp = ap_proxy_canonenc(p, r->args, strlen(r->args), enc_parm, 1, r->proxyreq);
            if (strp == NULL)
                return HTTP_BAD_REQUEST;
            parms = apr_pstrcat(p, parms, "?", strp, NULL);
        }
        else {
            strp = ap_proxy_canonenc(p, r->args, strlen(r->args), enc_fpath, 1, r->proxyreq);
            if (strp == NULL)
                return HTTP_BAD_REQUEST;
            path = apr_pstrcat(p, path, "?", strp, NULL);
        }
        r->args = NULL;
    }

/* now, rebuild URL */

    if (port != def_port)
        apr_snprintf(sport, sizeof(sport), ":%d", port);
    else
        sport[0] = '\0';

    if (ap_strchr_c(host, ':')) { /* if literal IPv6 address */
        host = apr_pstrcat(p, "[", host, "]", NULL);
    }
    r->filename = apr_pstrcat(p, "proxy:ftp://", (user != NULL) ? user : "",
                              (password != NULL) ? ":" : "",
                              (password != NULL) ? password : "",
                          (user != NULL) ? "@" : "", host, sport, "/", path,
                              (parms[0] != '\0') ? ";" : "", parms, NULL);

    return OK;
}