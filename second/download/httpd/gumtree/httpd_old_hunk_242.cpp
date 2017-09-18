    int eos;

    if (APR_SUCCESS != (rv = ap_proxy_string_read(ftp_ctrl, bb, response, sizeof(response), &eos))) {
        return -1;
    }
/*
    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, NULL,
                 "proxy: <FTP: %s", response);
*/
    if (!apr_isdigit(response[0]) || !apr_isdigit(response[1]) ||
    !apr_isdigit(response[2]) || (response[3] != ' ' && response[3] != '-'))
        status = 0;
    else
