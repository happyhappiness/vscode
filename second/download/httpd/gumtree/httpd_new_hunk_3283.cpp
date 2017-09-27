        return NULL;
    }

    if ((status = apr_sockaddr_info_get(&sa, addr, APR_UNSPEC, port, 0,
                                        process->pool))
        != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, status, process->pool, APLOGNO(00077)
                      "alloc_listener: failed to set up sockaddr for %s",
                      addr);
        return "Listen setup failed";
    }

    /* Initialize to our last configured ap_listener. */
