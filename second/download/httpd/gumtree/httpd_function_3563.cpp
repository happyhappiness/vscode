static int hm_post_config(apr_pool_t *p, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    const char *userdata_key = "mod_heartmonitor_init";
    void *data;
    hm_ctx_t *ctx = ap_get_module_config(s->module_config,
                                         &heartmonitor_module);
    APR_OPTIONAL_FN_TYPE(ap_watchdog_get_instance) *hm_watchdog_get_instance;
    APR_OPTIONAL_FN_TYPE(ap_watchdog_register_callback) *hm_watchdog_register_callback;

    hm_watchdog_get_instance = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_get_instance);
    hm_watchdog_register_callback = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_register_callback);
    if (!hm_watchdog_get_instance || !hm_watchdog_register_callback) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "Heartmonitor: mod_watchdog is required");
        return !OK;
    }

    /* Create the slotmem */
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        /* first call do nothing */
        apr_pool_userdata_set((const void *)1, userdata_key, apr_pool_cleanup_null, s->process->pool);
    } else {
        if (maxworkers) {
            storage = ap_lookup_provider(AP_SLOTMEM_PROVIDER_GROUP, "shared", "0");
            if (!storage) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_EMERG, 0, s, "ap_lookup_provider %s failed", AP_SLOTMEM_PROVIDER_GROUP);
                return !OK;
            }
            storage->create(&slotmem, "mod_heartmonitor", sizeof(hm_slot_server_t), maxworkers, AP_SLOTMEM_TYPE_PREGRAB, p);
            if (!slotmem) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_EMERG, 0, s, "slotmem_create for status failed");
                return !OK;
            }
        }
    }

    if (!ctx->active) {
        return OK;
    }
    rv = hm_watchdog_get_instance(&ctx->watchdog,
                                  HM_WATHCHDOG_NAME,
                                  0, 1, p);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "Heartmonitor: Failed to create watchdog "
                     "instance (%s)", HM_WATHCHDOG_NAME);
        return !OK;
    }
    /* Register a callback with zero interval. */
    rv = hm_watchdog_register_callback(ctx->watchdog,
                                       0,
                                       ctx,
                                       hm_watchdog_callback);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "Heartmonitor: Failed to register watchdog "
                     "callback (%s)", HM_WATHCHDOG_NAME);
        return !OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Heartmonitor: wd callback %s", HM_WATHCHDOG_NAME);
    return OK;
}