static apr_status_t wd_worker_cleanup(void *data)
{
    apr_status_t rv;
    ap_watchdog_t *w = (ap_watchdog_t *)data;

    if (w->is_running) {
        watchdog_list_t *wl = w->callbacks;
        while (wl) {
            if (wl->status == APR_SUCCESS) {
                /* Execute watchdog callback with STOPPING state */
                (*wl->callback_fn)(AP_WATCHDOG_STATE_STOPPING,
                                    (void *)wl->data, w->pool);
                wl->status = APR_EOF;
            }
            wl = wl->next;
        }
    }
    w->is_running = 0;
    apr_thread_join(&rv, w->thread);
    return rv;
}