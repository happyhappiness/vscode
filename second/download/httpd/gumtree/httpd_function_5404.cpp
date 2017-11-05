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

    ccfg = ap_get_module_config(c->conn_config, &reqtimeout_module);
    if (ccfg == NULL) {
        ccfg = apr_pcalloc(c->pool, sizeof(reqtimeout_con_cfg));
        ap_set_module_config(c->conn_config, &reqtimeout_module, ccfg);
        ap_add_output_filter(reqtimeout_filter_name, ccfg, NULL, c);
        ap_add_input_filter(reqtimeout_filter_name, ccfg, NULL, c);
    }

    /* we are not handling the connection, we just do initialization */
    return DECLINED;
}