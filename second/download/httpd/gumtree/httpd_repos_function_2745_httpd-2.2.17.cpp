static struct apr_thread_list_elt *trim_threads(apr_thread_pool_t *me,
                                                apr_size_t *cnt, int idle)
{
    struct apr_thread_list *thds;
    apr_size_t n, n_dbg, i;
    struct apr_thread_list_elt *head, *tail, *elt;

    apr_thread_mutex_lock(me->lock);
    if (idle) {
        thds = me->idle_thds;
        n = me->idle_cnt;
    }
    else {
        thds = me->busy_thds;
        n = me->thd_cnt - me->idle_cnt;
    }
    if (n <= *cnt) {
        apr_thread_mutex_unlock(me->lock);
        *cnt = 0;
        return NULL;
    }
    n -= *cnt;

    head = APR_RING_FIRST(thds);
    for (i = 0; i < *cnt; i++) {
        head = APR_RING_NEXT(head, link);
    }
    tail = APR_RING_LAST(thds);
    if (idle) {
        APR_RING_UNSPLICE(head, tail, link);
        me->idle_cnt = *cnt;
    }

    n_dbg = 0;
    for (elt = head; elt != tail; elt = APR_RING_NEXT(elt, link)) {
        elt->state = TH_STOP;
        n_dbg++;
    }
    elt->state = TH_STOP;
    n_dbg++;
    assert(n == n_dbg);
    *cnt = n;

    apr_thread_mutex_unlock(me->lock);

    APR_RING_PREV(head, link) = NULL;
    APR_RING_NEXT(tail, link) = NULL;
    return head;
}