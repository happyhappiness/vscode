static int fix_hostname(request_rec *r, const char *host_header,
                        unsigned http_conformance)
{
    const char *src;
    char *host, *scope_id;
    apr_port_t port;
    apr_status_t rv;
    const char *c;
    int is_v6literal = 0;
    int strict = (http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);

    src = host_header ? host_header : r->hostname;

    /* According to RFC 2616, Host header field CAN be blank */
    if (!*src) {
        return is_v6literal;
    }

    /* apr_parse_addr_port will interpret a bare integer as a port
     * which is incorrect in this context.  So treat it separately.
     */
    for (c = src; apr_isdigit(*c); ++c);
    if (!*c) {
        /* pure integer */
        if (strict) {
            /* RFC 3986 7.4 */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                         "[strict] purely numeric host names not allowed: %s",
                         src);
            goto bad_nolog;
        }
        r->hostname = src;
        return is_v6literal;
    }

    if (host_header) {
        rv = apr_parse_addr_port(&host, &scope_id, &port, src, r->pool);
        if (rv != APR_SUCCESS || scope_id)
            goto bad;
        if (port) {
            /* Don't throw the Host: header's port number away:
               save it in parsed_uri -- ap_get_server_port() needs it! */
            /* @@@ XXX there should be a better way to pass the port.
             *         Like r->hostname, there should be a r->portno
             */
            r->parsed_uri.port = port;
            r->parsed_uri.port_str = apr_itoa(r->pool, (int)port);
        }
        if (host_header[0] == '[')
            is_v6literal = 1;
    }
    else {
        /*
         * Already parsed, surrounding [ ] (if IPv6 literal) and :port have
         * already been removed.
         */
        host = apr_pstrdup(r->pool, r->hostname);
        if (ap_strchr(host, ':') != NULL)
            is_v6literal = 1;
    }

    if (is_v6literal) {
        rv = fix_hostname_v6_literal(r, host);
    }
    else {
        rv = fix_hostname_non_v6(r, host);
        if (strict && rv == APR_SUCCESS)
            rv = strict_hostname_check(r, host);
    }
    if (rv != APR_SUCCESS)
        goto bad;

    r->hostname = host;
    return is_v6literal;

bad:
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "Client sent malformed Host header: %s",
                  src);
bad_nolog:
    r->status = HTTP_BAD_REQUEST;
    return is_v6literal;
}