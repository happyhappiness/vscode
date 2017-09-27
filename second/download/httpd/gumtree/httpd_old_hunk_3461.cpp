     *
     * In spite of these problems, failure here is not a shooting offense.
     */
    apr_status_t status = apr_socket_opt_set(s, APR_TCP_NODELAY, 1);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, status, ap_server_conf,
                     "apr_socket_opt_set: (TCP_NODELAY)");
    }
}
#endif

#ifdef HAVE_GETPWNAM
