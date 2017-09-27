{
    apr_status_t rv;
    const char *pk = "watchdog_init_module_tag";
    apr_pool_t *pproc = s->process->pool;
    const apr_array_header_t *wl;

    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG)
        /* First time config phase -- skip. */
        return OK;

    apr_pool_userdata_get((void *)&wd_server_conf, pk, pproc);
    if (!wd_server_conf) {
        if (!(wd_server_conf = apr_pcalloc(pproc, sizeof(wd_server_conf_t))))
            return APR_ENOMEM;
        apr_pool_create(&wd_server_conf->pool, pproc);
        apr_pool_userdata_set(wd_server_conf, pk, apr_pool_cleanup_null, pproc);
    }
    wd_server_conf->s = s;
    if ((wl = ap_list_provider_names(pconf, AP_WATCHDOG_PGROUP,
                                            AP_WATCHDOG_PVERSION))) {
        const ap_list_provider_names_t *wn;
        int i;

        wn = (ap_list_provider_names_t *)wl->elts;
        for (i = 0; i < wl->nelts; i++) {
            ap_watchdog_t *w = ap_lookup_provider(AP_WATCHDOG_PGROUP,
                                                  wn[i].provider_name,
                                                  AP_WATCHDOG_PVERSION);
            if (w) {
                if (!w->active) {
                    int status = ap_run_watchdog_need(s, w->name, 1,
                                                      w->singleton);
                    if (status == OK) {
                        /* One of the modules returned OK to this watchog.
