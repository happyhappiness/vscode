static int simple_run_loop(simple_core_t * sc)
{
    apr_status_t rv;
    simple_timer_t *ep = NULL;

    while (sc->mpm_state == AP_MPMQ_RUNNING) {
        apr_time_t tnow = apr_time_now();
        simple_timer_t *head;
        apr_interval_time_t timeout = apr_time_from_msec(500);
        APR_RING_HEAD(simple_temp_timer_ring_t, simple_timer_t) tmp_ring;

        apr_thread_mutex_lock(sc->mtx);
        head = APR_RING_FIRST(&sc->timer_ring);

        if (head != APR_RING_SENTINEL(&sc->timer_ring, simple_timer_t, link)) {
            if (tnow < head->expires) {
                timeout = (head->expires - tnow);
                if (timeout > apr_time_from_msec(500)) {
                    /* pqXXXXX: I'm 95% sure that the Linux Powertop guys will slap me for this. */
                    timeout = apr_time_from_msec(500);
                }
            }
            else {
                /* We have already expired timers in the queue. */
                timeout = 0;
            }
        }
        apr_thread_mutex_unlock(sc->mtx);

        rv = apr_pollcb_poll(sc->pollcb, timeout, simple_io_callback, sc);

        tnow = apr_time_now();

        if (rv) {
            if (!APR_STATUS_IS_EINTR(rv) && !APR_STATUS_IS_TIMEUP(rv)) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                             "simple_main_loop: apr_pollcb_poll failed");
                return DONE;
            }
        }

        APR_RING_INIT(&tmp_ring, simple_timer_t, link);

        apr_thread_mutex_lock(sc->mtx);

        APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t, link);

        /* now iterate any timers */
        if (!APR_RING_EMPTY(&sc->timer_ring, simple_timer_t, link)) {
            for (ep = APR_RING_FIRST(&sc->timer_ring);
                 ep != APR_RING_SENTINEL(&sc->timer_ring,
                                         simple_timer_t, link);
                 ep = APR_RING_NEXT(ep, link)) {
                if (ep->expires < tnow) {
                    simple_timer_t *next = APR_RING_PREV(ep, link);
                    /* push this task */
                    APR_RING_REMOVE(ep, link);
                    APR_RING_CHECK_CONSISTENCY(&sc->timer_ring,
                                               simple_timer_t, link);
                    APR_RING_INSERT_TAIL(&tmp_ring, ep, simple_timer_t, link);
                    ep = next;
                }
                else {
                    break;
                }
            }
        }

        APR_RING_CHECK_CONSISTENCY(&sc->timer_ring, simple_timer_t, link);

        apr_thread_mutex_unlock(sc->mtx);

        if (!APR_RING_EMPTY(&tmp_ring, simple_timer_t, link)) {
            for (ep = APR_RING_FIRST(&tmp_ring);
                 ep != APR_RING_SENTINEL(&tmp_ring,
                                         simple_timer_t, link);
                 ep = APR_RING_NEXT(ep, link)) {
                apr_thread_pool_push(sc->workers,
                                     simple_timer_invoke,
                                     ep,
                                     APR_THREAD_TASK_PRIORITY_NORMAL, NULL);
            }
        }
    }

    return OK;
}