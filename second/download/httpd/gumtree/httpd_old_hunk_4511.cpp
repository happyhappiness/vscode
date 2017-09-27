    return NULL;
}

static const char *h2_conf_set_session_extra_files(cmd_parms *parms,
                                                   void *arg, const char *value)
{
    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
    apr_int64_t max = (int)apr_atoi64(value);
    if (max < 0) {
        return "value must be a non-negative number";
    }
    cfg->session_extra_files = (int)max;
    (void)arg;
    return NULL;
}

static const char *h2_conf_set_serialize_headers(cmd_parms *parms,
                                                 void *arg, const char *value)
{
