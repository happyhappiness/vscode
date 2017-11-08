static void *reqtimeout_create_srv_config(apr_pool_t *p, server_rec *s)
{
    reqtimeout_srv_cfg *cfg = apr_pcalloc(p, sizeof(reqtimeout_srv_cfg));

    cfg->header_timeout = UNSET;
    cfg->header_max_timeout = UNSET;
    cfg->header_min_rate = UNSET;
    cfg->body_timeout = UNSET;
    cfg->body_max_timeout = UNSET;
    cfg->body_min_rate = UNSET;

    return cfg;
}