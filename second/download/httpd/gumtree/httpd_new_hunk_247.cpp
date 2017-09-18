        return HTTP_INTERNAL_SERVER_ERROR;
#endif                          /* _OSD_POSIX */
    }

    /* Set a timeout on the socket */
    if (conf->timeout_set == 1) {
        apr_setsocketopt(sock, APR_SO_TIMEOUT, (int)conf->timeout);
    }
    else {
        apr_setsocketopt(sock, 
                         APR_SO_TIMEOUT, (int)r->server->timeout);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: socket has been created");


    /*
     * At this point we have a list of one or more IP addresses of the
     * machine to connect to. If configured, reorder this list so that the
