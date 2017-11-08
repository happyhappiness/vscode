static int reqtimeout_after_body(request_rec *r)
{
    reqtimeout_srv_cfg *cfg;
    reqtimeout_con_cfg *ccfg =
        ap_get_module_config(r->connection->conn_config, &reqtimeout_module);

    if (ccfg == NULL) {
        /* not configured for this connection */
        return OK;
    }

    cfg = ap_get_module_config(r->connection->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);

    ccfg->timeout_at = 0;
    ccfg->max_timeout_at = 0;
    ccfg->in_keep_alive = 1;
    ccfg->new_timeout = cfg->header_timeout;
    ccfg->new_max_timeout = cfg->header_max_timeout;
    ccfg->min_rate = cfg->header_min_rate;
    ccfg->rate_factor = cfg->header_rate_factor;
    
    ccfg->type = "header";

    return OK;
}