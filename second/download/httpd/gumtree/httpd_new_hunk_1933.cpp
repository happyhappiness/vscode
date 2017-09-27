    } else {
        c->ssl = NULL;
    }
#endif
    if ((rv = apr_socket_connect(c->aprsock, destsa)) != APR_SUCCESS) {
        if (APR_STATUS_IS_EINPROGRESS(rv)) {
            set_conn_state(c, STATE_CONNECTING);
            c->rwrite = 0;
            return;
        }
        else {
            set_conn_state(c, STATE_UNCONNECTED);
            apr_socket_close(c->aprsock);
            err_conn++;
            if (bad++ > 10) {
                fprintf(stderr,
                   "\nTest aborted after 10 failures\n\n");
                apr_err("apr_socket_connect()", rv);
            }
            
            start_connect(c);
            return;
        }
    }

    /* connected first time */
    set_conn_state(c, STATE_CONNECTED);
#ifdef USE_SSL
    if (c->ssl) {
        ssl_proceed_handshake(c);
    } else
#endif
    {
