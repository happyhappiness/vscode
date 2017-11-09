static const char *set_cache_mintime(cmd_parms *parms, void *in_struct_ptr,
        const char *arg)
{
    cache_socache_dir_conf *dconf = (cache_socache_dir_conf *) in_struct_ptr;
    apr_off_t seconds;

    if (apr_strtoff(&seconds, arg, NULL, 10) != APR_SUCCESS || seconds < 0) {
        return "CacheSocacheMinTime argument must be the minimum amount of time in seconds to cache an entry.";
    }
    dconf->mintime = apr_time_from_sec(seconds);
    dconf->mintime_set = 1;
    return NULL;
}