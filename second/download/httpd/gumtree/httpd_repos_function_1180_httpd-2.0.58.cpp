static void *merge_info_config(apr_pool_t *p, void *basev, void *overridesv)
{
    info_svr_conf *new = (info_svr_conf *) apr_pcalloc(p, sizeof(info_svr_conf));
    info_svr_conf *base = (info_svr_conf *) basev;
    info_svr_conf *overrides = (info_svr_conf *) overridesv;

    new->more_info = apr_array_append(p, overrides->more_info, base->more_info);
    return new;
}