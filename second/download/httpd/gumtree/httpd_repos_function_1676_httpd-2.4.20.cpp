static void wd_child_init_hook(apr_pool_t *p, server_rec *s)
{
    apr_status_t rv = OK;
    const apr_array_header_t *wl;

    if (!wd_server_conf->child_workers) {
        /* We don't have anything configured, bail out.
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(02980)
                     "Watchdog: nothing configured?");
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
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(02981)
                             "Watchdog: Created worker thread (%s).", wn[i].provider_name);
            }
        }
    }
}