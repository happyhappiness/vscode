static const char
*set_cache_maxfs(cmd_parms *parms, void *in_struct_ptr, const char *arg)
{
    disk_cache_conf *conf = ap_get_module_config(parms->server->module_config,
                                                 &disk_cache_module);
    if (apr_strtoff(&conf->maxfs, arg, NULL, 0) != APR_SUCCESS ||
            conf->maxfs < 0) 
    {
        return "CacheMaxFileSize argument must be a non-negative integer representing the max size of a file to cache in bytes.";
    }
    return NULL;
}