                     * automagically remove the FD if the socket is closed,
                     * therefore, we can accept _SUCCESS or _NOTFOUND,
                     * and we still want to keep going
                     */
                    if (rc != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rc)) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                                     APLOGNO(03094) "pollset remove failed");
                        start_lingering_close_nonblocking(cs);
                        break;
                    }

                    TO_QUEUE_ELEM_INIT(cs);
                    /* If we didn't get a worker immediately for a keep-alive
