                     * socket to a worker 
                     */
                    apr_socket_close(csd);
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                                 "ap_queue_push failed");
                }
                else {
                    have_idle_worker = 0;
                }
            }
        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
