    if (APR_SUCCESS != apr_uri_parse_hostinfo(p, url, &uri)) {
        return ap_proxyerror(r, HTTP_BAD_REQUEST,
                             apr_pstrcat(p, "URI cannot be parsed: ", url,
                                         NULL));
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01019)
                  "connecting %s to %s:%d", url, uri.hostname, uri.port);

    /* do a DNS lookup for the destination host */
    err = apr_sockaddr_info_get(&uri_addr, uri.hostname, APR_UNSPEC, uri.port,
                                0, p);
    if (APR_SUCCESS != err) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
