static apr_status_t
simple_timer_pool_cleanup(void *baton)
{
    simple_timer_t *elem = (simple_timer_t *)baton;
    simple_core_t *sc = elem->sc;

    apr_thread_mutex_lock(sc->mtx);
    APR_RING_REMOVE(elem, link);
    apr_thread_mutex_unlock(sc->mtx);

    return APR_SUCCESS;
}