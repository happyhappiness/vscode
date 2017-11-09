static const char *h2_conf_set_early_hints(cmd_parms *parms,
                                           void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    if (!strcasecmp(value, "On")) {
        cfg->early_hints = 1;
        return NULL;
    }
    else if (!strcasecmp(value, "Off")) {
        cfg->early_hints = 0;
        return NULL;
    }
    
    (void)arg;
    return "value must be On or Off";
}