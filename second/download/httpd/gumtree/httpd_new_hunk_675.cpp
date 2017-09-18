        (crlf = strchr(message, '\n')) != NULL)
        *crlf = '\0';
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy:<FTP: %3.3u %s", rc, message);

    if (pmessage != NULL)
        *pmessage = apr_pstrdup(r->pool, message);

    return rc;
}

/* Set ftp server to TYPE {A,I,E} before transfer of a directory or file */
static int ftp_set_TYPE(char xfer_type, request_rec *r, conn_rec *ftp_ctrl,
