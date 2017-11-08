static const char *h2_conf_set_window_size(cmd_parms *parms,
                                           void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    cfg->h2_window_size = (int)apr_atoi64(value);
    (void)arg;
    if (cfg->h2_window_size < 1024) {
        return "value must be >= 1024";
    }
    return NULL;
}