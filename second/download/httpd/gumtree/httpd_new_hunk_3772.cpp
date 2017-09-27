        }                   /* while for processing poll */

        /* XXX possible optimization: stash the current time for use as
         * r->request_time for new requests
         */
        now = apr_time_now();
        /* We only do this once per 0.1s (TIMEOUT_FUDGE_FACTOR), or on a clock
         * skew (if the system time is set back in the meantime, timeout_time
         * will exceed now + TIMEOUT_FUDGE_FACTOR, can't happen otherwise).
         */
        if (now > timeout_time || now + TIMEOUT_FUDGE_FACTOR < timeout_time ) {
            struct process_score *ps;
            timeout_time = now + TIMEOUT_FUDGE_FACTOR;

            /* handle timed out sockets */
            apr_thread_mutex_lock(timeout_mutex);

            /* Step 1: keepalive timeouts */
            /* If all workers are busy, we kill older keep-alive connections so that they
             * may connect to another process.
             */
            if (workers_were_busy && *keepalive_q->total) {
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
            }
            /* Step 2: write completion timeouts */
            process_timeout_queue(write_completion_q, timeout_time,
                                  start_lingering_close_nonblocking);
            /* Step 3: (normal) lingering close completion timeouts */
            process_timeout_queue(linger_q, timeout_time, stop_lingering_close);
            /* Step 4: (short) lingering close completion timeouts */
            process_timeout_queue(short_linger_q, timeout_time, stop_lingering_close);

            ps = ap_get_scoreboard_process(process_slot);
            ps->write_completion = *write_completion_q->total;
            ps->keep_alive = *keepalive_q->total;
            apr_thread_mutex_unlock(timeout_mutex);

            ps->connections = apr_atomic_read32(&connection_count);
            ps->suspended = apr_atomic_read32(&suspended_count);
            ps->lingering_close = apr_atomic_read32(&lingering_count);
        }
