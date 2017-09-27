/* Child init hook.                                                         */
/* Create watchdog threads and initializes Mutexes in child                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
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
