                /* A Listener Socket is ready for an accept() */
                if (workers_were_busy) {
                    if (!listeners_disabled)
                        disable_listensocks(process_slot);
                    listeners_disabled = 1;
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 "All workers busy, not accepting new conns "
                                 "in this process");
                }
                else if (  (int)apr_atomic_read32(&connection_count)
                           - (int)apr_atomic_read32(&lingering_count)
                         > threads_per_child
                           + ap_queue_info_get_idlers(worker_queue_info) *
