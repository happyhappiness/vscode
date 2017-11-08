static void wait_on_busy_threads(apr_thread_pool_t *me, void *owner)
{
#ifndef NDEBUG
    apr_os_thread_t *os_thread;
#endif
    struct apr_thread_list_elt *elt;
    apr_thread_mutex_lock(me->lock);
    elt = APR_RING_FIRST(me->busy_thds);
    while (elt != APR_RING_SENTINEL(me->busy_thds, apr_thread_list_elt, link)) {
        if (elt->current_owner != owner) {
            elt = APR_RING_NEXT(elt, link);
            continue;
        }
#ifndef NDEBUG
        /* make sure the thread is not the one calling tasks_cancel */
        apr_os_thread_get(&os_thread, elt->thd);
#ifdef WIN32
        /* hack for apr win32 bug */
        assert(!apr_os_thread_equal(apr_os_thread_current(), os_thread));
#else
        assert(!apr_os_thread_equal(apr_os_thread_current(), *os_thread));
#endif
#endif
        while (elt->current_owner == owner) {
            apr_thread_mutex_unlock(me->lock);
            apr_sleep(200 * 1000);
            apr_thread_mutex_lock(me->lock);
        }
        elt = APR_RING_FIRST(me->busy_thds);
    }
    apr_thread_mutex_unlock(me->lock);
    return;
}