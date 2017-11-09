static void *create_dir_config(apr_pool_t *p, char *dummy)
{
    disk_cache_dir_conf *dconf = apr_pcalloc(p, sizeof(disk_cache_dir_conf));

    dconf->maxfs = DEFAULT_MAX_FILE_SIZE;
    dconf->minfs = DEFAULT_MIN_FILE_SIZE;
    dconf->readsize = DEFAULT_READSIZE;
    dconf->readtime = DEFAULT_READTIME;

    return dconf;
}