     *
     * -John Heidemann <johnh@isi.edu> 25-Oct-96
     *
     * If no size is specified, use the kernel default.
     */
    if (send_buffer_size) {
        stat = apr_socket_opt_set(s, APR_SO_SNDBUF,  send_buffer_size);
        if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p,
                          "make_sock: failed to set SendBufferSize for "
                          "address %pI, using default",
                          server->bind_addr);
            /* not a fatal error */
