static apr_status_t ap_watchdog_set_callback_interval(ap_watchdog_t *w,
                                                      apr_interval_time_t interval,
                                                      const void *data,
                                                      ap_watchdog_callback_fn_t *callback)
{
    watchdog_list_t *c = w->callbacks;
    apr_status_t rv = APR_EOF;

    while (c) {
        if (c->data == data && c->callback_fn == callback) {
            /* We have existing callback.
             * Update the interval and reset status, so the
             * callback and continue execution if stopped earlier.
             */
            c->interval = interval;
            c->step     = 0;
            c->status   = APR_SUCCESS;
            rv          = APR_SUCCESS;
            break;
        }
        c = c->next;
    }
    return rv;
}