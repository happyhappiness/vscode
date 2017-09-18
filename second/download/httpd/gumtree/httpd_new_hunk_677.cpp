    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: serving URL %s", url);

    /* create space for state information */
    backend = (proxy_conn_rec *) ap_get_module_config(c->conn_config, &proxy_ftp_module);
    if (!backend) {
        backend = apr_pcalloc(c->pool, sizeof(proxy_conn_rec));
        backend->connection = NULL;
        backend->hostname = NULL;
        backend->port = 0;
        ap_set_module_config(c->conn_config, &proxy_ftp_module, backend);
    }
    if (backend->connection)
