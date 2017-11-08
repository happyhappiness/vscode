static void *log_debug_create_dconf(apr_pool_t *p, char *dirspec)
{
    log_debug_dirconf *dconf = apr_pcalloc(p, sizeof(log_debug_dirconf));
    return dconf;
}