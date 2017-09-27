        else {
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }

    /* setup polling for connection */
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "setting up poll()");

    if ((rv = apr_pollset_create(&pollset, 2, r->pool, 0)) != APR_SUCCESS) {
        apr_socket_close(sock);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01020)
                      "error apr_pollset_create()");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Add client side to the poll */
    pollfd.p = r->pool;
    pollfd.desc_type = APR_POLL_SOCKET;
