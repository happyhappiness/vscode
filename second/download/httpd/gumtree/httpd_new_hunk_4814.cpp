                        disable_listensocks(process_slot);
                    listeners_disabled = 1;
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 "All workers busy, not accepting new conns"
                                 "in this process");
                }
                else if (  (int)apr_atomic_read32(&connection_count)
                           - (int)apr_atomic_read32(&lingering_count)
                         > threads_per_child
                           + ap_queue_info_get_idlers(worker_queue_info) *
                             worker_factor / WORKER_FACTOR_SCALE)
                {
                    if (!listeners_disabled)
                        disable_listensocks(process_slot);
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 "Too many open connections (%u), "
                                 "not accepting new conns in this process",
