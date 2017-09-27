     */
    while((cp = strchr(buffer, '\012')) == NULL && i < sizeof(buffer) - 1) {
        apr_size_t j = sizeof(buffer) - 1 - i;
        apr_status_t status;
        status = apr_socket_recv(sock, buffer+i, &j);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, status, srv,
                         "read: rfc1413: error reading response");
            return status;
        }
        else if (j > 0) {
            i+=j;
        }
