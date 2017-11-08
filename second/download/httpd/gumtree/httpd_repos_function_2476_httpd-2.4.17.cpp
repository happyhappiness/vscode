static const char *h2_conf_set_max_streams(cmd_parms *parms,
                                           void *arg, const char *value)
{
    h2_config *cfg = h2_config_sget(parms->server);
    cfg->h2_max_streams = (int)apr_atoi64(value);
    (void)arg;
    if (cfg->h2_max_streams < 1) {
        return "value must be > 0";
    }
    return NULL;
}