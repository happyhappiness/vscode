static void *merge_proxy_dir_config(apr_pool_t *p, void *basev, void *addv)
{
    proxy_dir_conf *new = (proxy_dir_conf *) apr_pcalloc(p, sizeof(proxy_dir_conf));
    proxy_dir_conf *add = (proxy_dir_conf *) addv;
    proxy_dir_conf *base = (proxy_dir_conf *) basev;

    new->p = add->p;
    new->p_is_fnmatch = add->p_is_fnmatch;
    new->r = add->r;
    new->refs = add->refs;

    /* Put these in the dir config so they work inside <Location> */
    new->raliases = apr_array_append(p, base->raliases, add->raliases);
    new->cookie_paths
        = apr_array_append(p, base->cookie_paths, add->cookie_paths);
    new->cookie_domains
        = apr_array_append(p, base->cookie_domains, add->cookie_domains);
    new->interpolate_env = (add->interpolate_env == -1) ? base->interpolate_env
                                                        : add->interpolate_env;
    new->preserve_host = (add->preserve_host_set == 0) ? base->preserve_host
                                                        : add->preserve_host;
    new->preserve_host_set = add->preserve_host_set || base->preserve_host_set;
    new->error_override = (add->error_override_set == 0) ? base->error_override
                                                        : add->error_override;
    new->error_override_set = add->error_override_set || base->error_override_set;
    new->alias = (add->alias_set == 0) ? base->alias : add->alias;
    new->alias_set = add->alias_set || base->alias_set;
    new->add_forwarded_headers = add->add_forwarded_headers;
    return new;
}