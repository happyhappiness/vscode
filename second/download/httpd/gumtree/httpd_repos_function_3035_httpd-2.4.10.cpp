static const char *authn_cache_timeout(cmd_parms *cmd, void *CFG,
                                       const char *arg)
{
    authn_cache_dircfg *cfg = CFG;
    int secs = atoi(arg);
    cfg->timeout = apr_time_from_sec(secs);
    return NULL;
}