            apr_sleep(AP_WD_TM_SLICE);
        }
    }
    if (w->is_running) {
        watchdog_list_t *wl = w->callbacks;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, wd_server_conf->s,
                     APLOGNO(02972) "%sWatchdog (%s) running",
                     w->singleton ? "Singleton " : "", w->name);
        apr_time_clock_hires(w->pool);
        if (wl) {
            apr_pool_t *ctx = NULL;
            apr_pool_create(&ctx, w->pool);
            while (wl && w->is_running) {
                /* Execute watchdog callback */
