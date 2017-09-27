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

