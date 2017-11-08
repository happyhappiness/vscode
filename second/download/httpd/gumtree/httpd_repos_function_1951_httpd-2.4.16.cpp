static void *server_merge(apr_pool_t *p, void *basev, void *overridesv)
{
    express_server_conf *a, *base, *overrides;

    a         = (express_server_conf *)apr_pcalloc(p,
                                                   sizeof(express_server_conf));
    base      = (express_server_conf *)basev;
    overrides = (express_server_conf *)overridesv;

    a->dbmfile = (overrides->dbmfile) ? overrides->dbmfile : base->dbmfile;
    a->dbmtype = (overrides->dbmtype) ? overrides->dbmtype : base->dbmtype;
    a->enabled = (overrides->enabled) ? overrides->enabled : base->enabled;

    return (void *)a;
}