static void *create_dir_config(apr_pool_t *p, char *dummy)
{
    cache_socache_dir_conf *dconf =
            apr_pcalloc(p, sizeof(cache_socache_dir_conf));

    dconf->max = DEFAULT_MAX_FILE_SIZE;
    dconf->maxtime = apr_time_from_sec(DEFAULT_MAXTIME);
    dconf->mintime = apr_time_from_sec(DEFAULT_MINTIME);
    dconf->readsize = DEFAULT_READSIZE;
    dconf->readtime = DEFAULT_READTIME;

    return dconf;
}