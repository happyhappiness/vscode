static int hm_post_config(apr_pool_t *p, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    hm_ctx_t *ctx = ap_get_module_config(s->module_config,
                                         &heartmonitor_module);
    APR_OPTIONAL_FN_TYPE(ap_watchdog_get_instance) *hm_watchdog_get_instance;
    APR_OPTIONAL_FN_TYPE(ap_watchdog_register_callback) *hm_watchdog_register_callback;

    hm_watchdog_get_instance = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_get_instance);
    hm_watchdog_register_callback = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_register_callback);
    if (!hm_watchdog_get_instance || !hm_watchdog_register_callback) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(02093)
                     "mod_watchdog is required");
        return !OK;
    }

    /* Create the slotmem */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_CONFIG) {
        /* this is the real thing */
        if (maxworkers) {
            storage = ap_lookup_provider(AP_SLOTMEM_PROVIDER_GROUP, "shm",
                                         AP_SLOTMEM_PROVIDER_VERSION);
            if (!storage) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02284)
                             "failed to lookup provider 'shm' for '%s', "
                             "maybe you need to load mod_slotmem_shm?",
                             AP_SLOTMEM_PROVIDER_GROUP);
                return !OK;
            }
            storage->create(&slotmem, "mod_heartmonitor", sizeof(hm_slot_server_t), maxworkers, AP_SLOTMEM_TYPE_PREGRAB, p);
            if (!slotmem) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02285)
                             "slotmem_create for status failed");
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
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02094)
                     "Failed to create watchdog instance (%s)",
                     HM_WATHCHDOG_NAME);
        return !OK;
    }
    /* Register a callback with zero interval. */
    rv = hm_watchdog_register_callback(ctx->watchdog,
                                       0,
                                       ctx,
                                       hm_watchdog_callback);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02095)
                     "Failed to register watchdog callback (%s)",
                     HM_WATHCHDOG_NAME);
        return !OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02096)
                 "wd callback %s", HM_WATHCHDOG_NAME);
    return OK;
}