static const char *h2_conf_set_copy_files(cmd_parms *parms,
                                          void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)arg;
    if (!strcasecmp(value, "On")) {
        cfg->copy_files = 1;
        return NULL;
    }
    else if (!strcasecmp(value, "Off")) {
        cfg->copy_files = 0;
        return NULL;
    }
    
    (void)arg;
    return "value must be On or Off";
}