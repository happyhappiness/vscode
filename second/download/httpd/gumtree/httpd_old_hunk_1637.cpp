    ajp_msg_t *msg;
    apr_size_t bufsiz;
    char *buff;
    apr_uint16_t size;
    const char *tenc;
    int havebody = 1;
    int isok = 1;
    apr_off_t bb_len;
    int data_sent = 0;
    int rv = 0;
    apr_int32_t conn_poll_fd;
    apr_pollfd_t *conn_poll;

    /*
     * Send the AJP request to the remote server
     */

    /* send request headers */
    status = ajp_send_header(conn->sock, r, uri);
    if (status != APR_SUCCESS) {
        conn->close++;
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: AJP: request failed to %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
