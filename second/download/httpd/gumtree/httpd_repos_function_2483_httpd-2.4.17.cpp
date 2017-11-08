static const char *h2_conf_set_alt_svc_max_age(cmd_parms *parms,
                                               void *arg, const char *value)
{
    h2_config *cfg = h2_config_sget(parms->server);
    cfg->alt_svc_max_age = (int)apr_atoi64(value);
    (void)arg;
    return NULL;
}