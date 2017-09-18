                ret = apr_poll(pollset, num_listensocks, &n, -1);
                if (ret != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(ret)) {
                        continue;
                    }

                    /* apr_pollset_poll() will only return errors in catastrophic
                     * circumstances. Let's try exiting gracefully, for now. */
                    ap_log_error(APLOG_MARK, APLOG_ERR, ret, (const server_rec *)
                                 ap_server_conf, "apr_poll: (listen)");
                    signal_threads(ST_GRACEFUL);
                }

