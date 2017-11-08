static const char
*set_cache_minfs(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    disk_cache_conf *conf = ap_get_module_config(parms->server->module_config,
                                                 &disk_cache_module);

    if (apr_strtoff(&conf->minfs, arg, NULL, 0) != APR_SUCCESS ||
            conf->minfs < 0) 
    {
        return "CacheMinFileSize argument must be a non-negative integer representing the min size of a file to cache in bytes.";
    }
    return NULL;
}