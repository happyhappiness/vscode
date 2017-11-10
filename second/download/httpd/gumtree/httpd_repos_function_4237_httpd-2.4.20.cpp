static void process_lingering_close(event_conn_state_t *cs, const apr_pollfd_t *pfd)
{
    apr_socket_t *csd = ap_get_conn_socket(cs->c);
    char dummybuf[2048];
    apr_size_t nbytes;
    apr_status_t rv;
    struct timeout_queue *q;
    q = (cs->pub.state == CONN_STATE_LINGER_SHORT) ? short_linger_q : linger_q;

    /* socket is already in non-blocking state */
    do {
        nbytes = sizeof(dummybuf);
        rv = apr_socket_recv(csd, dummybuf, &nbytes);
    } while (rv == APR_SUCCESS);

    if (APR_STATUS_IS_EAGAIN(rv)) {
        return;
    }

    apr_thread_mutex_lock(timeout_mutex);
    rv = apr_pollset_remove(event_pollset, pfd);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    rv = apr_socket_close(csd);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    TO_QUEUE_REMOVE(q, cs);
    apr_thread_mutex_unlock(timeout_mutex);
    TO_QUEUE_ELEM_INIT(cs);

    ap_push_pool(worker_queue_info, cs->p);
}