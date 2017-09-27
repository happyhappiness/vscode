    void *sconf = s->module_config;
    proxy_server_conf *conf =
        (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    if (conn->sock) {
        if (!(connected = is_socket_connected(conn->sock))) {
            socket_cleanup(conn);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: %s: backend socket is disconnected.",
                         proxy_function);
        }
    }
    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                SOCK_STREAM, APR_PROTO_TCP,
                                conn->scpool)) != APR_SUCCESS) {
