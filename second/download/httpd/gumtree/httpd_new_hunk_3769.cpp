 * Post-condition: timeout_mutex will be locked again
 */
static void process_timeout_queue(struct timeout_queue *q,
                                  apr_time_t timeout_time,
                                  int (*func)(event_conn_state_t *))
{
    int total = 0, count;
    event_conn_state_t *first, *cs, *last;
    struct timeout_head_t trash;
    struct timeout_queue *qp;
    apr_status_t rv;

    if (!*q->total) {
        return;
    }

    APR_RING_INIT(&trash, event_conn_state_t, timeout_list);
    for (qp = q; qp; qp = qp->next) {
        count = 0;
        cs = first = last = APR_RING_FIRST(&qp->head);
        while (cs != APR_RING_SENTINEL(&qp->head, event_conn_state_t,
                                       timeout_list)
               /* Trash the entry if:
                * - no timeout_time was given (asked for all), or
                * - it expired (according to the queue timeout), or
                * - the system clock skewed in the past: no entry should be
                *   registered above the given timeout_time (~now) + the queue
                *   timeout, we won't keep any here (eg. for centuries).
                * Stop otherwise, no following entry will match thanks to the
                * single timeout per queue (entries are added to the end!).
                * This allows maintenance in O(1).
                */
               && (!timeout_time
                   || cs->queue_timestamp + qp->timeout < timeout_time
                   || cs->queue_timestamp > timeout_time + qp->timeout)) {
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
            continue;

        APR_RING_UNSPLICE(first, last, timeout_list);
        APR_RING_SPLICE_TAIL(&trash, first, last, event_conn_state_t,
                             timeout_list);
        qp->count -= count;
        total += count;
    }
    if (!total)
        return;

    AP_DEBUG_ASSERT(*q->total >= total);
    *q->total -= total;
    apr_thread_mutex_unlock(timeout_mutex);
    first = APR_RING_FIRST(&trash);
    do {
        cs = APR_RING_NEXT(first, timeout_list);
        TO_QUEUE_ELEM_INIT(first);
        func(first);
        first = cs;
    } while (--total);
    apr_thread_mutex_lock(timeout_mutex);
}

static void * APR_THREAD_FUNC listener_thread(apr_thread_t * thd, void *dummy)
{
    timer_event_t *ep;
