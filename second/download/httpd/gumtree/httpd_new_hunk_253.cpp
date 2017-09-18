    /* 550 Requested action not taken. */
    if (rc == -1 || rc == 421) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             "Error reading from remote server");
    }
    if (rc == 550) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: RETR failed, trying LIST instead");

        /* Directory Listings should always be fetched in ASCII mode */
        dirlisting = 1;
        ftp_set_TYPE('A', r, origin, bb, NULL);

