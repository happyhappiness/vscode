static void *create_proxy_dir_config(apr_pool_t *p, char *dummy)
{
    proxy_dir_conf *new =
        (proxy_dir_conf *) apr_pcalloc(p, sizeof(proxy_dir_conf));

    /* Filled in by proxysection, when applicable */

    /* Put these in the dir config so they work inside <Location> */
    new->raliases = apr_array_make(p, 10, sizeof(struct proxy_alias));
    new->cookie_paths = apr_array_make(p, 10, sizeof(struct proxy_alias));
    new->cookie_domains = apr_array_make(p, 10, sizeof(struct proxy_alias));
    new->cookie_path_str = apr_strmatch_precompile(p, "path=", 0);
    new->cookie_domain_str = apr_strmatch_precompile(p, "domain=", 0);

    return (void *) new;
}