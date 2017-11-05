static int hb_watchdog_init(server_rec *s, const char *name, apr_pool_t *pool)
{
    hb_ctx_t *ctx = ap_get_module_config(s->module_config, &heartbeat_module);

    ap_mpm_query(AP_MPMQ_HARD_LIMIT_THREADS, &ctx->thread_limit);
    ap_mpm_query(AP_MPMQ_HARD_LIMIT_DAEMONS, &ctx->server_limit);

    return OK;
}