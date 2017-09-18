{
    apr_socket_t *s = server->sd;
    int one = 1;
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

    /*
