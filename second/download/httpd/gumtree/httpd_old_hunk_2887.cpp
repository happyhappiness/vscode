 * might have more than one network address. The RFC1413 etc.
 * client sends only port numbers; the server takes the IP
 * addresses from the query socket.
 */

    if ((rv = apr_socket_bind(*newsock, localsa)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
                     "rfc1413: Error binding query socket to local port");
        apr_socket_close(*newsock);
        return rv;
    }

/*
