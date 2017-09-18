                         "ProxyReceiveBufferSize, using default");
        }
#endif

        /* Set a timeout on the socket */
        if (conf->timeout_set == 1) {
            apr_setsocketopt(*newsock, APR_SO_TIMEOUT,
                             (int)(conf->timeout * APR_USEC_PER_SEC));
        }
        else {
            apr_setsocketopt(*newsock, APR_SO_TIMEOUT,
                             (int)(s->timeout * APR_USEC_PER_SEC));
        }

        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, backend_name);

        /* make the connection out of the socket */
        rv = apr_connect(*newsock, backend_addr);

