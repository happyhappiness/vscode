static void *merge_cgi_config(apr_pool_t *p, void *basev, void *overridesv)
{
    cgi_server_conf *base = (cgi_server_conf *) basev,
                    *overrides = (cgi_server_conf *) overridesv;

    return overrides->logname ? overrides : base;
}