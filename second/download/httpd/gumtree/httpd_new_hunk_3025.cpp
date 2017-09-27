     *
     * We have determined who to connect to. Now make the connection.
     */


    if (ap_proxy_connect_backend("FTP", backend, worker, r->server)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01039)
                      "an error occurred creating a new connection to %pI (%s)",
                      connect_addr, connectname);
        proxy_ftp_cleanup(r, backend);
        return HTTP_SERVICE_UNAVAILABLE;
    }

    if (!backend->connection) {
        status = ap_proxy_connection_create("FTP", backend, c, r->server);
