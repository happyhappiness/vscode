    &age
};

static int lb_hb_init(apr_pool_t *p, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    apr_size_t size;
    unsigned int num;
    lb_hb_ctx_t *ctx = ap_get_module_config(s->module_config,
                                            &lbmethod_heartbeat_module);

    /* do nothing on first call */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG)
        return OK;

    storage = ap_lookup_provider(AP_SLOTMEM_PROVIDER_GROUP, "shm",
                                 AP_SLOTMEM_PROVIDER_VERSION);
    if (!storage) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(02281)
                     "Failed to lookup provider 'shm' for '%s'. Maybe you "
                     "need to load mod_slotmem_shm?",
                     AP_SLOTMEM_PROVIDER_GROUP);
        return OK;
    }

    /* Try to use a slotmem created by mod_heartmonitor */
    storage->attach(&hm_serversmem, "mod_heartmonitor", &size, &num, p);
    if (!hm_serversmem)
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(02282)
                     "No slotmem from mod_heartmonitor");
    else
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(02283)
                     "Using slotmem from mod_heartmonitor");

    if (hm_serversmem)
        ctx->path = "(slotmem)";

    return OK;
}
