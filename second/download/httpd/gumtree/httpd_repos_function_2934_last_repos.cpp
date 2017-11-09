static const char *h2_conf_set_max_worker_idle_secs(cmd_parms *parms,
                                                    void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    cfg->max_worker_idle_secs = (int)apr_atoi64(value);
    (void)arg;
    if (cfg->max_worker_idle_secs < 1) {
        return "value must be > 0";
    }
    return NULL;
}