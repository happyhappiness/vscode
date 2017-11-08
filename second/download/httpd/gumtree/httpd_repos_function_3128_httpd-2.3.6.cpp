static apr_status_t event_register_timed_callback(apr_time_t t,
                                                  ap_mpm_callback_fn_t *cbfn,
                                                  void *baton)
{
    int inserted = 0;
    timer_event_t *ep;
    timer_event_t *te;
    /* oh yeah, and make locking smarter/fine grained. */
    apr_thread_mutex_lock(g_timer_ring_mtx);

    if (!APR_RING_EMPTY(&timer_free_ring, timer_event_t, link)) {
        te = APR_RING_FIRST(&timer_free_ring);
        APR_RING_REMOVE(te, link);
    }
    else {
        /* XXXXX: lol, pool allocation without a context from any thread.Yeah. Right. MPMs Suck. */
        te = malloc(sizeof(timer_event_t));
        APR_RING_ELEM_INIT(te, link);
    }

    te->cbfunc = cbfn;
    te->baton = baton;
    /* XXXXX: optimize */
    te->when = t + apr_time_now();

    /* Okay, insert sorted by when.. */
    for (ep = APR_RING_FIRST(&timer_ring);
         ep != APR_RING_SENTINEL(&timer_ring,
                                 timer_event_t, link);
         ep = APR_RING_NEXT(ep, link))
    {
        if (ep->when > te->when) {
            inserted = 1;
            APR_RING_INSERT_BEFORE(ep, te, link);
            break;
        }
    }
    
    if (!inserted) {
        APR_RING_INSERT_TAIL(&timer_ring, te, timer_event_t, link);
    }

    apr_thread_mutex_unlock(g_timer_ring_mtx);

    return APR_SUCCESS;
}