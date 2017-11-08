static void *merge_cgid_config(apr_pool_t *p, void *basev, void *overridesv) 
{ 
    cgid_server_conf *base = (cgid_server_conf *) basev, *overrides = (cgid_server_conf *) overridesv; 

    return overrides->logname ? overrides : base; 
}