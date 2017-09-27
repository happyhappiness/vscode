 * Post-condition: timeout_mutex will be locked again
 */
static void process_timeout_queue(struct timeout_queue *q,
                                  apr_time_t timeout_time,
                                  int (*func)(event_conn_state_t *))
{
    int count = 0;
    event_conn_state_t *first, *cs, *last;
    apr_status_t rv;
    if (!q->count) {
        return;
    }
    AP_DEBUG_ASSERT(!APR_RING_EMPTY(&q->head, event_conn_state_t, timeout_list));

    cs = first = APR_RING_FIRST(&q->head);
    while (cs != APR_RING_SENTINEL(&q->head, event_conn_state_t, timeout_list)
           && cs->expiration_time < timeout_time) {
        last = cs;
        rv = apr_pollset_remove(event_pollset, &cs->pfd);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rv)) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, cs->c, APLOGNO(00473)
                          "apr_pollset_remove failed");
        }
        cs = APR_RING_NEXT(cs, timeout_list);
        count++;
    }
    if (!count)
        return;

    APR_RING_UNSPLICE(first, last, timeout_list);
    AP_DEBUG_ASSERT(q->count >= count);
    q->count -= count;
    apr_thread_mutex_unlock(timeout_mutex);
    while (count) {
        cs = APR_RING_NEXT(first, timeout_list);
        TO_QUEUE_ELEM_INIT(first);
        func(first);
        first = cs;
        count--;
    }
    apr_thread_mutex_lock(timeout_mutex);
}

static void * APR_THREAD_FUNC listener_thread(apr_thread_t * thd, void *dummy)
{
    timer_event_t *ep;
