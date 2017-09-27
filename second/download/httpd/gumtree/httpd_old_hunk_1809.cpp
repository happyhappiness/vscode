        /* expected cause is that the client disconnected already,
         * hence the debug level
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
                      "apr_socket_opt_set(APR_TCP_NODELAY)");
    }
#endif

    /* The core filter requires the timeout mode to be set, which
     * incidentally sets the socket to be nonblocking.  If this
     * is not initialized correctly, Linux - for example - will
     * be initially blocking, while Solaris will be non blocking
     * and any initial read will fail.
