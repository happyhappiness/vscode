static const char *h2_conf_set_tls_warmup_size(cmd_parms *parms,
                                               void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    cfg->tls_warmup_size = apr_atoi64(value);
    (void)arg;
    return NULL;
}