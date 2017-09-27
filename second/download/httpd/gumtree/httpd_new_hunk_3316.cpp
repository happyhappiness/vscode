                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "ap_queue_pop failed");
            }
            continue;
        }
        if (te != NULL) {
            te->cbfunc(te->baton);

            {
                apr_thread_mutex_lock(g_timer_ring_mtx);
                APR_RING_INSERT_TAIL(&timer_free_ring, te, timer_event_t, link);
                apr_thread_mutex_unlock(g_timer_ring_mtx);
