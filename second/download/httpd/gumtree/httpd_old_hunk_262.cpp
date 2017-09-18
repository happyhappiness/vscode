    if (backend->connection) {
        client_socket = ap_get_module_config(backend->connection->conn_config, &core_module);
        if ((backend->connection->id == c->id) &&
            (backend->port == p_conn->port) &&
            (backend->hostname) &&
            (!apr_strnatcasecmp(backend->hostname, p_conn->name))) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                         "proxy: keepalive address match (keep original socket)");
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                         "proxy: keepalive address mismatch / connection has"
                         " changed (close old socket (%s/%s, %d/%d))", 
                         p_conn->name, backend->hostname, p_conn->port,
                         backend->port);
            apr_socket_close(client_socket);
            backend->connection = NULL;
