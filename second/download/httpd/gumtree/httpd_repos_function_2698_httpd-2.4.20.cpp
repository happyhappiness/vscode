static const char *h2_conf_set_max_workers(cmd_parms *parms,
                                           void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    cfg->max_workers = (int)apr_atoi64(value);
    (void)arg;
    if (cfg->max_workers < 1) {
        return "value must be > 0";
    }
    return NULL;
}