static apr_status_t ap_watchdog_register_callback(ap_watchdog_t *w,
                                                  apr_interval_time_t interval,
                                                  const void *data,
                                                  ap_watchdog_callback_fn_t *callback)
{
    watchdog_list_t *c = w->callbacks;

    while (c) {
        if (c->data == data && c->callback_fn == callback) {
            /* We have already registered callback.
             * Do not allow callbacks that have the same
             * function and data pointers.
             */
            return APR_EEXIST;
        }
        c = c->next;
    }
    c = apr_palloc(w->pool, sizeof(watchdog_list_t));
    c->data        = data;
    c->callback_fn = callback;
    c->interval    = interval;
    c->step        = 0;
    c->status      = APR_EINIT;

    c->wd          = w;
    c->next        = w->callbacks;
    w->callbacks   = c;
    w->active++;

    return APR_SUCCESS;
}