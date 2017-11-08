static const char
*set_cache_minfs(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    disk_cache_dir_conf *dconf = (disk_cache_dir_conf *)in_struct_ptr;

    if (apr_strtoff(&dconf->minfs, arg, NULL, 10) != APR_SUCCESS ||
            dconf->minfs < 0)
    {
        return "CacheMinFileSize argument must be a non-negative integer representing the min size of a file to cache in bytes.";
    }
    dconf->minfs_set = 1;
    return NULL;
}