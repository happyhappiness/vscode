static const char *h2_add_alt_svc(cmd_parms *parms,
                                  void *arg, const char *value)
{
    if (value && strlen(value)) {
        h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
        h2_alt_svc *as = h2_alt_svc_parse(value, parms->pool);
        if (!as) {
            return "unable to parse alt-svc specifier";
        }
        if (!cfg->alt_svcs) {
            cfg->alt_svcs = apr_array_make(parms->pool, 5, sizeof(h2_alt_svc*));
        }
        APR_ARRAY_PUSH(cfg->alt_svcs, h2_alt_svc*) = as;
    }
    (void)arg;
    return NULL;
}