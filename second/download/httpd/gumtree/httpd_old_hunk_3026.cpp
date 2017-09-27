    }

    /* Use old naming */
    origin = backend->connection;
    sock = backend->sock;

    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
                 "proxy: FTP: control connection complete");


    /*
     * III: Send Control Request -------------------------
     *
     * Log into the ftp server, send the username & password, change to the
