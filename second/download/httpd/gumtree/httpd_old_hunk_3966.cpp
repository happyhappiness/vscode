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
