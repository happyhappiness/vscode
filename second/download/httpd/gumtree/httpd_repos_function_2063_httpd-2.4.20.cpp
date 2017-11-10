static int ftp_set_TYPE(char xfer_type, request_rec *r, conn_rec *ftp_ctrl,
                  apr_bucket_brigade *bb, char **pmessage)
{
    char old_type[2] = { 'A', '\0' }; /* After logon, mode is ASCII */
    int ret = HTTP_OK;
    int rc;

    /* set desired type */
    old_type[0] = xfer_type;

    rc = proxy_ftp_command(apr_pstrcat(r->pool, "TYPE ", old_type, CRLF, NULL),
                           r, ftp_ctrl, bb, pmessage);
/* responses: 200, 421, 500, 501, 504, 530 */
    /* 200 Command okay. */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 504 Command not implemented for that parameter. */
    /* 530 Not logged in. */
    if (rc == -1 || rc == 421) {
        ret = ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             "Error reading from remote server");
    }
    else if (rc != 200 && rc != 504) {
        ret = ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             "Unable to set transfer type");
    }
/* Allow not implemented */
    else if (rc == 504) {
        /* ignore it silently */
    }

    return ret;
}