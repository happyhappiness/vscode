static int reqtimeout_pre_conn(conn_rec *c, void *csd)
{
    reqtimeout_ctx *ctx;
    reqtimeout_con_cfg *ccfg;
    reqtimeout_srv_cfg *cfg;

    cfg = ap_get_module_config(c->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);
    if (cfg->header_timeout <= 0 && cfg->body_timeout <= 0) {
        /* not configured for this vhost */
        return OK;
    }

    ctx = apr_pcalloc(c->pool, sizeof(reqtimeout_ctx));
    ctx->socket = csd;

    ccfg = apr_pcalloc(c->pool, sizeof(reqtimeout_con_cfg));
    ccfg->new_timeout = cfg->header_timeout;
    ccfg->new_max_timeout = cfg->header_max_timeout;
    ccfg->type = "header";
    ccfg->min_rate = cfg->header_min_rate;
    ccfg->rate_factor = cfg->header_rate_factor;
    ap_set_module_config(c->conn_config, &reqtimeout_module, ccfg);

    ap_add_input_filter("reqtimeout", ctx, NULL, c);
    return OK;
}