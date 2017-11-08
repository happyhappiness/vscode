static int is_socket_connected(apr_socket_t *sock)

{
    apr_size_t buffer_len = 1;
    char test_buffer[1];
    apr_status_t socket_status;
    apr_interval_time_t current_timeout;

    /* save timeout */
    apr_socket_timeout_get(sock, &current_timeout);
    /* set no timeout */
    apr_socket_timeout_set(sock, 0);
    socket_status = apr_socket_recv(sock, test_buffer, &buffer_len);
    /* put back old timeout */
    apr_socket_timeout_set(sock, current_timeout);
    if (APR_STATUS_IS_EOF(socket_status)
        || APR_STATUS_IS_ECONNRESET(socket_status)) {
        return 0;
    }
    else {
        return 1;
    }
}