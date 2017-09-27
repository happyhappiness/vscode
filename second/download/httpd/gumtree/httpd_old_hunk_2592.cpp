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
