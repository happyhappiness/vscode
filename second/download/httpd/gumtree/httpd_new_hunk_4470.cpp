                             apr_atomic_read32(&connection_count),
                             apr_atomic_read32(&clogged_count),
                             *write_completion_q->total,
                             *keepalive_q->total,
                             apr_atomic_read32(&lingering_count),
                             apr_atomic_read32(&suspended_count));
                if (dying) {
                    ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
                                 "%u/%u workers shutdown",
                                 apr_atomic_read32(&threads_shutdown),
                                 threads_per_child);
                }
                apr_thread_mutex_unlock(timeout_mutex);
            }
        }

        apr_thread_mutex_lock(g_timer_skiplist_mtx);
        te = apr_skiplist_peek(timer_skiplist);
