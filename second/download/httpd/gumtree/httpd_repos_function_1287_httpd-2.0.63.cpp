static void *create_proxy_dir_config(apr_pool_t *p, char *dummy)
{
    proxy_dir_conf *new =
        (proxy_dir_conf *) apr_pcalloc(p, sizeof(proxy_dir_conf));

    /* Filled in by proxysection, when applicable */

    return (void *) new;
}