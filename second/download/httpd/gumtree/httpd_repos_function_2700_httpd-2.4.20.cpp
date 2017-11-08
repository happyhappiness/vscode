static const char *h2_conf_set_stream_max_mem_size(cmd_parms *parms,
                                                   void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    
    
    cfg->stream_max_mem_size = (int)apr_atoi64(value);
    (void)arg;
    if (cfg->stream_max_mem_size < 1024) {
        return "value must be >= 1024";
    }
    return NULL;
}