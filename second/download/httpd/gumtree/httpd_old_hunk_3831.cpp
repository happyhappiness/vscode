    }

#if APR_TCP_NODELAY_INHERITED
    ap_sock_disable_nagle(s);
#endif

    if ((stat = apr_socket_bind(s, server->bind_addr)) != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, stat, p, APLOGNO(00072)
                      "make_sock: could not bind to address %pI",
                      server->bind_addr);
        apr_socket_close(s);
        return stat;
