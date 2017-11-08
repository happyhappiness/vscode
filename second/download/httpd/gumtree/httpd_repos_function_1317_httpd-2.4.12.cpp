static const char *set_cache_readtime(cmd_parms *parms, void *in_struct_ptr,
        const char *arg)
{
    cache_socache_dir_conf *dconf = (cache_socache_dir_conf *) in_struct_ptr;
    apr_off_t milliseconds;

    if (apr_strtoff(&milliseconds, arg, NULL, 10) != APR_SUCCESS
            || milliseconds < 0) {
        return "CacheSocacheReadTime argument must be a non-negative integer representing the max amount of time taken to cache in go.";
    }
    dconf->readtime = apr_time_from_msec(milliseconds);
    dconf->readtime_set = 1;
    return NULL;
}