static void *create_dir_conf(apr_pool_t *p, char *dummy)
{
    fcgi_dir_conf *dconf = apr_pcalloc(p, sizeof(fcgi_dir_conf));

    dconf->authoritative = 1;
    return dconf;
}