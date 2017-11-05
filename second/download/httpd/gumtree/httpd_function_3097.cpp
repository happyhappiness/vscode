static int wd_post_config_hook(apr_pool_t *pconf, apr_pool_t *plog,
                               apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    const char *pk = "watchdog_init_module_tag";
    apr_pool_t *pproc = s->process->pool;
    const apr_array_header_t *wl;

    apr_pool_userdata_get((void *)&wd_server_conf, pk, pproc);
    if (!wd_server_conf) {
        if (!(wd_server_conf = apr_pcalloc(pproc, sizeof(wd_server_conf_t))))
            return APR_ENOMEM;
        apr_pool_create(&wd_server_conf->pool, pproc);
        wd_server_conf->s = s;
        apr_pool_userdata_set(wd_server_conf, pk, apr_pool_cleanup_null, pproc);
        /* First time config phase -- skip. */
        return OK;
    }
#if defined(WIN32)
    {
        const char *ppid = getenv("AP_PARENT_PID");
        if (ppid && *ppid) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                "[%" APR_PID_T_FMT " - %s] "
                "child second stage post config hook",
                getpid(), ppid);
            return OK;
        }
    }
#endif
    wd_server_conf->s = s;
    if ((wl = ap_list_provider_names(pconf, AP_WATCHODG_PGROUP,
                                            AP_WATCHODG_PVERSION))) {
        const ap_list_provider_names_t *wn;
        int i;

        wn = (ap_list_provider_names_t *)wl->elts;
        for (i = 0; i < wl->nelts; i++) {
            ap_watchdog_t *w = ap_lookup_provider(AP_WATCHODG_PGROUP,
                                                  wn[i].provider_name,
                                                  AP_WATCHODG_PVERSION);
            if (w) {
                if (!w->active) {
                    int status = ap_run_watchdog_need(s, w->name, 1,
                                                      w->singleton);
                    if (status == OK) {
                        /* One of the modules returned OK to this watchog.
                         * Mark it as active
                         */
                        w->active = 1;
                    }
                }
                if (w->active) {
                    /* We have active watchdog.
                     * Create the watchdog thread
                     */
                    if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                                "Watchdog: Failed to create parent worker thread.");
                        return rv;
                    }
                    wd_server_conf->parent_workers++;
                }
            }
        }
    }
    if (wd_server_conf->parent_workers) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Spawned %d parent worker threads.",
                     wd_server_conf->parent_workers);
    }
    if ((wl = ap_list_provider_names(pconf, AP_WATCHODG_PGROUP,
                                            AP_WATCHODG_CVERSION))) {
        const ap_list_provider_names_t *wn;
        int i;

        wn = (ap_list_provider_names_t *)wl->elts;
        for (i = 0; i < wl->nelts; i++) {
            ap_watchdog_t *w = ap_lookup_provider(AP_WATCHODG_PGROUP,
                                                  wn[i].provider_name,
                                                  AP_WATCHODG_CVERSION);
            if (w) {
                if (!w->active) {
                    int status = ap_run_watchdog_need(s, w->name, 0,
                                                      w->singleton);
                    if (status == OK) {
                        /* One of the modules returned OK to this watchog.
                         * Mark it as active
                         */
                        w->active = 1;
                    }
                }
                if (w->active) {
                    /* We have some callbacks registered.
                     * Create mutexes for singleton watchdogs
                     */
                    if (w->singleton) {
                        rv = ap_proc_mutex_create(&w->mutex, NULL, wd_proc_mutex_type,
                                                  w->name, s,
                                                  wd_server_conf->pool, 0);
                        if (rv != APR_SUCCESS) {
                            return rv;
                        }
                    }
                    wd_server_conf->child_workers++;
                }
            }
        }
    }
    return OK;
}