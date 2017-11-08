static void reqtimeout_before_header(request_rec *r, conn_rec *c)
{
    reqtimeout_srv_cfg *cfg;
    reqtimeout_con_cfg *ccfg =
        ap_get_module_config(c->conn_config, &reqtimeout_module);

    if (ccfg == NULL) {
        /* not configured for this connection */
        return;
    }

    cfg = ap_get_module_config(c->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);

    /* (Re)set the state for this new request, but ccfg->socket and
     * ccfg->tmpbb which have the lifetime of the connection.
     */
    ccfg->timeout_at = 0;
    ccfg->max_timeout_at = 0;
    ccfg->in_keep_alive = (c->keepalives > 0);
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
}