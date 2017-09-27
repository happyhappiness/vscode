            apr_thread_mutex_lock(timeout_mutex);

            /* Step 1: keepalive timeouts */
            /* If all workers are busy, we kill older keep-alive connections so that they
             * may connect to another process.
             */
            if ((workers_were_busy || dying) && *keepalive_q->total) {
                if (!dying)
                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
                                 "All workers are busy, will close %d keep-alive "
                                 "connections",
                                 *keepalive_q->total);
                process_timeout_queue(keepalive_q, 0,
                                      start_lingering_close_nonblocking);
            }
            else {
                process_timeout_queue(keepalive_q, timeout_time,
                                      start_lingering_close_nonblocking);
