                                SOCK_STREAM, conn->pool)) != APR_SUCCESS) {
	ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
                     "rfc1413: error creating query socket");
        return rv;
    }

    if ((rv = apr_setsocketopt(*newsock, APR_SO_TIMEOUT, 
                               (apr_int32_t)(ap_rfc1413_timeout 
                                              * APR_USEC_PER_SEC)))
        != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
                     "rfc1413: error setting query socket timeout");
        apr_socket_close(*newsock);
        return rv;
    }

