static int
proxy_ftp_command(const char *cmd, request_rec *r, conn_rec *ftp_ctrl,
                  apr_bucket_brigade *bb, char **pmessage)
{
    char *crlf;
    int rc;
    char message[HUGE_STRING_LEN];

    /* If cmd == NULL, we retrieve the next ftp response line */
    if (cmd != NULL) {
        conn_rec *c = r->connection;
        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(cmd, strlen(cmd), r->pool, c->bucket_alloc));
        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_flush_create(c->bucket_alloc));
        ap_pass_brigade(ftp_ctrl->output_filters, bb);

        /* strip off the CRLF for logging */
        apr_cpystrn(message, cmd, sizeof(message));
        if ((crlf = strchr(message, '\r')) != NULL ||
            (crlf = strchr(message, '\n')) != NULL)
            *crlf = '\0';
        if (strncmp(message,"PASS ", 5) == 0)
            strcpy(&message[5], "****");
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                     "proxy:>FTP: %s", message);
    }

    rc = ftp_getrc_msg(ftp_ctrl, bb, message, sizeof message);
    if (rc == -1 || rc == 421)
        strcpy(message,"<unable to read result>");
    if ((crlf = strchr(message, '\r')) != NULL ||
        (crlf = strchr(message, '\n')) != NULL)
        *crlf = '\0';
    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                 "proxy:<FTP: %3.3u %s", rc, message);

    if (pmessage != NULL)
        *pmessage = apr_pstrdup(r->pool, message);

    return rc;
}