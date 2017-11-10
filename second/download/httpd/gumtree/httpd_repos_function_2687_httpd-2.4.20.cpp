static void *h2_config_create(apr_pool_t *pool,
                              const char *prefix, const char *x)
{
    h2_config *conf = (h2_config *)apr_pcalloc(pool, sizeof(h2_config));
    
    const char *s = x? x : "unknown";
    char *name = apr_pstrcat(pool, prefix, "[", s, "]", NULL);
    
    conf->name                 = name;
    conf->h2_max_streams       = DEF_VAL;
    conf->h2_window_size       = DEF_VAL;
    conf->min_workers          = DEF_VAL;
    conf->max_workers          = DEF_VAL;
    conf->max_worker_idle_secs = DEF_VAL;
    conf->stream_max_mem_size  = DEF_VAL;
    conf->alt_svc_max_age      = DEF_VAL;
    conf->serialize_headers    = DEF_VAL;
    conf->h2_direct            = DEF_VAL;
    conf->session_extra_files  = DEF_VAL;
    conf->modern_tls_only      = DEF_VAL;
    conf->h2_upgrade           = DEF_VAL;
    conf->tls_warmup_size      = DEF_VAL;
    conf->tls_cooldown_secs    = DEF_VAL;
    conf->h2_push              = DEF_VAL;
    conf->priorities           = NULL;
    conf->push_diary_size      = DEF_VAL;
    
    return conf;
}