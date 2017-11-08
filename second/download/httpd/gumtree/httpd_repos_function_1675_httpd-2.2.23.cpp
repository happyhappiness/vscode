static void *reqtimeout_create_srv_config(apr_pool_t *p, server_rec *s)
{
    reqtimeout_srv_cfg *cfg = apr_pcalloc(p, sizeof(reqtimeout_srv_cfg));

    cfg->header_timeout = -1;
    cfg->header_max_timeout = -1;
    cfg->header_min_rate = -1;
    cfg->body_timeout = -1;
    cfg->body_max_timeout = -1;
    cfg->body_min_rate = -1;

    return cfg;
}