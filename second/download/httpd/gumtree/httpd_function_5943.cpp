static void* APR_THREAD_FUNC wd_worker(apr_thread_t *thread, void *data)
{
    ap_watchdog_t *w = (ap_watchdog_t *)data;
    apr_status_t rv;
    int locked = 0;
    int probed = 0;
    int inited = 0;
    int mpmq_s = 0;

    w->pool = apr_thread_pool_get(thread);
    w->is_running = 1;

    apr_thread_mutex_unlock(w->startup);
    if (w->mutex) {
        while (w->is_running) {
            if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpmq_s) != APR_SUCCESS) {
                w->is_running = 0;
                break;
            }
            if (mpmq_s == AP_MPMQ_STOPPING) {
                w->is_running = 0;
                break;
            }
            rv = apr_proc_mutex_trylock(w->mutex);
            if (rv == APR_SUCCESS) {
                if (probed) {
                    /* Sleep after we were locked
                     * up to 1 second. Httpd can be
                     * in the middle of shutdown, and
                     * our child didn't yet received
                     * the shutdown signal.
                     */
                    probed = 10;
                    while (w->is_running && probed > 0) {
                        apr_sleep(AP_WD_TM_INTERVAL);
                        probed--;
                        if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpmq_s) != APR_SUCCESS) {
                            w->is_running = 0;
                            break;
                        }
                        if (mpmq_s == AP_MPMQ_STOPPING) {
                            w->is_running = 0;
                            break;
                        }
                    }
                }
                locked = 1;
                break;
            }
            probed = 1;
            apr_sleep(AP_WD_TM_SLICE);
        }
    }
    if (w->is_running) {
        watchdog_list_t *wl = w->callbacks;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, wd_server_conf->s,
                     "%sWatchdog (%s) running",
                     w->singleton ? "Singleton" : "", w->name);
        apr_time_clock_hires(w->pool);
        if (wl) {
            apr_pool_t *ctx = NULL;
            apr_pool_create(&ctx, w->pool);
            while (wl && w->is_running) {
                /* Execute watchdog callback */
                wl->status = (*wl->callback_fn)(AP_WATCHDOG_STATE_STARTING,
                                                (void *)wl->data, ctx);
                wl = wl->next;
            }
            apr_pool_destroy(ctx);
        }
        else {
            ap_run_watchdog_init(wd_server_conf->s, w->name, w->pool);
            inited = 1;
        }
    }

    /* Main execution loop */
    while (w->is_running) {
        apr_pool_t *ctx = NULL;
        apr_time_t curr;
        watchdog_list_t *wl = w->callbacks;

        apr_sleep(AP_WD_TM_SLICE);
        if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpmq_s) != APR_SUCCESS) {
            w->is_running = 0;
        }
        if (mpmq_s == AP_MPMQ_STOPPING) {
            w->is_running = 0;
        }
        if (!w->is_running) {
            break;
        }
        curr = apr_time_now() - AP_WD_TM_SLICE;
        while (wl && w->is_running) {
            if (wl->status == APR_SUCCESS) {
                wl->step += (apr_time_now() - curr);
                if (wl->step >= wl->interval) {
                    if (!ctx)
                        apr_pool_create(&ctx, w->pool);
                    wl->step = 0;
                    /* Execute watchdog callback */
                    wl->status = (*wl->callback_fn)(AP_WATCHDOG_STATE_RUNNING,
                                                    (void *)wl->data, ctx);
                    if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpmq_s) != APR_SUCCESS) {
                        w->is_running = 0;
                    }
                    if (mpmq_s == AP_MPMQ_STOPPING) {
                        w->is_running = 0;
                    }
                }
            }
            wl = wl->next;
        }
        if (w->is_running && w->callbacks == NULL) {
            /* This is hook mode watchdog
             * running on WatchogInterval
             */
            w->step += (apr_time_now() - curr);
            if (w->step >= wd_interval) {
                if (!ctx)
                    apr_pool_create(&ctx, w->pool);
                w->step = 0;
                /* Run watchdog step hook */
                ap_run_watchdog_step(wd_server_conf->s, w->name, ctx);
            }
        }
        if (ctx)
            apr_pool_destroy(ctx);
        if (!w->is_running) {
            break;
        }
    }
    if (inited) {
        /* Run the watchdog exit hooks.
         * If this was singleton watchdog the init hook
         * might never been called, so skip the exit hook
         * in that case as well.
         */
        ap_run_watchdog_exit(wd_server_conf->s, w->name, w->pool);
    }
    else {
        watchdog_list_t *wl = w->callbacks;
        while (wl) {
            if (wl->status == APR_SUCCESS) {
                /* Execute watchdog callback with STOPPING state */
                (*wl->callback_fn)(AP_WATCHDOG_STATE_STOPPING,
                                   (void *)wl->data, w->pool);
            }
            wl = wl->next;
        }
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, wd_server_conf->s,
                 "%sWatchdog (%s) stopping",
                 w->singleton ? "Singleton" : "", w->name);

    if (locked)
        apr_proc_mutex_unlock(w->mutex);
    apr_thread_exit(w->thread, APR_SUCCESS);

    return NULL;
}