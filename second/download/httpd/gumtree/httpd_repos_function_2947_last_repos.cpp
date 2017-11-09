static const char *h2_conf_set_push_diary_size(cmd_parms *parms,
                                               void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    (void)arg;
    cfg->push_diary_size = (int)apr_atoi64(value);
    if (cfg->push_diary_size < 0) {
        return "value must be >= 0";
    }
    if (cfg->push_diary_size > 0 && (cfg->push_diary_size & (cfg->push_diary_size-1))) {
        return "value must a power of 2";
    }
    if (cfg->push_diary_size > (1 << 15)) {
        return "value must <= 65536";
    }
    return NULL;
}