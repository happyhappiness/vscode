            backend_addr = backend_addr->next;
            continue;
        }

#if !defined(TPF) && !defined(BEOS)
        if (conf->recv_buffer_size > 0 &&
            (rv = apr_setsocketopt(*newsock, APR_SO_RCVBUF,
                                   conf->recv_buffer_size))) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "setsockopt(SO_RCVBUF): Failed to set "
                         "ProxyReceiveBufferSize, using default");
        }
#endif

        /* Set a timeout on the socket */
        if (conf->timeout_set == 1) {
            apr_setsocketopt(*newsock, APR_SO_TIMEOUT, (int)conf->timeout);
        }
        else {
            apr_setsocketopt(*newsock, APR_SO_TIMEOUT, (int)s->timeout);
        }

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, backend_name);

