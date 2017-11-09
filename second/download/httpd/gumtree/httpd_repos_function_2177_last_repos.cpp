static void *fcgi_merge_dconf(apr_pool_t *p, void *basev, void *overridesv)
{
    fcgi_dirconf_t *a, *base, *over;

    a     = (fcgi_dirconf_t *)apr_pcalloc(p, sizeof(fcgi_dirconf_t));
    base  = (fcgi_dirconf_t *)basev;
    over  = (fcgi_dirconf_t *)overridesv;

    a->backend_type = (over->backend_type != BACKEND_DEFAULT_UNKNOWN)
                      ? over->backend_type
                      : base->backend_type;
    a->env_fixups = apr_array_append(p, base->env_fixups, over->env_fixups);
    return a;
}