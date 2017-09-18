                                      r->connection->sbh, c->bucket_alloc);
    if (!origin) {
        /*
         * the peer reset the connection already; ap_run_create_connection() closed
         * the socket
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: an error occurred creating a new connection to %pI (%s)", connect_addr, connectname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* if a keepalive connection is floating around, close it first! */
    /* we might support ftp keepalives later, but not now... */
    if (backend->connection) {
        apr_socket_close(origin_sock);
        backend->connection = NULL;
        origin_sock = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: control connection complete");


    /*
     * III: Send Control Request -------------------------
     *
