    }

    /* are we connecting directly, or via a proxy? */
    if (proxyname) {
        connectname = proxyname;
        connectport = proxyport;
        err = apr_sockaddr_info_get(&connect_addr, proxyname, APR_UNSPEC,
                                    proxyport, 0, p);
    }
    else {
        connectname = uri.hostname;
        connectport = uri.port;
        connect_addr = uri_addr;
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: CONNECT: connecting to remote proxy %s on port %d",
                 connectname, connectport);

    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, uri_addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }

    /* Check if it is an allowed port */
    if(!allowed_port(c_conf, uri.port)) {
              return ap_proxyerror(r, HTTP_FORBIDDEN,
                                   "Connect to remote machine blocked");
    }

    /*
     * Step Two: Make the Connection
     *
     * We have determined who to connect to. Now make the connection.
