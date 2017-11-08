static const char
*set_cache_readsize(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    disk_cache_dir_conf *dconf = (disk_cache_dir_conf *)in_struct_ptr;

    if (apr_strtoff(&dconf->readsize, arg, NULL, 10) != APR_SUCCESS ||
            dconf->readsize < 0)
    {
        return "CacheReadSize argument must be a non-negative integer representing the max amount of data to cache in go.";
    }
    dconf->readsize_set = 1;
    return NULL;
}