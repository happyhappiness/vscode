                                    r->connection->sbh, c->bucket_alloc);
    if (!data) {
        /*
         * the peer reset the connection already; ap_run_create_connection() closed
         * the socket
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
          "proxy: FTP: an error occurred creating the transfer connection");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* set up the connection filters */
    ap_run_pre_connection(data, data_sock);
