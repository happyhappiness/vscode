static const char
*set_cache_maxfs(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    disk_cache_dir_conf *dconf = (disk_cache_dir_conf *)in_struct_ptr;

    if (apr_strtoff(&dconf->maxfs, arg, NULL, 10) != APR_SUCCESS ||
            dconf->maxfs < 0)
    {
        return "CacheMaxFileSize argument must be a non-negative integer representing the max size of a file to cache in bytes.";
    }
    return NULL;
}