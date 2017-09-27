    void *sconf = s->module_config;
    proxy_server_conf *conf =
        (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    if (conn->sock) {
        if (!(connected = is_socket_connected(conn->sock))) {
            socket_cleanup(conn);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00951)
                         "%s: backend socket is disconnected.",
                         proxy_function);
        }
    }
    while ((backend_addr || conn->uds_path) && !connected) {
#if APR_HAVE_SYS_UN_H
        if (conn->uds_path)
        {
