static int reqtimeout_init(conn_rec *c)
{
    reqtimeout_con_cfg *ccfg;
    reqtimeout_srv_cfg *cfg;

    cfg = ap_get_module_config(c->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);
    if (cfg->header_timeout == 0 && cfg->body_timeout == 0) {
        /* disabled for this vhost */
        return DECLINED;
    }

    ccfg = apr_pcalloc(c->pool, sizeof(reqtimeout_con_cfg));
    ccfg->type = "header";
    if (cfg->header_timeout != UNSET) {
        ccfg->new_timeout     = cfg->header_timeout;
        ccfg->new_max_timeout = cfg->header_max_timeout;
        ccfg->min_rate        = cfg->header_min_rate;
        ccfg->rate_factor     = cfg->header_rate_factor;
    }
    else {
        ccfg->new_timeout     = MRT_DEFAULT_HEADER_TIMEOUT;
        ccfg->new_max_timeout = MRT_DEFAULT_HEADER_MAX_TIMEOUT;
        ccfg->min_rate        = MRT_DEFAULT_HEADER_MIN_RATE;
        ccfg->rate_factor     = default_header_rate_factor;
    }
    ap_set_module_config(c->conn_config, &reqtimeout_module, ccfg);

    ap_add_input_filter("reqtimeout", ccfg, NULL, c);
    /* we are not handling the connection, we just do initialization */
    return DECLINED;
}