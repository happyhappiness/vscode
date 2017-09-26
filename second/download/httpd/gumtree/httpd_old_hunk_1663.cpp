    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: connected %s to %s:%d", *url, conn->hostname,
                 conn->port);
    return OK;
}

static int is_socket_connected(apr_socket_t *sock)

{
    apr_size_t buffer_len = 1;
    char test_buffer[1];
    apr_status_t socket_status;
