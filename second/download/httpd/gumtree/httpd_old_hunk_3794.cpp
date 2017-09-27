    i = 0;
    memset(buffer, '\0', sizeof(buffer));
    /*
     * Note that the strchr function below checks for \012 instead of '\n'
     * this allows it to work on both ASCII and EBCDIC machines.
     */
    while((cp = strchr(buffer, '\012')) == NULL && i < sizeof(buffer) - 1) {
        apr_size_t j = sizeof(buffer) - 1 - i;
        apr_status_t status;
        status = apr_socket_recv(sock, buffer+i, &j);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, status, srv, APLOGNO(01498)
                         "read: rfc1413: error reading response");
