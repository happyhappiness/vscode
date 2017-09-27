     *
     * Log into the ftp server, send the username & password, change to the
     * correct directory...
     */

    /* set up the connection filters */
    ap_run_pre_connection(origin, sock);

    /* possible results: */
    /* 120 Service ready in nnn minutes. */
    /* 220 Service ready for new user. */
    /* 421 Service not available, closing control connection. */
    rc = proxy_ftp_command(NULL, r, origin, bb, &ftpmessage);
