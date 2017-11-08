static const char *h2_conf_set_modern_tls_only(cmd_parms *parms,
                                               void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    if (!strcasecmp(value, "On")) {
        cfg->modern_tls_only = 1;
        return NULL;
    }
    else if (!strcasecmp(value, "Off")) {
        cfg->modern_tls_only = 0;
        return NULL;
    }
    
    (void)arg;
    return "value must be On or Off";
}