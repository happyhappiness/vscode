        /* The event needs to be removed from the accepted socket,
         * if not removed from the listen socket prior to accept(),
         */
        rv = WSAEventSelect(nlsd, events[2], FD_ACCEPT);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_ERR,
                         apr_get_netos_error(), ap_server_conf, APLOGNO(00333)
                         "WSAEventSelect() failed.");
            CloseHandle(events[2]);
            return 1;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00334)
                 "Child: Accept thread listening on %s:%d using AcceptFilter %s",
                 lr->bind_addr->hostname ? lr->bind_addr->hostname : "*",
                 lr->bind_addr->port, accf_name);

    while (!shutdown_in_progress) {
        if (!context) {
            int timeout;

            context = mpm_get_completion_context(&timeout);
            if (!context) {
                if (!timeout) {
                    /* Hopefully a temporary condition in the provider? */
                    ++err_count;
                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(00335)
                                     "winnt_accept: Too many failures grabbing a "
                                     "connection ctx.  Aborting.");
                        break;
                    }
                }
                Sleep(100);
                continue;
            }
        }

        if (accf > 0) /* Either 'connect' or 'data' */
