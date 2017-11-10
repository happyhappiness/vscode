static void *merge_alias_config(apr_pool_t *p, void *basev, void *overridesv)
{
    alias_server_conf *a =
    (alias_server_conf *) apr_pcalloc(p, sizeof(alias_server_conf));
    alias_server_conf *base = (alias_server_conf *) basev;
    alias_server_conf *overrides = (alias_server_conf *) overridesv;

    a->aliases = apr_array_append(p, overrides->aliases, base->aliases);
    a->redirects = apr_array_append(p, overrides->redirects, base->redirects);
    return a;
}