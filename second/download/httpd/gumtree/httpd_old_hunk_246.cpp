    }
    else {
        user = "anonymous";
        password = "apache-proxy@";
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
       "proxy: FTP: connecting %s to %s:%d", url, connectname, connectport);

    /* do a DNS lookup for the destination host */
    err = apr_sockaddr_info_get(&connect_addr, connectname, APR_UNSPEC, connectport, 0, p);

    /* check if ProxyBlock directive on this host */
