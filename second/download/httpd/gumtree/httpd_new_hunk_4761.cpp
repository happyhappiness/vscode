                                         NULL));
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01019)
                  "connecting %s to %s:%d", url, uri.hostname, uri.port);

    /* Determine host/port of next hop; from request URI or of a proxy. */
    connectname = proxyname ? proxyname : uri.hostname;
    connectport = proxyname ? proxyport : uri.port;

    /* Do a DNS lookup for the next hop */
    rv = apr_sockaddr_info_get(&nexthop, connectname, APR_UNSPEC, 
                               connectport, 0, p);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO()
                      "failed to resolve hostname '%s'", connectname);
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             apr_pstrcat(p, "DNS lookup failure for: ",
                                         connectname, NULL));
    }

    /* Check ProxyBlock directive on the hostname/address.  */
    if (ap_proxy_checkproxyblock2(r, conf, uri.hostname, 
                                 proxyname ? NULL : nexthop) != OK) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "connecting to remote proxy %s on port %d",
                  connectname, connectport);

    /* Check if it is an allowed port */
    if(!allowed_port(c_conf, uri.port)) {
              return ap_proxyerror(r, HTTP_FORBIDDEN,
                                   "Connect to remote machine blocked");
    }

    /*
     * Step Two: Make the Connection
     *
     * We have determined who to connect to. Now make the connection.
     */

    /*
     * At this point we have a list of one or more IP addresses of
     * the machine to connect to. If configured, reorder this
     * list so that the "best candidate" is first try. "best
     * candidate" could mean the least loaded server, the fastest
     * responding server, whatever.
     *
     * For now we do nothing, ie we get DNS round robin.
     * XXX FIXME
     */
    failed = ap_proxy_connect_to_backend(&sock, "CONNECT", nexthop,
                                         connectname, conf, r);

    /* handle a permanent error from the above loop */
    if (failed) {
        if (proxyname) {
            return DECLINED;
