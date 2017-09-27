    apr_int32_t pollcnt, pi;
    apr_int16_t pollevent;
    apr_sockaddr_t *nexthop;

    apr_uri_t uri;
    const char *connectname;
    apr_port_t connectport = 0;

    /* is this for us? */
    if (r->method_number != M_CONNECT) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "declining URL %s", url);
        return DECLINED;
    }
