static const char *h2_conf_set_serialize_headers(cmd_parms *parms,
                                                 void *arg, const char *value)
{
    h2_config *cfg = h2_config_sget(parms->server);
    if (!strcasecmp(value, "On")) {
        cfg->serialize_headers = 1;
        return NULL;
    }
    else if (!strcasecmp(value, "Off")) {
        cfg->serialize_headers = 0;
        return NULL;
    }
    
    (void)arg;
    return "value must be On or Off";
}