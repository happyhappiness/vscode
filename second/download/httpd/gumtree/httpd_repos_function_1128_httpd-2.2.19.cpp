static void *merge_userdir_config(apr_pool_t *p, void *basev, void *overridesv)
{
    userdir_config *cfg = apr_pcalloc(p, sizeof(userdir_config));
    userdir_config *base = basev, *overrides = overridesv;
 
    cfg->globally_disabled = (overrides->globally_disabled != O_DEFAULT) ? overrides->globally_disabled : base->globally_disabled;
    cfg->userdir = (overrides->userdir != DEFAULT_USER_DIR) ? overrides->userdir : base->userdir;
 
    /* not merged */
    cfg->enabled_users = overrides->enabled_users;
    cfg->disabled_users = overrides->disabled_users;
    
    return cfg;
}