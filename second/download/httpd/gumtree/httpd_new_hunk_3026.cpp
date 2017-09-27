    }

    /* Use old naming */
    origin = backend->connection;
    sock = backend->sock;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "control connection complete");


    /*
     * III: Send Control Request -------------------------
     *
     * Log into the ftp server, send the username & password, change to the
