     * Send the AJP request to the remote server
     */

    /* send request headers */
    status = ajp_send_header(conn->sock, r, maxsize, uri);
    if (status != APR_SUCCESS) {
        conn->close = 1;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00868)
                      "request failed to %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->s->hostname);
        if (status == AJP_EOVERFLOW)
            return HTTP_BAD_REQUEST;
