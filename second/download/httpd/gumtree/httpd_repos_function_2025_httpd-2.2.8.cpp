static void fix_hostname(request_rec *r)
{
    char *host, *scope_id;
    char *dst;
    apr_port_t port;
    apr_status_t rv;

    /* According to RFC 2616, Host header field CAN be blank. */
    if (!*r->hostname) {
        return;
    }

    rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
    if (rv != APR_SUCCESS || scope_id) {
        goto bad;
    }

    if (!host && port) {
        /* silly looking host ("Host: 123") but that isn't our job
         * here to judge; apr_parse_addr_port() would think we had a port
         * but no address
         */
        host = apr_itoa(r->pool, (int)port);
    }
    else if (port) {
        /* Don't throw the Host: header's port number away:
           save it in parsed_uri -- ap_get_server_port() needs it! */
        /* @@@ XXX there should be a better way to pass the port.
         *         Like r->hostname, there should be a r->portno
         */
        r->parsed_uri.port = port;
        r->parsed_uri.port_str = apr_itoa(r->pool, (int)port);
    }

    /* if the hostname is an IPv6 numeric address string, it was validated
     * already; otherwise, further validation is needed
     */
    if (r->hostname[0] != '[') {
        for (dst = host; *dst; dst++) {
            if (apr_islower(*dst)) {
                /* leave char unchanged */
            }
            else if (*dst == '.') {
                if (*(dst + 1) == '.') {
                    goto bad;
                }
            }
            else if (apr_isupper(*dst)) {
                *dst = apr_tolower(*dst);
            }
            else if (*dst == '/' || *dst == '\\') {
                goto bad;
            }
        }
        /* strip trailing gubbins */
        if (dst > host && dst[-1] == '.') {
            dst[-1] = '\0';
        }
    }
    r->hostname = host;
    return;

bad:
    r->status = HTTP_BAD_REQUEST;
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Client sent malformed Host header");
    return;
}