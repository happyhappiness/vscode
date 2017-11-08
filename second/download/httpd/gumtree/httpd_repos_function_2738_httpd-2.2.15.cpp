static apr_size_t trim_idle_threads(apr_thread_pool_t *me, apr_size_t cnt)
{
    apr_size_t n_dbg;
    struct apr_thread_list_elt *elt, *head, *tail;
    apr_status_t rv;

    elt = trim_threads(me, &cnt, 1);

    apr_thread_mutex_lock(me->cond_lock);
    apr_thread_cond_broadcast(me->cond);
    apr_thread_mutex_unlock(me->cond_lock);

    n_dbg = 0;
    if (NULL != (head = elt)) {
        while (elt) {
            tail = elt;
            apr_thread_join(&rv, elt->thd);
            elt = APR_RING_NEXT(elt, link);
            ++n_dbg;
        }
        apr_thread_mutex_lock(me->lock);
        APR_RING_SPLICE_TAIL(me->recycled_thds, head, tail,
                             apr_thread_list_elt, link);
        apr_thread_mutex_unlock(me->lock);
    }
    assert(cnt == n_dbg);

    return cnt;
}