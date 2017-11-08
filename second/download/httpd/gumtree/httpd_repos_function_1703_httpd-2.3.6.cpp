static void *merge_config(apr_pool_t *p, void *basev, void *overridesv)
{
    connect_conf *c = apr_pcalloc(p, sizeof(connect_conf));
    connect_conf *base = (connect_conf *) basev;
    connect_conf *overrides = (connect_conf *) overridesv;

    c->allowed_connect_ports = apr_array_append(p,
                                                base->allowed_connect_ports,
                                                overrides->allowed_connect_ports);
    
    return c;
}