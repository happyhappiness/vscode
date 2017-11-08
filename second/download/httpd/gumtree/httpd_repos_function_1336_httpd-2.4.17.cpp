static const char *set_cache_max(cmd_parms *parms, void *in_struct_ptr,
        const char *arg)
{
    cache_socache_dir_conf *dconf = (cache_socache_dir_conf *) in_struct_ptr;

    if (apr_strtoff(&dconf->max, arg, NULL, 10) != APR_SUCCESS || dconf->max
            < 1024) {
        return "CacheSocacheMaxSize argument must be a integer representing the max size of a cached entry (headers and body), at least 1024";
    }
    dconf->max_set = 1;
    return NULL;
}