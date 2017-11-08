static void *create_proxy_dir_config(apr_pool_t *p, char *dummy)
{
    proxy_dir_conf *new =
        (proxy_dir_conf *) apr_pcalloc(p, sizeof(proxy_dir_conf));

    /* Filled in by proxysection, when applicable */

    /* Put these in the dir config so they work inside <Location> */
    new->raliases = apr_array_make(p, 10, sizeof(struct proxy_alias));
    new->cookie_paths = apr_array_make(p, 10, sizeof(struct proxy_alias));
    new->cookie_domains = apr_array_make(p, 10, sizeof(struct proxy_alias));
    new->preserve_host_set = 0;
    new->preserve_host = 0;
    new->interpolate_env = -1; /* unset */
    new->error_override = 0;
    new->error_override_set = 0;
    new->add_forwarded_headers = 1;

    return (void *) new;
}