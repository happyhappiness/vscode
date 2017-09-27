    /* 550 Requested action not taken. */
    if (rc == -1 || rc == 421) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                              "Error reading from remote server");
    }
    if (rc == 550) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: RETR failed, trying LIST instead");

        /* Directory Listings should always be fetched in ASCII mode */
        dirlisting = 1;
        ftp_set_TYPE('A', r, origin, bb, NULL);

        rc = proxy_ftp_command(apr_pstrcat(p, "CWD ",
                               ftp_escape_globbingchars(p, path), CRLF, NULL),
                               r, origin, bb, &ftpmessage);
        /* possible results: 250, 421, 500, 501, 502, 530, 550 */
        /* 250 Requested file action okay, completed. */
        /* 421 Service not available, closing control connection. */
        /* 500 Syntax error, command unrecognized. */
        /* 501 Syntax error in parameters or arguments. */
