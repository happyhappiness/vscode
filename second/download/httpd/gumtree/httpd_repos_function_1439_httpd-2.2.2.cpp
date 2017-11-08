static void *merge_proxy_dir_config(apr_pool_t *p, void *basev, void *addv)
{
    proxy_dir_conf *new = (proxy_dir_conf *) apr_pcalloc(p, sizeof(proxy_dir_conf));
    proxy_dir_conf *add = (proxy_dir_conf *) addv;
    proxy_dir_conf *base = (proxy_dir_conf *) basev;

    new->p = add->p;
    new->p_is_fnmatch = add->p_is_fnmatch;
    new->r = add->r;

    /* Put these in the dir config so they work inside <Location> */
    new->raliases = apr_array_append(p, base->raliases, add->raliases);
    new->cookie_paths
        = apr_array_append(p, base->cookie_paths, add->cookie_paths);
    new->cookie_domains
        = apr_array_append(p, base->cookie_domains, add->cookie_domains);
    new->cookie_path_str = base->cookie_path_str;
    new->cookie_domain_str = base->cookie_domain_str;
    return new;
}