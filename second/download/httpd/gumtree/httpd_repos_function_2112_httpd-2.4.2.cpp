static int reqtimeout_after_headers(request_rec *r)
{
    reqtimeout_srv_cfg *cfg;
    reqtimeout_con_cfg *ccfg =
        ap_get_module_config(r->connection->conn_config, &reqtimeout_module);

    if (ccfg == NULL || r->method_number == M_CONNECT) {
        /* either disabled for this connection or a CONNECT request */
        return OK;
    }
    cfg = ap_get_module_config(r->connection->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);

    ccfg->timeout_at = 0;
    ccfg->max_timeout_at = 0;
    ccfg->type = "body";
    if (cfg->body_timeout != UNSET) {
        ccfg->new_timeout     = cfg->body_timeout;
        ccfg->new_max_timeout = cfg->body_max_timeout;
        ccfg->min_rate        = cfg->body_min_rate;
        ccfg->rate_factor     = cfg->body_rate_factor;
    }
    else {
        ccfg->new_timeout     = MRT_DEFAULT_BODY_TIMEOUT;
        ccfg->new_max_timeout = MRT_DEFAULT_BODY_MAX_TIMEOUT;
        ccfg->min_rate        = MRT_DEFAULT_BODY_MIN_RATE;
        ccfg->rate_factor     = default_body_rate_factor;
    }
    return OK;
}