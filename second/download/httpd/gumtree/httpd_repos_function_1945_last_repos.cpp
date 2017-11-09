static int hb_watchdog_need(server_rec *s, const char *name,
                          int parent, int singleton)
{
    hb_ctx_t *ctx = ap_get_module_config(s->module_config, &heartbeat_module);

    if (ctx->active && singleton && !strcmp(name, AP_WATCHDOG_SINGLETON))
        return OK;
    else
        return DECLINED;
}