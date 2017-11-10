static void *reqtimeout_merge_srv_config(apr_pool_t *p, void *base_, void *add_)
{
    reqtimeout_srv_cfg *base = base_;
    reqtimeout_srv_cfg *add  = add_;
    reqtimeout_srv_cfg *cfg  = apr_pcalloc(p, sizeof(reqtimeout_srv_cfg));

    MERGE_INT(cfg, base, add, header_timeout);
    MERGE_INT(cfg, base, add, header_max_timeout);
    MERGE_INT(cfg, base, add, header_min_rate);
    MERGE_INT(cfg, base, add, body_timeout);
    MERGE_INT(cfg, base, add, body_max_timeout);
    MERGE_INT(cfg, base, add, body_min_rate);

    cfg->header_rate_factor = (cfg->header_min_rate == UNSET) ?
                              base->header_rate_factor : add->header_rate_factor;
    cfg->body_rate_factor = (cfg->body_min_rate == UNSET) ?
                            base->body_rate_factor : add->body_rate_factor;
    return cfg;
}