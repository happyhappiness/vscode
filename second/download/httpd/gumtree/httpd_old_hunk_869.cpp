        for (lr = ap_listeners; lr; lr = lr->next) {
            apr_status_t status;

            status = apr_socket_opt_set(lr->sd, APR_SO_NONBLOCK, 1);
            if (status != APR_SUCCESS) {
                ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, status, pool,
                              "ap_listen_open: unable to make socket non-blocking");
                return -1;
            }
        }
    }
#endif /* AP_NONBLOCK_WHEN_MULTI_LISTEN */

