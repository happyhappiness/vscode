    }

    /* Use old naming */
    origin = backend->connection;
    sock = backend->sock;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: control connection complete");


    /*
     * III: Send Control Request -------------------------
     *
