static const char *h2_conf_add_push_priority(cmd_parms *cmd, void *_cfg,
                                             const char *ctype, const char *sdependency,
                                             const char *sweight)
{
    h2_config *cfg = (h2_config *)h2_config_sget(cmd->server);
    const char *sdefweight = "16";         /* default AFTER weight */
    h2_dependency dependency;
    h2_priority *priority;
    int weight;
    
    if (!strlen(ctype)) {
        return "1st argument must be a mime-type, like 'text/css' or '*'";
    }
    
    if (!sweight) {
        /* 2 args only, but which one? */
        if (apr_isdigit(sdependency[0])) {
            sweight = sdependency;
            sdependency = "AFTER";        /* default dependency */
        }
    }
    
    if (!strcasecmp("AFTER", sdependency)) {
        dependency = H2_DEPENDANT_AFTER;
    } 
    else if (!strcasecmp("BEFORE", sdependency)) {
        dependency = H2_DEPENDANT_BEFORE;
        if (sweight) {
            return "dependecy 'Before' does not allow a weight";
        }
    } 
    else if (!strcasecmp("INTERLEAVED", sdependency)) {
        dependency = H2_DEPENDANT_INTERLEAVED;
        sdefweight = "256";        /* default INTERLEAVED weight */
    }
    else {
        return "dependency must be one of 'After', 'Before' or 'Interleaved'";
    }
    
    weight = (int)apr_atoi64(sweight? sweight : sdefweight);
    if (weight < NGHTTP2_MIN_WEIGHT) {
        return apr_psprintf(cmd->pool, "weight must be a number >= %d",
                            NGHTTP2_MIN_WEIGHT);
    }
    
    priority = apr_pcalloc(cmd->pool, sizeof(*priority));
    priority->dependency = dependency;
    priority->weight = weight;
    
    if (!cfg->priorities) {
        cfg->priorities = apr_hash_make(cmd->pool);
    }
    apr_hash_set(cfg->priorities, ctype, strlen(ctype), priority);
    return NULL;
}