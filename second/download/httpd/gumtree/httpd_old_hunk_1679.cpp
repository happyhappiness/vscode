    }

    /* are we connecting directly, or via a proxy? */
    if (proxyname) {
        connectname = proxyname;
        connectport = proxyport;
        err = apr_sockaddr_info_get(&connect_addr, proxyname, APR_UNSPEC, proxyport, 0, p);
    }
    else {
        connectname = uri.hostname;
        connectport = uri.port;
        connect_addr = uri_addr;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
         "proxy: CONNECT: connecting to remote proxy %s on port %d", connectname, connectport);
 
    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, uri_addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }

    /* Check if it is an allowed port */
    if (conf->allowed_connect_ports->nelts == 0) {
    /* Default setting if not overridden by AllowCONNECT */
        switch (uri.port) {
            case APR_URI_HTTPS_DEFAULT_PORT:
            case APR_URI_SNEWS_DEFAULT_PORT:
                break;
            default:
                /* XXX can we call ap_proxyerror() here to get a nice log message? */
                return HTTP_FORBIDDEN;
        }
    } else if(!allowed_port(conf, uri.port)) {
        /* XXX can we call ap_proxyerror() here to get a nice log message? */
        return HTTP_FORBIDDEN;
    }

    /*
     * Step Two: Make the Connection
     *
     * We have determined who to connect to. Now make the connection.
