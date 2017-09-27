    apr_signal(SIGPIPE, SIG_IGN);
#endif /* SIGPIPE */

#endif
}

static int start_lingering_close_common(event_conn_state_t *cs)
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
    apr_atomic_inc32(&lingering_count);
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
    return 1;
}

/*
 * Close our side of the connection, flushing data to the client first.
 * Pre-condition: cs is not in any timeout queue and not in the pollset,
 *                timeout_mutex is not locked
 * return: 0 if connection is fully closed,
 *         1 if connection is lingering
 * May only be called by worker thread.
 */
static int start_lingering_close_blocking(event_conn_state_t *cs)
{
    if (ap_start_lingering_close(cs->c)) {
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    return start_lingering_close_common(cs);
}

/*
 * Close our side of the connection, NOT flushing data to the client.
 * This should only be called if there has been an error or if we know
 * that our send buffers are empty.
 * Pre-condition: cs is not in any timeout queue and not in the pollset,
 *                timeout_mutex is not locked
 * return: 0 if connection is fully closed,
 *         1 if connection is lingering
 * may be called by listener thread
 */
static int start_lingering_close_nonblocking(event_conn_state_t *cs)
{
    conn_rec *c = cs->c;
    apr_socket_t *csd = cs->pfd.desc.s;

    if (c->aborted
        || apr_socket_shutdown(csd, APR_SHUTDOWN_WRITE) != APR_SUCCESS) {
        apr_socket_close(csd);
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    return start_lingering_close_common(cs);
}

/*
 * forcibly close a lingering connection after the lingering period has
 * expired
 * Pre-condition: cs is not in any timeout queue and not in the pollset
