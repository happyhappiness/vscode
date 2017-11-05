void
simple_register_timer(simple_core_t * sc,
                      simple_timer_cb cb,
                      void *baton, apr_time_t relative_time,
                      apr_pool_t *shutdown_pool)
{
    simple_timer_t *elem = NULL;
    simple_timer_t *ep = NULL;
    int inserted = 0;
    apr_time_t t = apr_time_now() + relative_time;

    apr_thread_mutex_lock(sc->mtx);

    APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t, link);

    elem = (simple_timer_t *) apr_pcalloc(shutdown_pool, sizeof(simple_timer_t));

    APR_RING_ELEM_INIT(elem, link);
    elem->expires = t;
    elem->cb = cb;
    elem->baton = baton;
    elem->pool = shutdown_pool;
    elem->sc = sc;
    apr_pool_cleanup_register(elem->pool, elem, simple_timer_pool_cleanup, apr_pool_cleanup_null);

    APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t, link);

    /* pqXXXXXX: skiplist would be a nice optimization here. */
    if (!APR_RING_EMPTY(&sc->timer_ring, simple_timer_t, link)) {
        ep = APR_RING_FIRST(&sc->timer_ring);
        while (inserted == 0 &&
               ep != APR_RING_SENTINEL(&sc->timer_ring, simple_timer_t, link))
        {
            if (ep->expires < elem->expires) {
                APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t,
                                           link);
                APR_RING_INSERT_BEFORE(ep, elem, link);
                inserted = 1;
                APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t,
                                           link);
            }
            ep = APR_RING_NEXT(ep, link);
        }
    }

    APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t, link);

    if (!inserted) {
        APR_RING_INSERT_TAIL(&sc->timer_ring, elem, simple_timer_t, link);
    }

    APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t, link);

    apr_thread_mutex_unlock(sc->mtx);
}