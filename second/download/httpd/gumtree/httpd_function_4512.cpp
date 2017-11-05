static int start_lingering_close(event_conn_state_t *cs)
{
    apr_status_t rv;

    cs->c->sbh = NULL;  /* prevent scoreboard updates from the listener 
                         * worker will loop around and set SERVER_READY soon
                         */

    if (ap_start_lingering_close(cs->c)) {
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    else {
        apr_socket_t *csd = ap_get_conn_socket(cs->c);
        struct timeout_queue *q;

#ifdef AP_DEBUG
        {
            rv = apr_socket_timeout_set(csd, 0);
            AP_DEBUG_ASSERT(rv == APR_SUCCESS);
        }
#else
        apr_socket_timeout_set(csd, 0);
#endif
        /*
         * If some module requested a shortened waiting period, only wait for
         * 2s (SECONDS_TO_LINGER). This is useful for mitigating certain
         * DoS attacks.
         */
        if (apr_table_get(cs->c->notes, "short-lingering-close")) {
            cs->expiration_time =
                apr_time_now() + apr_time_from_sec(SECONDS_TO_LINGER);
            q = &short_linger_q;
            cs->pub.state = CONN_STATE_LINGER_SHORT;
        }
        else {
            cs->expiration_time =
                apr_time_now() + apr_time_from_sec(MAX_SECS_TO_LINGER);
            q = &linger_q;
            cs->pub.state = CONN_STATE_LINGER_NORMAL;
        }
        apr_thread_mutex_lock(timeout_mutex);
        TO_QUEUE_APPEND(*q, cs);
        cs->pfd.reqevents = APR_POLLIN | APR_POLLHUP | APR_POLLERR;
        rv = apr_pollset_add(event_pollset, &cs->pfd);
        apr_thread_mutex_unlock(timeout_mutex);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_EEXIST(rv)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                         "start_lingering_close: apr_pollset_add failure");
            apr_thread_mutex_lock(timeout_mutex);
            TO_QUEUE_REMOVE(*q, cs);
            apr_thread_mutex_unlock(timeout_mutex);
            apr_socket_close(cs->pfd.desc.s);
            apr_pool_clear(cs->p);
            ap_push_pool(worker_queue_info, cs->p);
            return 0;
        }
    }
    return 1;
}