static int hc_post_config(apr_pool_t *p, apr_pool_t *plog,
                       apr_pool_t *ptemp, server_rec *main_s)
{
    apr_status_t rv;
    server_rec *s = main_s;

    APR_OPTIONAL_FN_TYPE(ap_watchdog_get_instance) *hc_watchdog_get_instance;
    APR_OPTIONAL_FN_TYPE(ap_watchdog_register_callback) *hc_watchdog_register_callback;

    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }
    hc_watchdog_get_instance = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_get_instance);
    hc_watchdog_register_callback = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_register_callback);
    if (!hc_watchdog_get_instance || !hc_watchdog_register_callback) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(03262)
                     "mod_watchdog is required");
        return !OK;
    }
    rv = hc_watchdog_get_instance(&watchdog,
                                  HCHECK_WATHCHDOG_NAME,
                                  0, 1, p);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(03263)
                     "Failed to create watchdog instance (%s)",
                     HCHECK_WATHCHDOG_NAME);
        return !OK;
    }
    while (s) {
        sctx_t *ctx = ap_get_module_config(s->module_config,
                                           &proxy_hcheck_module);

        if (s != ctx->s) {
            ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s, APLOGNO(10019)
                         "Missing unique per-server context: %s (%pp:%pp) (no hchecks)",
                         s->server_hostname, s, ctx->s);
            s = s->next;
            continue;
        }
        rv = hc_watchdog_register_callback(watchdog,
                apr_time_from_sec(HCHECK_WATHCHDOG_INTERVAL),
                ctx,
                hc_watchdog_callback);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(03264)
                         "Failed to register watchdog callback (%s)",
                         HCHECK_WATHCHDOG_NAME);
            return !OK;
        }
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03265)
                     "watchdog callback registered (%s for %s)", HCHECK_WATHCHDOG_NAME, s->server_hostname);
        s = s->next;
    }
    return OK;
}