static int hb_watchdog_step(server_rec *s, const char *name, apr_pool_t *pool)
{
    hb_ctx_t *ctx = ap_get_module_config(s->module_config, &heartbeat_module);

    if (!ctx->active || strcmp(name, AP_WATCHDOG_SINGLETON)) {
        return OK;
    }
    return hb_monitor(ctx, pool);
}