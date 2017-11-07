static int start_lingering_close_common(event_conn_state_t *cs, int in_worker)
{
    apr_status_t rv;
    struct timeout_queue *q;
    apr_socket_t *csd = cs->pfd.desc.s;
#ifdef AP_DEBUG
    {
        rv = apr_socket_timeout_set(csd, 0);
        AP_DEBUG_ASSERT(rv == APR_SUCCESS);
    }
#else
    apr_socket_timeout_set(csd, 0);
#endif
    cs->queue_timestamp = apr_time_now();
    /*
     * If some module requested a shortened waiting period, only wait for
     * 2s (SECONDS_TO_LINGER). This is useful for mitigating certain
     * DoS attacks.
     */
    if (apr_table_get(cs->c->notes, "short-lingering-close")) {
        q = short_linger_q;
        cs->pub.state = CONN_STATE_LINGER_SHORT;
    }
    else {
        q = linger_q;
        cs->pub.state = CONN_STATE_LINGER_NORMAL;
    }
    apr_atomic_inc32(&lingering_count);
    if (in_worker) { 
        notify_suspend(cs);
    }
    else {
        cs->c->sbh = NULL;
    }
    apr_thread_mutex_lock(timeout_mutex);
    TO_QUEUE_APPEND(q, cs);
    cs->pfd.reqevents = (
            cs->pub.sense == CONN_SENSE_WANT_WRITE ? APR_POLLOUT :
                    APR_POLLIN) | APR_POLLHUP | APR_POLLERR;
    cs->pub.sense = CONN_SENSE_DEFAULT;
    rv = apr_pollset_add(event_pollset, &cs->pfd);
    apr_thread_mutex_unlock(timeout_mutex);
    if (rv != APR_SUCCESS && !APR_STATUS_IS_EEXIST(rv)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "start_lingering_close: apr_pollset_add failure");
        apr_thread_mutex_lock(timeout_mutex);
        TO_QUEUE_REMOVE(q, cs);
        apr_thread_mutex_unlock(timeout_mutex);
        apr_socket_close(cs->pfd.desc.s);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    return 1;
}