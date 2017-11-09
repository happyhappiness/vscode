static apr_status_t event_register_timed_callback(apr_time_t t,
                                                  ap_mpm_callback_fn_t *cbfn,
                                                  void *baton)
{
    timer_event_t *te;
    /* oh yeah, and make locking smarter/fine grained. */
    apr_thread_mutex_lock(g_timer_skiplist_mtx);

    if (!APR_RING_EMPTY(&timer_free_ring, timer_event_t, link)) {
        te = APR_RING_FIRST(&timer_free_ring);
        APR_RING_REMOVE(te, link);
    }
    else {
        te = apr_skiplist_alloc(timer_skiplist, sizeof(timer_event_t));
        APR_RING_ELEM_INIT(te, link);
    }

    te->cbfunc = cbfn;
    te->baton = baton;
    /* XXXXX: optimize */
    te->when = t + apr_time_now();

    /* Okay, add sorted by when.. */
    apr_skiplist_insert(timer_skiplist, te);

    apr_thread_mutex_unlock(g_timer_skiplist_mtx);

    return APR_SUCCESS;
}