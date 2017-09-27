                rv = ap_queue_push(worker_queue, csd, ptrans);
                if (rv) {
                    /* trash the connection; we couldn't queue the connected
                     * socket to a worker
                     */
                    apr_socket_close(csd);
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(03138)
                                 "ap_queue_push failed");
                }
                else {
                    have_idle_worker = 0;
                }
            }
