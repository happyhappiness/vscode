                          "make_sock: failed to set SendBufferSize for "
                          "address %pI, using default",
                          server->bind_addr);
            /* not a fatal error */
        }
    }

#if APR_TCP_NODELAY_INHERITED
    ap_sock_disable_nagle(s);
#endif

    if ((stat = apr_bind(s, server->bind_addr)) != APR_SUCCESS) {
