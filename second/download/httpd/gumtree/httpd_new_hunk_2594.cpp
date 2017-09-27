
    if (!wd_server_conf->child_workers) {
        /* We don't have anything configured, bail out.
         */
        return;
    }
    if ((wl = ap_list_provider_names(p, AP_WATCHDOG_PGROUP,
                                        AP_WATCHDOG_CVERSION))) {
        const ap_list_provider_names_t *wn;
        int i;
        wn = (ap_list_provider_names_t *)wl->elts;
        for (i = 0; i < wl->nelts; i++) {
            ap_watchdog_t *w = ap_lookup_provider(AP_WATCHDOG_PGROUP,
                                                  wn[i].provider_name,
                                                  AP_WATCHDOG_CVERSION);
            if (w && w->active) {
                /* We have some callbacks registered.
                 * Kick of the watchdog
                 */
                if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01573)
                                 "Watchdog: Failed to create worker thread.");
                    /* No point to continue */
                    return;
                }
            }
        }
