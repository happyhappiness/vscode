#endif
    apr_status_t stat;

#ifndef WIN32
    stat = apr_socket_opt_set(s, APR_SO_REUSEADDR, one);
    if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p,
                      "make_sock: for address %pI, apr_socket_opt_set: (SO_REUSEADDR)",
                      server->bind_addr);
        apr_socket_close(s);
        return stat;
    }
#endif

    stat = apr_socket_opt_set(s, APR_SO_KEEPALIVE, one);
    if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p,
                      "make_sock: for address %pI, apr_socket_opt_set: (SO_KEEPALIVE)",
                      server->bind_addr);
        apr_socket_close(s);
        return stat;
    }

#if APR_HAVE_IPV6
    if (server->bind_addr->family == APR_INET6) {
        stat = apr_socket_opt_set(s, APR_IPV6_V6ONLY, v6only_setting);
        if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
            ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p,
                          "make_sock: for address %pI, apr_socket_opt_set: "
                          "(IPV6_V6ONLY)",
                          server->bind_addr);
            apr_socket_close(s);
            return stat;
        }
